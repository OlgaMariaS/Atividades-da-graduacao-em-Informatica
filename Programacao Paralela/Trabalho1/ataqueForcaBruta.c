#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <pthread.h>
#include <semaphore.h>

#define TAMANHO 12 // Tamanho máximo da senha (utilizado para limitar a complexidade evitando longos períodos de processamento)
#define NUMERO_DE_THREADS 2 // Números de threads é no minino duas se não o comportamente seria como o sequencial
#define TOTAL_SUBSTITUICOES 6 // Total de tipos de substituição leet speak suportados
#define MAX_MUTACOES 1000
#define MAX_LINHA 512
#define NOME_DICIONARIO "rockyou.txt"

int tamMaxSenha;
char alvo[TAMANHO + 1];

/* ESTRUTURAS PARA PARALELIZAÇÃO */
typedef struct {
    int inicio;
    int fim;
    const char *palavra;
    char (*resultados)[8];
} DadosMutacaoData;

typedef struct {
    long thread_id;
    long tentativas_locais;
    char **palavras;
    char **senha_achada;
    int inicio;
    int fim;
} DadosThreadDicionario;

typedef struct {
    long long inicio;
    long long fim;
    long thread_id;
    long tentativas_locais;
    char **senha_achada;
} DadosThread;

typedef struct {
    long thread_id;
    int inicio_subst;        
    int fim_subst;
    const char *palavra;
    int len_palavra;
    char **resultados_globais; 
    int *total_global;
    pthread_mutex_t *mutex;
    int maxResultados;
} DadosSubstituicao;

typedef struct {
    long thread_id;
    int inicio_iter;         
    int fim_iter;           
    const char *palavra;
    int tamanhoBase;
    char ultimo;
    int espacoLivre;
    char **resultados_globais;
    int *total_global;         
    pthread_mutex_t *mutex;
    int maxResultados;
} DadosSufixo;

typedef struct {
    long thread_id;
    int inicio_lista;        
    int fim_lista;           
    const char *palavra;
    char **listaPalavras;
    char **resultados_globais; 
    int *total_global;      
    pthread_mutex_t *mutex;
    int maxResultados;
} DadosConcatenar;
/* ============================================================================ */
/* FUNÇÕES AUXILIARES */

/*
 * Remove quebra de linha e espaço do final da string.
 */
void remover_quebra_linha(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

/*
 * Lê a senha alvo e faz validações sobre a quantidade de caracteres.
 */
int ler_senha_alvo(void) {
    char buffer[256];

    printf("Digite a senha alvo: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("[ERRO] Falha ao ler a senha alvo.\n");
        return 0;
    }

    remover_quebra_linha(buffer);

    if ((int)strlen(buffer) > TAMANHO) {
        printf("[ERRO] A senha alvo nao pode ter mais de %d caracteres.\n", TAMANHO);
        return 0;
    }

    strcpy(alvo, buffer);
    return 1;
}

/*
 * Duplica uma string em memória dinâmica.
 * Utilizada para apontar para a palavra encontrada
 */
char *duplicar_string(const char *origem) {
    char *copia = (char *)malloc(strlen(origem) + 1);
    if (copia == NULL) {
        printf("[ERRO] Falha ao alocar memória para string.\n");
        exit(1);
    }
    strcpy(copia, origem);
    return copia;
}

/*
 * Verifica se a string contem apenas dígitos.
 */
int eh_numero(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) return 0;
    }
    return 1;
}

/*
 * Verifica se a string tem exatamente 4 dígitos e parece um ano.
 */
int eh_ano(const char *str) {
    if (!eh_numero(str)) return 0;
    if (strlen(str) != 4) return 0;

    int ano = atoi(str);
    return (ano >= 1900 && ano <= 2099);
}

/*
 * Retorna 10^exp
 */
int potencia10(int exp) {
    int r = 1;
    for (int i = 0; i < exp; i++) r *= 10;
    return r;
}

/*
 * Compara um candidato com a senha alvo.
 */
int comparar_candidato(const char *candidato) {
    if (strcmp(candidato, alvo) == 0) {
        printf(">>> ENCONTRADO! '%s' e igual ao alvo.\n", candidato);
        return 1;
    }
    return 0;
}
/*
 * Libera memória.
 */
