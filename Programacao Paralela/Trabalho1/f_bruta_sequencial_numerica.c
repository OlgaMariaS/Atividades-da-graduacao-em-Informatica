#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_SENHA 10
#define MAX_COMBINACOES 10000000000 // 10^8 (100 milhões)

// ==========================================
// FUNÇÃO: FORÇA BRUTA NUMÉRICA SEQUENCIAL
// ==========================================
int forca_bruta_numerica_sequencial(const char *senha_alvo, char *senha_encontrada) {
    char tentativa[TAMANHO_SENHA + 1]; 
    
    printf("\n[SISTEMA] Iniciando busca sequencial de %d possibilidades...\n", MAX_COMBINACOES);
    printf("[SISTEMA] Aguarde... O progresso sera atualizado a cada 10 milhoes de testes.\n\n");

    for (long long i = 0; i < MAX_COMBINACOES; i++) {
        
        // Formata o número 'i' para ter 8 casas, preenchendo com zeros
        sprintf(tentativa, "%10lld", i);
        
        // ==========================================
        // CONTROLE DE PROGRESSO (HEARTBEAT)
        // ==========================================
        // Só entra neste 'if' a cada 10.000.000 de iterações.
        // O 'i > 0' evita que ele printe a mensagem logo no zero.
        if (i > 0 && i % 10000000 == 0) {
            printf("[PROGRESSO] %lld milhoes de senhas testadas... (CPU trabalhando)\n", i / 1000000);
        }

        // Comparação direta com a senha alvo
        if (strcmp(tentativa, senha_alvo) == 0) {
            strcpy(senha_encontrada, tentativa);
            return 1; // Encontrou a senha!
        }
    }
    
    return 0; // Testou as 100 milhões e não encontrou
}
// ==========================================
// FUNÇÃO MAIN
// ==========================================
int main() {
    char senha_alvo[TAMANHO_SENHA + 1];
    char senha_resolvida[TAMANHO_SENHA + 1] = "";

    // Título da Aplicação
    printf("====================================================\n");
    printf("      SIMULADOR DE FORCA BRUTA NUMERICA (V1)        \n");
    printf("====================================================\n\n");

    // Coleta da senha com validação restrita a 8 dígitos
    printf("=== ENTRADA DE DADOS: O ALVO ===\n");
    do {
        printf("Digite a senha alvo (DEVE conter exatamente 10 digitos numericos):\n");
        scanf(" %10s", senha_alvo); // O %8s limita a leitura a 8 caracteres
        
        // Limpeza do buffer do teclado para evitar loops infinitos
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if (strlen(senha_alvo) != TAMANHO_SENHA) {
            printf("[ERRO] Tamanho invalido! A senha digitada possui %lu caracteres.\n\n", strlen(senha_alvo));
        }
    } while (strlen(senha_alvo) != TAMANHO_SENHA);

    // ==========================================
    // EXECUÇÃO E MEDIÇÃO DE TEMPO
    // ==========================================
    printf("\n=== INICIANDO EXECUCAO SEQUENCIAL ===\n");
    
    // Inicia o cronômetro
    clock_t tempo_inicio = clock();
    
    // Chama a lógica de força bruta
    int encontrou = forca_bruta_numerica_sequencial(senha_alvo, senha_resolvida);
    
    // Para o cronômetro
    clock_t tempo_fim = clock();
    double tempo_gasto = (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
    
    printf("\n====================================================\n");
    if (encontrou) {
        printf("[SUCESSO] Senha Encontrada: '%s'\n", senha_resolvida);
    } else {
        printf("[FALHA] Senha nao encontrada no espaco de busca.\n");
    }
    
    printf("Tempo total de execucao: %f segundos\n", tempo_gasto);
    printf("====================================================\n");

    return 0;
}