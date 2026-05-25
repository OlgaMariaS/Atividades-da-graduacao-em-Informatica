#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <pthread.h>

#define TAMANHO 6 // Tamanho máximo da senha (utilizado para limitar a complexidade evitando longos períodos de processamento)
#define NUMERO_DE_THREADS 2 // Números de threads é no minino duas se não o comportamente seria como o sequencial
#define MAX_MUTACOES 1000
#define MAX_LINHA 512
#define NOME_DICIONARIO "rockyou.txt"

int tamanho;
char alvo[TAMANHO + 1];

/* ESTRUTURAS PARA PARALELIZAÇÃO */
typedef struct {
    int inicio;
    int fim;
    const char *palavra;
    char (*resultados)[TAMANHO + 1];
} DadosMutacaoData;

typedef struct {
    int inicio;
    int fim;
    long thread_id;
    long tentativas_locais;
    char **palavras;       // Ponteiro para o dicionário na memória
    char **senha_achada;   // Ponteiro para a variável local da função de controle
} DadosThreadDicionario;

typedef struct {
    long long inicio;
    long long fim;
    long thread_id;
    long tentativas_locais;
    char **senha_achada; // Ponteiro para a variável local da função de controle
} DadosThread;
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
/* FUNÇÕES DO ATAQUE POR MUTAÇÕES */
/*
 * Gera mutações por substituiçao.
 * a->4 ou @, e->3, o->0, i->1, s->5, t->7
 */
int mutacao_substituicao(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;
    int len = (int)strlen(palavra);

    for (int i = 0; i < len && total < maxResultados; i++) {
        // copia da palavra original
        char nova[TAMANHO + 1];
        strncpy(nova, palavra, TAMANHO);
        nova[TAMANHO] = '\0';

        // pega somente um caracter minusculo da palavra
        char c = (char)tolower((unsigned char)nova[i]);

        if (c == 'a') {
            nova[i] = '4';
            strcpy(resultados[total], nova);
            total++;

            if (total < maxResultados) {
                strncpy(nova, palavra, TAMANHO);
                nova[TAMANHO] = '\0';
                nova[i] = '@';
                strcpy(resultados[total], nova);
                total++;
            }
        } else if (c == 'e') {
            nova[i] = '3';
            strcpy(resultados[total], nova);
            total++;
        } else if (c == 'i') {
            nova[i] = '1';
            strcpy(resultados[total], nova);
            total++;
        } else if (c == 'o') {
            nova[i] = '0';
            strcpy(resultados[total], nova);
            total++;
        } else if (c == 's') {
            nova[i] = '5';
            strcpy(resultados[total], nova);
            total++;
        } else if (c == 't') {
            nova[i] = '7';
            strcpy(resultados[total], nova);
            total++;
        }
    }

    return total;
}

/*
 * Gera mutações por sufixo respeitando o tamanho máximo da senha.
 * nome -> nome123, nomenom, nomeeee, nomeee1
 */
int mutacao_sufixo(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;
    int tamanhoBase = (int)strlen(palavra);
    int max_repeti_ult_letra = 3;

    // se o tamanho da palavra ja é o máximo, não é possível adicionar sufixo
    if (tamanhoBase >= TAMANHO) return 0;
    // palavra vazia
    if (tamanhoBase == 0) return 0;

    char ultimo = palavra[tamanhoBase - 1];
    int espacoLivre = TAMANHO - tamanhoBase;

    for (int i = 0; i <= max_repeti_ult_letra && i <= espacoLivre && total < maxResultados; i++) {
        char prefixo[TAMANHO + 1];
        strcpy(prefixo, palavra);

        for (int r = 0; r < i; r++) {
            int len = (int)strlen(prefixo);
            prefixo[len] = ultimo;
            prefixo[len + 1] = '\0';
        }

        if (i > 0) {
            strcpy(resultados[total], prefixo);
            total++;
            if (total >= maxResultados) break;
        }
        
        // Criar sufixos com números sendo o máximo a quantidade de espaço livre
        // ex: nome até TAMANHO(7) sobra 3 resulta em: nome100, nome101, ..., nome999
        int espacoNumeros = TAMANHO - (int)strlen(prefixo);
        if (espacoNumeros <= 0) continue;

        int limite = potencia10(espacoNumeros) - 1;

        for (int n = 1; n <= limite && total < maxResultados; n++) {
            char candidato[TAMANHO + 1];
            snprintf(candidato, sizeof(candidato), "%s%d", prefixo, n);
            candidato[TAMANHO] = '\0';

            if ((int)strlen(candidato) <= TAMANHO) {
                strcpy(resultados[total], candidato);
                total++;
            }
        }
    }

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
            snprintf(dados->resultados[k], TAMANHO + 1, "%s%02d", dados->palavra, k + 1);
        } else if (k < 43) {
            // Súfixo Dia (12 a 42)
            snprintf(dados->resultados[k], TAMANHO + 1, "%s%02d", dados->palavra, k - 12 + 1);
        } else if (k < 55) {
            // Prefixo Mês (43 a 54)
            snprintf(dados->resultados[k], TAMANHO + 1, "%02d%s", k - 43 + 1, dados->palavra);
        } else {
            // Prefixo Dia (55 a 85)
            snprintf(dados->resultados[k], TAMANHO + 1, "%02d%s", k - 55 + 1, dados->palavra);
        }
    }
    pthread_exit(NULL);
}