void liberar_array_strings(char **array, int qtd) {
    if (array == NULL) return;

    for (int i = 0; i < qtd; i++) {
        free(array[i]);
    }
    free(array);
}
/*
 * Lê o arquivo base e guarda em array dinâmico.
 */
char **ler_arquivo_para_array(const char *nomeArquivo, int *quantidade, int tamanho_exato) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("[ERRO] Nao foi possível abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    char linha[MAX_LINHA];
    char **array = NULL;
    int count = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        remover_quebra_linha(linha);

        if (strlen(linha) == 0) continue;

        if (tamanho_exato > 0) {
            if ((int)strlen(linha) != tamanho_exato) continue;
        }

        char **novo = realloc(array, (count + 1) * sizeof(char *));
        if (novo == NULL) {
            fclose(fp);
            liberar_array_strings(array, count);
            return NULL;
        }

        array = novo;
        array[count] = duplicar_string(linha);
        count++;
    }

    fclose(fp);
    *quantidade = count;
    return array;
}

/* ============================================================================ */
/* FUNÇÕES DE ATAQUE POR MUTAÇÕES */

/* 
 * Tabela de substituições:
 * Cada entrada define: o caractere original, o substituto
 */
static const struct { char orig; char subst1; char subst2; } TABELA_SUBST[TOTAL_SUBSTITUICOES] = {
    {'a', '4', '@'},
    {'e', '3', '\0'},
    {'i', '1', '\0'},
    {'o', '0', '\0'},
    {'s', '5', '\0'},
    {'t', '7', '\0'},
};

/* 
 * Cada thread recebe um subconjunto de índices da TABELA_SUBST (inicio_subst..fim_subst).
 * Para cada tipo de substituição no seu intervalo, a thread percorre toda a palavra
 * buscando ocorrências do caractere original e gera a(s) string(s) substituída(s).
 * O acesso ao array compartilhado e ao contador global é protegido por mutex. */
void *rotina_mutacao_substituicao(void *arg) {
    DadosSubstituicao *dados = (DadosSubstituicao *)arg;
    const char *palavra = dados->palavra;
    int len = dados->len_palavra;

    for (int s = dados->inicio_subst; s < dados->fim_subst; s++) {
        char orig   = TABELA_SUBST[s].orig;
        char subst1 = TABELA_SUBST[s].subst1;
        char subst2 = TABELA_SUBST[s].subst2;

        for (int i = 0; i < len; i++) {
            char c = (char)tolower((unsigned char)palavra[i]);
            if (c != orig) continue;

            // Primeira substituição
            char nova[TAMANHO + 1];
            strncpy(nova, palavra, tamMaxSenha);
            nova[tamMaxSenha] = '\0';
            nova[i] = subst1;

            pthread_mutex_lock(dados->mutex);
            if (dados->total_global[0] < dados->maxResultados) {
                dados->resultados_globais[dados->total_global[0]] = duplicar_string(nova);
                dados->total_global[0]++;
            }
            pthread_mutex_unlock(dados->mutex);

            // Segunda substituição (apenas 'a' -> '@')
            if (subst2 != '\0') {
                strncpy(nova, palavra, tamMaxSenha);
                nova[tamMaxSenha] = '\0';
                nova[i] = subst2;

                pthread_mutex_lock(dados->mutex);
                if (dados->total_global[0] < dados->maxResultados) {
                    dados->resultados_globais[dados->total_global[0]] = duplicar_string(nova);
                    dados->total_global[0]++;
                }
                pthread_mutex_unlock(dados->mutex);
            }
        }
    }
    pthread_exit(NULL);
}

/*
 * Gera mutações por substituiçao.
 * a->4 ou @, e->3, o->0, i->1, s->5, t->7
 *
 * Distribui tipos de substituição entre as threads disponíveis:
 *   - Se num_threads >= TOTAL_SUBSTITUICOES: cada thread recebe exatamente 1 tipo.
 *   - Caso contrário: os tipos são divididos igualmente entre as threads, ex: 2 threads para 6 tipos => cada thread processa 3 tipos distintos.
 */
