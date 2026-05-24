#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define TAMANHO 7
#define MAX_MUTACOES 1000
#define MAX_LINHA 512
#define NOME_DICIONARIO "rockyou.txt"

char alvo[TAMANHO + 1];

/*
 * Remove '\n' e '\r' do final da string.
 */
void remover_quebra_linha(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

/*
 * Duplica uma string em memória dinâmica.
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
 * Verifica se a string contém apenas dígitos.
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
 * Compara um candidato com a palavra alvo.
 */
int comparar_candidato(const char *candidato) {
    printf("[DEBUG] Comparando candidato '%s' com alvo '%s'\n", candidato, alvo);

    if (strcmp(candidato, alvo) == 0) {
        printf("[DEBUG] >>> ENCONTRADO! '%s' é igual ao alvo.\n", candidato);
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
char **ler_arquivo_para_array(const char *nomeArquivo, int *quantidade) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("[ERRO] Não foi possível abrir o arquivo base: %s\n", nomeArquivo);
        return NULL;
    }

    printf("[DEBUG] Arquivo base '%s' aberto com sucesso.\n", nomeArquivo);

    char linha[MAX_LINHA];
    char **array = NULL;
    int count = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        remover_quebra_linha(linha);

        if (strlen(linha) == 0) {
            printf("[DEBUG] Linha vazia ignorada.\n");
            continue;
        }

        if ((int)strlen(linha) > TAMANHO) {
            printf("[DEBUG] Palavra '%s' ignorada por ultrapassar TAMANHO=%d.\n", linha, TAMANHO);
            continue;
        }

        char **novo = (char **)realloc(array, (count + 1) * sizeof(char *));
        if (novo == NULL) {
            printf("[ERRO] Falha no realloc do array de strings.\n");
            fclose(fp);
            free(array);
            exit(1);
        }
        array = novo;

        array[count] = duplicar_string(linha);
        printf("[DEBUG] Palavra lida[%d] = '%s'\n", count, array[count]);
        count++;
    }

    if (ferror(fp)) {
        printf("[ERRO] Erro durante leitura do arquivo base.\n");
        fclose(fp);
        liberar_array_strings(array, count);
        return NULL;
    }

    fclose(fp);
    *quantidade = count;
    printf("[DEBUG] Total de palavras base lidas: %d\n", count);

    return array;
}

/*
 * Gera mutações por substituição.
 */
