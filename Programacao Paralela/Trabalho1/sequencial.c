#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#define TAMANHO 12
#define MAX_MUTACOES 1000
#define MAX_LINHA 512
#define NOME_DICIONARIO "rockyou.txt"

char alvo[TAMANHO + 1];

/*
 * Remove quebra de linha e espaço do final da string.
 */
void remover_quebra_linha(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
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
 * Gera mutações com datas
 * Se a palavra for um ano, gera mutações de data compatíveis com TAMANHO.
 * YYYY -> YYYYMMD, DDMYYYY, YYYYMDD
 */
int mutacao_data(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;

    if (!eh_ano(palavra)) return 0;
    
    for (int mes = 1; mes <= 12 && total < maxResultados; mes++) {
        snprintf(resultados[total], TAMANHO + 1, "%s%02d", palavra, mes);
        total++;
    }

    for (int dia = 1; dia <= 31 && total < maxResultados; dia++) {
        snprintf(resultados[total], TAMANHO + 1, "%s%02d", palavra, dia);
        total++;
    }

    for (int mes = 1; mes <= 12 && total < maxResultados; mes++) {
        snprintf(resultados[total], TAMANHO + 1, "%02d%s", mes, palavra);
        total++;
    }

    for (int dia = 1; dia <= 31 && total < maxResultados; dia++) {
        snprintf(resultados[total], TAMANHO + 1, "%02d%s", dia, palavra);
        total++;
    }

    return total;
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
char *ataque_por_mutacoes(char **array, int qtdPalavras, long *tentativas) {
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

        qtd = mutacao_data(array[i], resultados, MAX_MUTACOES);
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

/*
 * Ataque de força bruta usando o dicionário rockyou.
 * Aplica um filtro e testa somente as palavras com tamanho igual a TAMANHO.
 */
char *ataque_por_dicionario(long *tentativas) {
    printf("[ETAPA 2] Iniciando o ataque por dicionario\n\n");

    int qtd = 0;
    char **palavras = ler_arquivo_para_array(NOME_DICIONARIO, &qtd, TAMANHO);
    if (palavras == NULL) {
        return NULL;
    }

    printf("Total de palavras filtradas com tamanho %d: %d\n", TAMANHO, qtd);

    for (int i = 0; i < qtd; i++) {
        (*tentativas)++;

        if (i > 0 && i % 1000000 == 0) {
            printf("[PROGRESSO] Dicionario: %d milhoes de palavras testadas.\n", i / 1000000);
        }

        if (strcmp(palavras[i], alvo) == 0) {
            char *resultado = duplicar_string(palavras[i]);
            liberar_array_strings(palavras, qtd);
            return resultado;
        }
    }
    printf("==============================\n");
    liberar_array_strings(palavras, qtd);
    return NULL;
}

/*
 * Ataque usando apenas números com exatamente TAMANHO dígitos.
 * Para TAMANHO=7, vai de 1000000 ate 9999999.
 */
char *ataque_numerico(long *tentativas) {
    char tentativa[TAMANHO + 1];
    long long inicio = potencia10(TAMANHO - 1);
    long long fim = potencia10(TAMANHO);

    printf("\n [ETAPA 3] Iniciando ataque numerico\n");
    printf("O progresso sera atualizado a cada 1 milhao de testes...\n\n");

    for (long long i = inicio; i < fim; i++) {
        // Formata com zeros à esquerda caso necessário.
        sprintf(tentativa, "%0*lld", TAMANHO, i);

        if (i % 1000000 == 0)
            printf("[PROGRESSO] %lld milhoes de numeros testados...\n", i / 1000000);

        (*tentativas)++;

        if (strcmp(tentativa, alvo) == 0)
            return duplicar_string(tentativa);
    }
    printf("==============================\n");
    return NULL;
}

/*
 * Orquestra tudo. 
 * Tenta quebrar a senha do método mais provavél para o mais exaustivo.
 */
char *forca_bruta(char **arrayBase, int qtdPalavrasBase, long *tentativas) {
    *tentativas = 0;

    char *encontrada = ataque_por_mutacoes(arrayBase, qtdPalavrasBase, tentativas);
    if (encontrada != NULL) return encontrada;

    encontrada = ataque_por_dicionario(tentativas);
    if (encontrada != NULL) return encontrada;

    encontrada = ataque_numerico(tentativas);
    if (encontrada != NULL) return encontrada;

    return NULL;
}

/*
 * Lê a senha alvo e faz validações sobre a quantidade de caracteres.
 */
int ler_senha_alvo(void) {
    char buffer[256];

    printf("Digite a senha alvo (exatamente %d caracteres): ", TAMANHO);
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

int main() {
    // Configuraçao para 
    setlocale(LC_ALL, "");

    char nomeArquivoBase[256];
    int qtdPalavrasBase = 0;
    long tentativas = 0;

    printf("\nEste e um programa SEQUENCIAL para simular um ataque de forca bruta na quebra de senhas.\n");
    printf("O tempo de processamento depende da complexidade da senha.\n");
    printf("Tamanho de senha suportado eh de %d caracteres.\n", TAMANHO);
    
    printf("\n=== ENTRADA DE DADOS ===\n");
    if (!ler_senha_alvo()) {
        return 1;
    }
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
    printf("\n========================\n");

    /* Chama a função de força bruta para descobrir a senha alvo */
    clock_t tempo_inicio = clock();

    char *senhaEncontrada = forca_bruta(dados_alvo, qtdPalavrasBase, &tentativas);

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