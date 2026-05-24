#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#define TAMANHO 7
#define MAX_MUTACOES 1000
#define MAX_LINHA 512

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
 * Verifica se a string tem exatamente 4 dígitos e parece um ano razoável.
 */
int eh_ano(const char *str) {
    if (!eh_numero(str)) return 0;
    if (strlen(str) != 4) return 0;

    int ano = atoi(str);
    return (ano >= 1900 && ano <= 2099);
}

/*
 * Potência inteira simples: base^exp
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
 * Lê um arquivo pequeno/base e guarda em array dinâmico.
 * Use para o arquivo de entrada com poucas palavras.
 */
char **ler_arquivo_para_array(const char *nomeArquivo, int *quantidade) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("[ERRO] Não foi possível abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    printf("[DEBUG] Arquivo base '%s' aberto com sucesso.\n", nomeArquivo);

    char linha[MAX_LINHA];
    char **array = NULL;
    int count = 0;

    while (fgets(linha, sizeof(linha), fp) != NULL) {
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

    fclose(fp);
    *quantidade = count;
    printf("[DEBUG] Total de palavras base lidas: %d\n", count);

    return array;
}

/*
 * Gera mutações por substituição:
 * a -> 4 ou @
 * e -> 3
 * i -> 1
 * o -> 0
 * s -> 5
 * t -> 7
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
 * Gera mutações por sufixo:
 * 1) repete a última letra até no máximo 3 vezes;
 * 2) adiciona números enquanto couber;
 * 3) combina repetição (0..3) + números enquanto couber.
 *
 * Exemplo para "nome" (faltam 3 posições):
 * nomee, nomeee, nomeeee
 * nome1 ... nome999
 * nomee1 ... nomee99
 * nomeee1 ... nomeee9
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
 * Se a palavra for um ano (4 dígitos), gera mutações de data.
 * Como TAMANHO=7, não cabe YYYYMMDD.
 * Então tentamos formatos compatíveis com 7:
 * YYYYMM (ex: 200012)
 * YYYYDD (ex: 200031)
 * MMYYYY (ex: 012000)
 * DDYYYY (ex: 312000)
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
 * Gera mutações concatenando a palavra atual com cada item do array base.
 * Exemplo:
 * nome + teste => nometes
 * teste + nome => tesnome
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
 * Aplica as mutações nas palavras do array base.
 * Cada grupo gerado é testado logo em seguida.
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
 * Dicionário em streaming.
 * Lê linha a linha, filtra por tamanho <= TAMANHO e compara imediatamente.
 * Isso é apropriado para arquivos muito grandes, como rockyou.
 */
char *testar_dicionario_stream(const char *nomeDicionario, long *tentativas) {
    FILE *fp = fopen(nomeDicionario, "r");
    if (fp == NULL) {
        printf("[ERRO] Não foi possível abrir o dicionário: %s\n", nomeDicionario);
        return NULL;
    }

    printf("\n[DEBUG] ===== Iniciando teste no dicionário '%s' =====\n", nomeDicionario);

    char linha[MAX_LINHA];
    long linhaAtual = 0;

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        linhaAtual++;
        remover_quebra_linha(linha);

        if (linha[0] == '\0') continue;
        if ((int)strlen(linha) > TAMANHO) continue;

        (*tentativas)++;

        if (linhaAtual % 1000000 == 0) {
            printf("[DEBUG] Dicionário: %ld linhas processadas, %ld tentativas acumuladas.\n",
                   linhaAtual, *tentativas);
        }

        if (comparar_candidato(linha)) {
            fclose(fp);
            return duplicar_string(linha);
        }
    }

    fclose(fp);
    return NULL;
}

/*
 * Gera números em fluxo, sem guardar tudo em memória.
 * Para cada quantidade de dígitos de 1 até TAMANHO:
 * 1 dígito: 1..9
 * 2 dígitos: 01..99
 * ...
 * 7 dígitos: 0000001..9999999
 */
char *testar_numeros_stream(long *tentativas) {
    printf("\n[DEBUG] ===== Iniciando teste numérico =====\n");

    for (int digitos = 1; digitos <= TAMANHO; digitos++) {
        int inicio = 1;
        int fim = potencia10(digitos) - 1;

        printf("[DEBUG] Testando números com %d dígito(s): de ", digitos);

        if (digitos == 1) {
            printf("1 até %d\n", fim);
        } else {
            printf("%0*d até %0*d\n", digitos, 1, digitos, fim);
        }

        for (int n = inicio; n <= fim; n++) {
            char candidato[TAMANHO + 1];
            snprintf(candidato, sizeof(candidato), "%0*d", digitos, n);

            (*tentativas)++;

            if (n % 1000000 == 0) {
                printf("[DEBUG] Numéricos: %d dígitos, valor atual %0*d, tentativas=%ld\n",
                       digitos, digitos, n, *tentativas);
            }

            if (comparar_candidato(candidato)) {
                return duplicar_string(candidato);
            }
        }
    }

    return NULL;
}

/*
 * Orquestra o processo completo:
 * 1) mutações sobre o array base;
 * 2) dicionário grande;
 * 3) números.
 */
char *descobre_palavra(char **arrayBase, int qtdPalavrasBase, const char *nomeDicionario, long *tentativas) {
    *tentativas = 0;

    char *encontrada = testar_mutacoes_array(arrayBase, qtdPalavrasBase, tentativas);
    if (encontrada != NULL) {
        return encontrada;
    }

    // encontrada = testar_dicionario_stream(nomeDicionario, tentativas);
    // if (encontrada != NULL) {
    //     return encontrada;
    // }

    encontrada = testar_numeros_stream(tentativas);
    if (encontrada != NULL) {
        return encontrada;
    }

    return NULL;
}

/*
 * Libera toda memória do array de strings.
 */
void liberar_array_strings(char **array, int qtd) {
    if (array == NULL) return;

    for (int i = 0; i < qtd; i++) {
        free(array[i]);
    }
    free(array);
}

int main() {
    /*
     * Usa a locale padrão do sistema.
     * Isso tende a funcionar melhor para acentuação do que fixar "Portuguese".
     */
    setlocale(LC_ALL, "");

    char nomeArquivoBase[256];
    char nomeDicionario[256];
    int qtdPalavrasBase = 0;
    long tentativas = 0;

    printf("Este é um programa SEQUENCIAL para simular um ataque de força bruta na quebra de senhas.\n");
    printf("O tempo de processamento depende da complexidade da senha.\n");
    printf("Tamanho máximo de senha suportado: %d caracteres.\n", TAMANHO);

    printf("\nDigite o nome do arquivo base (com extensão .txt): ");
    fgets(nomeArquivoBase, sizeof(nomeArquivoBase), stdin);
    remover_quebra_linha(nomeArquivoBase);

    printf("Digite o nome do dicionário grande (ex: rockyou.txt): ");
    fgets(nomeDicionario, sizeof(nomeDicionario), stdin);
    remover_quebra_linha(nomeDicionario);

    printf("Digite a senha alvo: ");
    scanf("%7s", alvo);

    char **entrada = ler_arquivo_para_array(nomeArquivoBase, &qtdPalavrasBase);
    if (entrada == NULL) {
        return 1;
    }

    clock_t tempo_inicio = clock();

    char *palavraEncontrada = descobre_palavra(entrada, qtdPalavrasBase, nomeDicionario, &tentativas);

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