int mutacao_substituicao(const char *palavra, char resultados[][tamMaxSenha + 1], int maxResultados, int num_threads) {
    int len = (int)strlen(palavra);
    if (len == 0) return 0;

    // Array para receber as substituições das threads
    char **res_temp = (char **)calloc(maxResultados, sizeof(char *));
    if (!res_temp) return 0;

    int total_global = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    // Determina quantas threads realmente serão criadas (não mais do que TOTAL_SUBSTITUICOES)
    if (num_threads > TOTAL_SUBSTITUICOES) num_threads = TOTAL_SUBSTITUICOES;

    pthread_t threads[TOTAL_SUBSTITUICOES];
    DadosSubstituicao dados_threads[TOTAL_SUBSTITUICOES];
    int carga = TOTAL_SUBSTITUICOES / num_threads;

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].thread_id         = i;
        dados_threads[i].inicio_subst      = i * carga;
        dados_threads[i].fim_subst         = (i == num_threads - 1) ? TOTAL_SUBSTITUICOES : (i + 1) * carga;
        dados_threads[i].palavra           = palavra;
        dados_threads[i].len_palavra       = len;
        dados_threads[i].resultados_globais = res_temp;
        dados_threads[i].total_global      = &total_global;
        dados_threads[i].mutex             = &mutex;
        dados_threads[i].maxResultados     = maxResultados;

        pthread_create(&threads[i], NULL, rotina_mutacao_substituicao, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    // Copia para o array estático esperado pelo chamador
    int total = total_global;
    for (int i = 0; i < total; i++) {
        strncpy(resultados[i], res_temp[i], tamMaxSenha);
        resultados[i][tamMaxSenha] = '\0';
        free(res_temp[i]);
    }
    free(res_temp);

    return total;
}

/* 
 * Cada thread recebe um subintervalo do loop externo (i = número de repetições
 * da última letra). Para cada valor de i no seu intervalo, a thread gera as
 * variações de sufixo.
 */
void *rotina_mutacao_sufixo(void *arg) {
    DadosSufixo *dados = (DadosSufixo *)arg;
    const char *palavra = dados->palavra;

    for (int i = dados->inicio_iter; i <= dados->fim_iter; i++) {
        if (i == 0) continue; // i=0 não gera sufixo de letras

        // Monta prefixo com 'i' repetições da última letra
        char prefixo[TAMANHO + 1];
        strcpy(prefixo, palavra);
        for (int r = 0; r < i; r++) {
            int lp = (int)strlen(prefixo);
            if (lp >= tamMaxSenha) break;
            prefixo[lp] = dados->ultimo;
            prefixo[lp + 1] = '\0';
        }

        // Versão sem número
        pthread_mutex_lock(dados->mutex);
        if (dados->total_global[0] < dados->maxResultados) {
            dados->resultados_globais[dados->total_global[0]] = duplicar_string(prefixo);
            dados->total_global[0]++;
        }
        pthread_mutex_unlock(dados->mutex);

        // Criar sufixos com números sendo o máximo a quantidade de espaço livre
        // ex: nome até tamMaxSenha(7) sobra 3 resulta em: nome100, nome101, ..., nome999
        int espacoNumeros = tamMaxSenha - (int)strlen(prefixo);
        if (espacoNumeros <= 0) continue;

        int limite = potencia10(espacoNumeros) - 1;

        for (int n = 1; n <= limite; n++) {
            char candidato[TAMANHO + 1];
            snprintf(candidato, sizeof(candidato), "%s%d", prefixo, n);
            candidato[tamMaxSenha] = '\0';

            if ((int)strlen(candidato) > tamMaxSenha) continue;

            pthread_mutex_lock(dados->mutex);
            if (dados->total_global[0] < dados->maxResultados) {
                dados->resultados_globais[dados->total_global[0]] = duplicar_string(candidato);
                dados->total_global[0]++;
            }
            pthread_mutex_unlock(dados->mutex);
        }
    }
    pthread_exit(NULL);
}

/* 
 * Gera mutações por sufixo respeitando o tamanho máximo da senha.
 * nome -> nome123, nomenom, nomeeee, nomeee1
 * 
 * O loop externo da função original vai de 1 a max_repeti_ult_letra (3 iterações).
 * Essas iterações são distribuídas entre as threads disponíveis.
 */