/*
 * Gera mutações com datas
 * Se a palavra for um ano, gera mutações de data compatíveis com TAMANHO.
 * YYYY -> YYYYMMD, DDMYYYY, YYYYMDD
 */
int mutacao_data(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados, int num_threads) {
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
 * Gera mutações concatendo de duas formas as palavras do input.
 * nome + teste = nometes, tesnome
 */
int mutacao_concatenar_termos(const char *palavra, char **listaPalavras, int qtdPalavras, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;

    for (int i = 0; i < qtdPalavras && total < maxResultados; i++) {
        char temp1[2 * TAMANHO + 10];
        char temp2[2 * TAMANHO + 10];

        snprintf(temp1, sizeof(temp1), "%s%s", palavra, listaPalavras[i]);
        snprintf(temp2, sizeof(temp2), "%s%s", listaPalavras[i], palavra);

        strncpy(resultados[total], temp1, TAMANHO);
        resultados[total][TAMANHO] = '\0';
        total++;

        if (total < maxResultados) {
            strncpy(resultados[total], temp2, TAMANHO);
            resultados[total][TAMANHO] = '\0';
            total++;
        }
    }

    return total;
}

/*
 * Aplica 3 métodos de mutações em todas as palavras do array de input.
 * Compara se as mutações geradas são iguais a senha alvo. 
 */
char *ataque_por_mutacoes(char **array, int qtdPalavras, long *tentativas, int num_threads) {
    printf("[ETAPA 1] Iniciando ataque por mutacoes\n\n");

    for (int i = 0; i < qtdPalavras; i++) {

        char resultados[MAX_MUTACOES][TAMANHO + 1];
        int qtd = 0;

        qtd = mutacao_substituicao(array[i], resultados, MAX_MUTACOES);
        for (int j = 0; j < qtd; j++) {
            (*tentativas)++;
            if (comparar_candidato(resultados[j])) {
                return duplicar_string(resultados[j]);
            }
        }

        qtd = mutacao_sufixo(array[i], resultados, MAX_MUTACOES);
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

        qtd = mutacao_concatenar_termos(array[i], array, qtdPalavras, resultados, MAX_MUTACOES);
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
 * Aplica um filtro e testa somente as palavras com tamanho igual a TAMANHO.
 */
char *ataque_por_dicionario(long *tentativas, int num_threads) {
    printf("[ETAPA 2] Iniciando o ataque por dicionario PARALELO com %d threads\n\n", num_threads);

    int qtd = 0;
    char **palavras = ler_arquivo_para_array(NOME_DICIONARIO, &qtd, TAMANHO);
    if (palavras == NULL) return NULL;

    printf("Total de palavras filtradas com tamanho %d: %d\n", TAMANHO, qtd);

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
 * Ataque usando apenas números com exatamente TAMANHO dígitos.
 * Para TAMANHO=7, vai de 1000000 ate 9999999.
 */
void *rotina_ataque_numerico(void *arg) {
    DadosThread *dados = (DadosThread *)arg;
    char tentativa[TAMANHO + 1];

    for (long long i = dados->inicio; i < dados->fim; i++) {
        if (*(dados->senha_achada) != NULL) pthread_exit(NULL);

        sprintf(tentativa, "%0*lld", TAMANHO, i);

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
 * Ataque usando apenas números com exatamente TAMANHO dígitos.
 * Para TAMANHO=7, vai de 1000000 ate 9999999.
 */
char *ataque_numerico(long *tentativas, int num_threads) {
    long long inicio_total = potencia10(TAMANHO - 1);
    long long fim_total = potencia10(TAMANHO);
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
    // Configuraçao para 
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
    scanf(" %d", &tamanho);

    if(tamanho <= 1) tamanho = TAMANHO;

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