int mutacao_substituicao(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;
    int len = (int)strlen(palavra);

    printf("[DEBUG] mutacao_substituicao() para '%s'\n", palavra);

    for (int i = 0; i < len && total < maxResultados; i++) {
        char nova[TAMANHO + 1];
        strncpy(nova, palavra, TAMANHO);
        nova[TAMANHO] = '\0';

        char c = (char)tolower((unsigned char)nova[i]);

        if (c == 'a') {
            nova[i] = '4';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;

            if (total < maxResultados) {
                strncpy(nova, palavra, TAMANHO);
                nova[TAMANHO] = '\0';
                nova[i] = '@';
                strcpy(resultados[total], nova);
                printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
                total++;
            }
        } else if (c == 'e') {
            nova[i] = '3';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        } else if (c == 'i') {
            nova[i] = '1';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        } else if (c == 'o') {
            nova[i] = '0';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        } else if (c == 's') {
            nova[i] = '5';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        } else if (c == 't') {
            nova[i] = '7';
            strcpy(resultados[total], nova);
            printf("[DEBUG] Substituição gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        }
    }

    return total;
}

/*
 * Gera mutações por sufixo.
 */
int mutacao_sufixo(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;
    int tamanhoBase = (int)strlen(palavra);

    printf("[DEBUG] mutacao_sufixo() para '%s'\n", palavra);

    if (tamanhoBase >= TAMANHO) {
        printf("[DEBUG] Palavra já está no tamanho máximo. Nenhum sufixo gerado.\n");
        return 0;
    }

    if (tamanhoBase == 0) return 0;

    char ultimo = palavra[tamanhoBase - 1];
    int espacoLivre = TAMANHO - tamanhoBase;

    for (int repeticoes = 0; repeticoes <= 3 && repeticoes <= espacoLivre && total < maxResultados; repeticoes++) {
        char prefixo[TAMANHO + 1];
        strcpy(prefixo, palavra);

        for (int r = 0; r < repeticoes; r++) {
            int len = (int)strlen(prefixo);
            prefixo[len] = ultimo;
            prefixo[len + 1] = '\0';
        }

        if (repeticoes > 0) {
            strcpy(resultados[total], prefixo);
            printf("[DEBUG] Sufixo repetição gerado[%d] = '%s'\n", total, resultados[total]);
            total++;
            if (total >= maxResultados) break;
        }

        int espacoNumeros = TAMANHO - (int)strlen(prefixo);
        if (espacoNumeros <= 0) continue;

        int limite = potencia10(espacoNumeros) - 1;

        for (int n = 1; n <= limite && total < maxResultados; n++) {
            char candidato[TAMANHO + 1];
            snprintf(candidato, sizeof(candidato), "%s%d", prefixo, n);
            candidato[TAMANHO] = '\0';

            if ((int)strlen(candidato) <= TAMANHO) {
                strcpy(resultados[total], candidato);
                printf("[DEBUG] Sufixo número gerado[%d] = '%s'\n", total, resultados[total]);
                total++;
            }
        }
    }

    return total;
}

/*
 * Se a palavra for um ano, gera mutações de data compatíveis com TAMANHO=7.
 */
int mutacao_data(const char *palavra, char resultados[][TAMANHO + 1], int maxResultados) {
    int total = 0;

    printf("[DEBUG] mutacao_data() para '%s'\n", palavra);

    if (!eh_ano(palavra)) {
        printf("[DEBUG] Palavra '%s' não parece um ano. Nenhuma mutação de data gerada.\n", palavra);
        return 0;
    }

    for (int mes = 1; mes <= 12 && total < maxResultados; mes++) {
        snprintf(resultados[total], TAMANHO + 1, "%s%02d", palavra, mes);
        printf("[DEBUG] Data ano+mês gerada[%d] = '%s'\n", total, resultados[total]);
        total++;
    }

    for (int dia = 1; dia <= 31 && total < maxResultados; dia++) {
        snprintf(resultados[total], TAMANHO + 1, "%s%02d", palavra, dia);
        printf("[DEBUG] Data ano+dia gerada[%d] = '%s'\n", total, resultados[total]);
        total++;
    }

    for (int mes = 1; mes <= 12 && total < maxResultados; mes++) {
        snprintf(resultados[total], TAMANHO + 1, "%02d%s", mes, palavra);
        printf("[DEBUG] Data mês+ano gerada[%d] = '%s'\n", total, resultados[total]);
        total++;
    }

    for (int dia = 1; dia <= 31 && total < maxResultados; dia++) {
        snprintf(resultados[total], TAMANHO + 1, "%02d%s", dia, palavra);
        printf("[DEBUG] Data dia+ano gerada[%d] = '%s'\n", total, resultados[total]);
        total++;
    }

    return total;
}

/*
 * Concatenação.
 */
int mutacao_concatenar_termos(
    const char *palavra,
    char **listaPalavras,
    int qtdPalavras,
    char resultados[][TAMANHO + 1],
    int maxResultados
) {
    int total = 0;

    printf("[DEBUG] mutacao_concatenar_termos() para '%s'\n", palavra);

    for (int i = 0; i < qtdPalavras && total < maxResultados; i++) {
        char temp1[2 * TAMANHO + 10];
        char temp2[2 * TAMANHO + 10];

        snprintf(temp1, sizeof(temp1), "%s%s", palavra, listaPalavras[i]);
        snprintf(temp2, sizeof(temp2), "%s%s", listaPalavras[i], palavra);

        strncpy(resultados[total], temp1, TAMANHO);
        resultados[total][TAMANHO] = '\0';
        printf("[DEBUG] Concat gerada[%d] = '%s'\n", total, resultados[total]);
        total++;

        if (total < maxResultados) {
            strncpy(resultados[total], temp2, TAMANHO);
            resultados[total][TAMANHO] = '\0';
            printf("[DEBUG] Concat gerada[%d] = '%s'\n", total, resultados[total]);
            total++;
        }
    }

    return total;
}

/*
 * Testa mutações do array base.
 */
char *testar_mutacoes_array(char **array, int qtdPalavras, long *tentativas) {
    for (int i = 0; i < qtdPalavras; i++) {
        printf("\n[DEBUG] ===== Testando palavra base '%s' =====\n", array[i]);

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

    return NULL;
}

/*
 * Dicionário em streaming usando nome fixo.
 */
char *testar_dicionario_stream(long *tentativas) {
    FILE *fp = fopen(NOME_DICIONARIO, "rb");
    if (fp == NULL) {
        printf("[ERRO] Não foi possível abrir o dicionário: %s\n", NOME_DICIONARIO);
        return NULL;
    }

    printf("\n[DEBUG] ===== Carregando dicionário inteiro em memória: '%s' =====\n", NOME_DICIONARIO);

    if (fseek(fp, 0, SEEK_END) != 0) {
        printf("[ERRO] Falha no fseek do dicionário.\n");
        fclose(fp);
        return NULL;
    }

    long tamanhoArquivo = ftell(fp);
    if (tamanhoArquivo < 0) {
        printf("[ERRO] Falha no ftell do dicionário.\n");
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char *buffer = (char *)malloc((size_t)tamanhoArquivo + 1);
    if (buffer == NULL) {
        printf("[ERRO] Memória insuficiente para carregar o dicionário.\n");
        fclose(fp);
        return NULL;
    }

    size_t bytesLidos = fread(buffer, 1, (size_t)tamanhoArquivo, fp);
    fclose(fp);

    buffer[bytesLidos] = '\0';

    printf("[DEBUG] Dicionário carregado em memória: %zu bytes.\n", bytesLidos);
    printf("[DEBUG] Iniciando parsing e filtro por tamanho %d...\n", TAMANHO);

    char **linhasFiltradas = NULL;
    long qtdFiltradas = 0;

    char *inicio = buffer;
    for (size_t i = 0; i <= bytesLidos; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\0') {
            buffer[i] = '\0';

            size_t len = strlen(inicio);
            if (len > 0 && inicio[len - 1] == '\r') {
                inicio[len - 1] = '\0';
                len--;
            }

            if ((int)len == TAMANHO) {
                char **novo = (char **)realloc(linhasFiltradas, (qtdFiltradas + 1) * sizeof(char *));
                if (novo == NULL) {
                    printf("[ERRO] Falha ao expandir lista filtrada do dicionário.\n");
                    free(linhasFiltradas);
                    free(buffer);
                    return NULL;
                }

                linhasFiltradas = novo;
                linhasFiltradas[qtdFiltradas] = inicio;
                qtdFiltradas++;
            }

            inicio = &buffer[i + 1];
        }
    }

    printf("[DEBUG] Total de palavras filtradas com tamanho %d: %ld\n", TAMANHO, qtdFiltradas);
    printf("[DEBUG] Iniciando comparação do dicionário filtrado...\n");

    for (long i = 0; i < qtdFiltradas; i++) {
        (*tentativas)++;

        if (i > 0 && i % 1000000 == 0) {
            printf("[PROGRESSO] Dicionário: %ld milhão(ões) de palavras testadas.\n", i / 1000000);
        }

        if (strcmp(linhasFiltradas[i], alvo) == 0) {
            char *resultado = duplicar_string(linhasFiltradas[i]);
            free(linhasFiltradas);
            free(buffer);
            return resultado;
        }
    }

    free(linhasFiltradas);
    free(buffer);
    return NULL;
}

/*
 * Testa apenas números com exatamente TAMANHO dígitos.
 * Para TAMANHO=7, vai de 1000000 até 9999999.
 */
char *testar_numeros_stream(long *tentativas) {
    char tentativa[TAMANHO + 1];
    long long inicio = potencia10(TAMANHO - 1);
    long long fim = potencia10(TAMANHO);

    printf("\n[SISTEMA] Iniciando busca numérica sequencial de %lld possibilidades...\n", fim - inicio);
    printf("[SISTEMA] Aguarde... O progresso será atualizado a cada 1 milhão de testes.\n\n");

    for (long long i = inicio; i < fim; i++) {
        /*
         * Formata com zeros à esquerda caso necessário.
         * Para TAMANHO=7, vai de 1000000 até 9999999.
         */
        sprintf(tentativa, "%0*lld", TAMANHO, i);

        if (i > inicio && i % 1000000 == 0) {
            printf("[PROGRESSO] %lld milhão(ões) de números testados...\n", i / 1000000);
        }

        (*tentativas)++;

        if (strcmp(tentativa, alvo) == 0) {
            return duplicar_string(tentativa);
        }
    }

    return NULL;
}

/*
 * Orquestra tudo.
 */
char *descobre_palavra(char **arrayBase, int qtdPalavrasBase, long *tentativas) {
    *tentativas = 0;

    char *encontrada = testar_mutacoes_array(arrayBase, qtdPalavrasBase, tentativas);
    if (encontrada != NULL) return encontrada;

    encontrada = testar_dicionario_stream(tentativas);
    if (encontrada != NULL) return encontrada;

    encontrada = testar_numeros_stream(tentativas);
    if (encontrada != NULL) return encontrada;

    return NULL;
}

/*
 * Lê o alvo e exige exatamente TAMANHO caracteres.
 */
int ler_alvo_valido(void) {
    char buffer[256];

    printf("Digite a senha alvo (exatamente %d caracteres): ", TAMANHO);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("[ERRO] Falha ao ler a senha alvo.\n");
        return 0;
    }

    remover_quebra_linha(buffer);

    if ((int)strlen(buffer) < TAMANHO) {
        printf("[ERRO] A senha alvo não pode ter menos de %d caracteres.\n", TAMANHO);
        return 0;
    }

    if ((int)strlen(buffer) > TAMANHO) {
        printf("[ERRO] A senha alvo não pode ter mais de %d caracteres.\n", TAMANHO);
        return 0;
    }

    strcpy(alvo, buffer);
    return 1;
}

int main() {
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    char nomeArquivoBase[256];
    int qtdPalavrasBase = 0;
    long tentativas = 0;

    printf("Este é um programa SEQUENCIAL para simular um ataque de força bruta na quebra de senhas.\n");
    printf("O tempo de processamento depende da complexidade da senha.\n");
    printf("Tamanho exato de senha suportado nesta versão: %d caracteres.\n", TAMANHO);
    printf("Dicionário configurado internamente: %s\n", NOME_DICIONARIO);

    printf("\nDigite o nome do arquivo base (com extensão .txt): ");
    if (!fgets(nomeArquivoBase, sizeof(nomeArquivoBase), stdin)) {
        printf("[ERRO] Falha ao ler nome do arquivo base.\n");
        return 1;
    }
    remover_quebra_linha(nomeArquivoBase);

    if (!ler_alvo_valido()) {
        return 1;
    }
    // printf("Digite a senha alvo: ");
    // scanf("%7s", alvo);

    char **entrada = ler_arquivo_para_array(nomeArquivoBase, &qtdPalavrasBase);
    if (entrada == NULL) {
        return 1;
    }

    clock_t tempo_inicio = clock();

    char *palavraEncontrada = descobre_palavra(entrada, qtdPalavrasBase, &tentativas);

    clock_t tempo_fim = clock();
    double tempo_gasto = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;

    if (palavraEncontrada != NULL) {
        printf("\n[RESULTADO] Palavra encontrada: '%s' com %ld tentativas.\n", palavraEncontrada, tentativas);
        free(palavraEncontrada);
    } else {
        printf("\n[RESULTADO] Não encontrado com %ld tentativas.\n", tentativas);
    }

    printf("Tempo gasto: %.3f segundos\n", tempo_gasto);

    liberar_array_strings(entrada, qtdPalavrasBase);

    return 0;
}