int mutacao_sufixo(const char *palavra, char resultados[][tamMaxSenha + 1], int maxResultados, int num_threads) {
    int tamanhoBase = (int)strlen(palavra);
    int max_repeti_ult_letra = 3;

    // se o tamanho da palavra ja é o máximo, não é possível adicionar sufixo
    if (tamanhoBase >= tamMaxSenha) return 0;
    // palavra vazia
    if (tamanhoBase == 0) return 0;

    char ultimo = palavra[tamanhoBase - 1];
    int espacoLivre = tamMaxSenha - tamanhoBase;

    // Número real de iterações do loop externo
    int max_iter = (max_repeti_ult_letra < espacoLivre) ? max_repeti_ult_letra : espacoLivre;

    char **res_temp = (char **)calloc(maxResultados, sizeof(char *));
    if (!res_temp) return 0;

    int total_global = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    if (num_threads > max_iter) num_threads = max_iter;

    pthread_t threads[TAMANHO];
    DadosSufixo dados_threads[TAMANHO];
    int carga = max_iter / num_threads;

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].thread_id          = i;
        dados_threads[i].inicio_iter        = i * carga + 1; // começa em 1 (i=0 não gera sufixo)
        dados_threads[i].fim_iter           = (i == num_threads - 1) ? max_iter : (i + 1) * carga;
        dados_threads[i].palavra            = palavra;
        dados_threads[i].tamanhoBase        = tamanhoBase;
        dados_threads[i].ultimo             = ultimo;
        dados_threads[i].espacoLivre        = espacoLivre;
        dados_threads[i].resultados_globais = res_temp;
        dados_threads[i].total_global       = &total_global;
        dados_threads[i].mutex              = &mutex;
        dados_threads[i].maxResultados      = maxResultados;

        pthread_create(&threads[i], NULL, rotina_mutacao_sufixo, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    int total = total_global;
    for (int i = 0; i < total; i++) {
        strncpy(resultados[i], res_temp[i], tamMaxSenha);
        resultados[i][tamMaxSenha] = '\0';
        free(res_temp[i]);
    }
    free(res_temp);

    return total;
}

/* 
 * Função auxiliar para a mutacao_data 
 */
void *rotina_mutacao_data(void *arg) {
    DadosMutacaoData *dados = (DadosMutacaoData *)arg;

    for (int k = dados->inicio; k < dados->fim; k++) {
        if (k < 12) {
            // Súfixo Mês (0 a 11)
            snprintf(dados->resultados[k], tamMaxSenha + 1, "%s%02d", dados->palavra, k + 1);
        } else if (k < 43) {
            // Súfixo Dia (12 a 42)
            snprintf(dados->resultados[k], tamMaxSenha + 1, "%s%02d", dados->palavra, k - 12 + 1);
        } else if (k < 55) {
            // Prefixo Mês (43 a 54)
            snprintf(dados->resultados[k], tamMaxSenha + 1, "%02d%s", k - 43 + 1, dados->palavra);
        } else {
            // Prefixo Dia (55 a 85)
            snprintf(dados->resultados[k], tamMaxSenha + 1, "%02d%s", k - 55 + 1, dados->palavra);
        }
    }
    pthread_exit(NULL);
}

/*
 * Gera mutações com datas
 * Se a palavra for um ano, gera mutações de data compatíveis com tamMaxSenha.
 * YYYY -> YYYYMMD, DDMYYYY, YYYYMDD
 */
int mutacao_data(const char *palavra, char resultados[][tamMaxSenha + 1], int maxResultados, int num_threads) {
    if (!eh_ano(palavra)) return 0;

    int total_mutacoes = 86; 
    if (total_mutacoes > maxResultados) {
        total_mutacoes = maxResultados;
    }

    pthread_t threads[num_threads];
    DadosMutacaoData dados_threads[num_threads];
    int carga_por_thread = total_mutacoes / num_threads;

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].palavra = palavra;
        dados_threads[i].resultados = resultados;
        dados_threads[i].inicio = i * carga_por_thread;
        dados_threads[i].fim = (i == num_threads - 1) ? total_mutacoes : (i + 1) * carga_por_thread;

        pthread_create(&threads[i], NULL, rotina_mutacao_data, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return total_mutacoes;
}

/* 
 * Cada thread recebe um subintervalo da lista de palavras (inicio_lista..fim_lista).
 * Para cada palavra no seu intervalo, gera as duas concatenações (palavra+termo e termo+palavra),
 * truncando ao tamMaxSenha. 
 */
void *rotina_mutacao_concatenar(void *arg) {
    DadosConcatenar *dados = (DadosConcatenar *)arg;
    const char *palavra = dados->palavra;

    for (int i = dados->inicio_lista; i < dados->fim_lista; i++) {
        char temp1[2 * TAMANHO + 10];
        char temp2[2 * TAMANHO + 10];

        snprintf(temp1, sizeof(temp1), "%s%s", palavra, dados->listaPalavras[i]);
        snprintf(temp2, sizeof(temp2), "%s%s", dados->listaPalavras[i], palavra);

        // Primeira concatenação: palavra + termo
        pthread_mutex_lock(dados->mutex);
        if (dados->total_global[0] < dados->maxResultados) {
            char buf[TAMANHO + 1];
            strncpy(buf, temp1, tamMaxSenha);
            buf[tamMaxSenha] = '\0';
            dados->resultados_globais[dados->total_global[0]] = duplicar_string(buf);
            dados->total_global[0]++;
        }
        pthread_mutex_unlock(dados->mutex);

        // Segunda concatenação: termo + palavra
        pthread_mutex_lock(dados->mutex);
        if (dados->total_global[0] < dados->maxResultados) {
            char buf[TAMANHO + 1];
            strncpy(buf, temp2, tamMaxSenha);
            buf[tamMaxSenha] = '\0';
            dados->resultados_globais[dados->total_global[0]] = duplicar_string(buf);
            dados->total_global[0]++;
        }
        pthread_mutex_unlock(dados->mutex);
    }
    pthread_exit(NULL);
}

/*
 * Gera mutações concatendo de duas formas as palavras do input.
 * nome + teste = nometes, tesnome
 *
 * A lista de palavras é dividida igualmente entre as threads disponíveis.
 * Cada thread processa o seu subintervalo de forma independente.
 */
int mutacao_concatenar_termos(const char *palavra, char **listaPalavras, int qtdPalavras, char resultados[][tamMaxSenha + 1], int maxResultados, int num_threads) {
    if (qtdPalavras == 0) return 0;

    char **res_temp = (char **)calloc(maxResultados, sizeof(char *));
    if (!res_temp) return 0;

    int total_global = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    if (num_threads > qtdPalavras) num_threads = qtdPalavras;

    pthread_t threads[num_threads];
    DadosConcatenar dados_threads[num_threads];
    int carga = qtdPalavras / num_threads;

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].thread_id          = i;
        dados_threads[i].inicio_lista       = i * carga;
        dados_threads[i].fim_lista          = (i == num_threads - 1) ? qtdPalavras : (i + 1) * carga;
        dados_threads[i].palavra            = palavra;
        dados_threads[i].listaPalavras      = listaPalavras;
        dados_threads[i].resultados_globais  = res_temp;
        dados_threads[i].total_global       = &total_global;
        dados_threads[i].mutex              = &mutex;
        dados_threads[i].maxResultados      = maxResultados;

        pthread_create(&threads[i], NULL, rotina_mutacao_concatenar, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    int total = total_global;
    for (int i = 0; i < total; i++) {
        strncpy(resultados[i], res_temp[i], tamMaxSenha);
        resultados[i][tamMaxSenha] = '\0';
        free(res_temp[i]);
    }
    free(res_temp);

    return total;
}

/*
 * Aplica 3 métodos de mutações em todas as palavras do array de input.
 * Compara se as mutações geradas são iguais a senha alvo. 
 */
char *ataque_por_mutacoes(char **array, int qtdPalavras, long *tentativas, int num_threads) {
    printf("[ETAPA 1] Iniciando ataque por mutacoes PARALELO com %d threads\n\n", num_threads);

    for (int i = 0; i < qtdPalavras; i++) {

        char resultados[MAX_MUTACOES][tamMaxSenha + 1];
        int qtd = 0;

        qtd = mutacao_substituicao(array[i], resultados, MAX_MUTACOES, num_threads);
        for (int j = 0; j < qtd; j++) {
            (*tentativas)++;
            if (comparar_candidato(resultados[j])) {
                return duplicar_string(resultados[j]);
            }
        }

        qtd = mutacao_sufixo(array[i], resultados, MAX_MUTACOES, num_threads);
        for (int j = 0; j < qtd; j++) {
            (*tentativas)++;
            if (comparar_candidato(resultados[j])) {
                return duplicar_string(resultados[j]);
            }
        }

        qtd = mutacao_data(array[i], resultados, MAX_MUTACOES, num_threads);
        for (int j = 0; j < qtd; j++) {
            (*tentativas)++;
            if (comparar_candidato(resultados[j])) {
                return duplicar_string(resultados[j]);
            }
        }

        qtd = mutacao_concatenar_termos(array[i], array, qtdPalavras, resultados, MAX_MUTACOES, num_threads);
        for (int j = 0; j < qtd; j++) {
            (*tentativas)++;
            if (comparar_candidato(resultados[j])) {
                return duplicar_string(resultados[j]);
            }
        }
    }
    printf("==============================\n");
    return NULL;
}

/* ============================================================================ */
/* ATAQUE POR DICIONÁRIO */

void *rotina_ataque_dicionario(void *arg) {
    DadosThreadDicionario *dados = (DadosThreadDicionario *)arg;

    for (int i = dados->inicio; i < dados->fim; i++) {
        if (*(dados->senha_achada) != NULL) pthread_exit(NULL);

        if (dados->thread_id == 0 && i > 0 && i % 1000000 == 0) {
            printf("[PROGRESSO] Dicionario: %d milhoes de palavras testadas.\n", i / 1000000);
        }

        dados->tentativas_locais++;

        if (strcmp(dados->palavras[i], alvo) == 0) {
            *(dados->senha_achada) = duplicar_string(dados->palavras[i]);
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}
/*
 * Ataque de força bruta usando o dicionário rockyou.
 * Aplica um filtro e testa somente as palavras com tamanho igual a tamMaxSenha.
 */
char *ataque_por_dicionario(long *tentativas, int num_threads) {
    printf("[ETAPA 2] Iniciando o ataque por dicionario PARALELO com %d threads\n\n", num_threads);

    int qtd = 0;
    char **palavras = ler_arquivo_para_array(NOME_DICIONARIO, &qtd, tamMaxSenha);
    if (palavras == NULL) return NULL;

    printf("Total de palavras filtradas com tamanho %d: %d\n", tamMaxSenha, qtd);

    pthread_t threads[num_threads];
    DadosThreadDicionario dados_threads[num_threads];
    char *resultado = NULL;

    int carga_por_thread = qtd / num_threads;

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].thread_id = i;
        dados_threads[i].tentativas_locais = 0;
        dados_threads[i].palavras = palavras;
        dados_threads[i].senha_achada = &resultado;
        dados_threads[i].inicio = i * carga_por_thread;
        dados_threads[i].fim = (i == num_threads - 1) ? qtd : (i + 1) * carga_por_thread;

        pthread_create(&threads[i], NULL, rotina_ataque_dicionario, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        *tentativas += dados_threads[i].tentativas_locais;
    }

    printf("==============================\n");
    liberar_array_strings(palavras, qtd);
    
    return resultado;
}
/* ============================================================================ */
/* ATAQUE NÚMERICO */

/*
 * Ataque usando apenas números com exatamente tamMaxSenha dígitos.
 * Para tamMaxSenha=7, vai de 1000000 ate 9999999.
 */
void *rotina_ataque_numerico(void *arg) {
    DadosThread *dados = (DadosThread *)arg;
    char tentativa[tamMaxSenha + 1];

    for (long long i = dados->inicio; i < dados->fim; i++) {
        if (*(dados->senha_achada) != NULL) pthread_exit(NULL);

        sprintf(tentativa, "%0*lld", tamMaxSenha, i);

        if (dados->thread_id == 0 && i % 1000000 == 0) {
            printf("[PROGRESSO] %lld milhoes de numeros testados...\n", i / 1000000);
        }

        dados->tentativas_locais++;

        if (strcmp(tentativa, alvo) == 0) {
            *(dados->senha_achada) = duplicar_string(tentativa);
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}

/*
 * Ataque usando apenas números com exatamente tamMaxSenha dígitos.
 * Para tamMaxSenha=7, vai de 1000000 ate 9999999.
 */
char *ataque_numerico(long *tentativas, int num_threads) {
    long long inicio_total = potencia10(tamMaxSenha - 1);
    long long fim_total = potencia10(tamMaxSenha);
    long long total_numeros = fim_total - inicio_total;
    long long carga_por_thread = total_numeros / num_threads;

    pthread_t threads[num_threads];
    DadosThread dados_threads[num_threads];
    char *resultado = NULL; 

    printf("\n [ETAPA 3] Iniciando ataque numerico PARALELO com %d threads\n", num_threads);

    for (int i = 0; i < num_threads; i++) {
        dados_threads[i].thread_id = i;
        dados_threads[i].tentativas_locais = 0;
        dados_threads[i].inicio = inicio_total + (i * carga_por_thread);
        dados_threads[i].fim = (i == num_threads - 1) ? fim_total : dados_threads[i].inicio + carga_por_thread;
        dados_threads[i].senha_achada = &resultado; 

        pthread_create(&threads[i], NULL, rotina_ataque_numerico, (void *)&dados_threads[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        *tentativas += dados_threads[i].tentativas_locais;
    }

    printf("==============================\n");
    return resultado;
}
/* ============================================================================ */

/*
 * Orquestra tudo. 
 * Tenta quebrar a senha do método mais provavél para o mais exaustivo.
 */
char *forca_bruta(char **arrayBase, int qtdPalavrasBase, long *tentativas, int num_threads) {
    *tentativas = 0;

    char *encontrada = ataque_por_mutacoes(arrayBase, qtdPalavrasBase, tentativas, num_threads);
    if (encontrada != NULL) return encontrada;

    encontrada = ataque_por_dicionario(tentativas, num_threads);
    if (encontrada != NULL) return encontrada;

    encontrada = ataque_numerico(tentativas, num_threads);
    if (encontrada != NULL) return encontrada;

    return NULL;
}

/* ============================================================================ */

int main() {
    // Configuraçao de linguagem 
    setlocale(LC_ALL, "");

    char nomeArquivoBase[256];
    int qtdPalavrasBase = 0;
    int numero_threads = 0;
    long tentativas = 0;

    printf("\nEste e um programa paralelizado para simular um ataque de forca bruta na quebra de senhas.\n");
    printf("O tempo de processamento depende da complexidade e tamanho da senha.\n");
    
    printf("\n==== ENTRADA DE DADOS ====\n");

    if (!ler_senha_alvo()) return 1;

    printf("\nDigite o nome do arquivo com dados do alvo (extensao .txt): ");
    if (!fgets(nomeArquivoBase, sizeof(nomeArquivoBase), stdin)) {
        printf("[ERRO] Falha ao ler nome do arquivo base.\n");
        return 1;
    }
    remover_quebra_linha(nomeArquivoBase);
    char **dados_alvo = ler_arquivo_para_array(nomeArquivoBase, &qtdPalavrasBase, 0);
    if (dados_alvo == NULL) {
        return 1;
    }

    printf("\nInforme o tamanho maximo de senha: ");
    scanf(" %d", &tamMaxSenha);
    if(tamMaxSenha <= 1) tamMaxSenha = tamMaxSenha;

    printf("\nDigite a quantidade de threads: ");
    scanf(" %d", &numero_threads);

    if(numero_threads > NUMERO_DE_THREADS){
        numero_threads = numero_threads;
    }else{
        numero_threads = NUMERO_DE_THREADS;
    }

    printf("\n========================\n");

    /* Chama a função de força bruta para descobrir a senha alvo */
    clock_t tempo_inicio = clock();

    char *senhaEncontrada = forca_bruta(dados_alvo, qtdPalavrasBase, &tentativas, numero_threads);

    clock_t tempo_fim = clock();
    double tempo_gasto = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
    
    if (senhaEncontrada != NULL) {
        printf("\n[RESULTADO] Senha quebrada: '%s' com %ld tentativas.\nMais sorte na proxima vez.\n\n", senhaEncontrada, tentativas);
        free(senhaEncontrada);
    } else {
        printf("\n[RESULTADO] Nao foi possivel quebrar a senha com %ld tentativas.\nVoce eh uma pessoa de sorte.\n\n", tentativas);
    }

    printf("Tempo total de execucao: %.3f segundos\n", tempo_gasto);

    liberar_array_strings(dados_alvo, qtdPalavrasBase);

    return 0;
}