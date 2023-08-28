#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_OPERACAO 2
#define TAM_CAMPOS 100
#define QUEBRA_DE_LINHA '\n'

typedef struct {
    int id;
    char titulo[TAM_CAMPOS];
    char ano[TAM_CAMPOS];
    char genero[TAM_CAMPOS];
    char produtora[TAM_CAMPOS];
    char plataforma[TAM_CAMPOS];
} Jogo;

// Funções de busca e inserção
void buscar(FILE *arquivo, int chave) {
    Jogo jogo;
    while (fread(&jogo, sizeof(Jogo), 1, arquivo) == 1) {
        if (jogo.id == chave) {
            printf("Jogo encontrado:\n");
            printf("ID: %d\nTítulo: %s\nAno: %s\nGênero: %s\nProdutora: %s\nPlataforma: %s\n",
                   jogo.id, jogo.titulo, jogo.ano, jogo.genero, jogo.produtora, jogo.plataforma);
            return;
        }
    }
    printf("Jogo com ID %d não encontrado.\n", chave);
}

void inserir(FILE *arquivo, int id, const char *titulo, const char *ano, const char *genero, const char *produtora, const char *plataforma) {
    Jogo novoJogo;
    novoJogo.id = id;
    strcpy(novoJogo.titulo, titulo);
    strcpy(novoJogo.ano, ano);
    strcpy(novoJogo.genero, genero);
    strcpy(novoJogo.produtora, produtora);
    strcpy(novoJogo.plataforma, plataforma);

    fwrite(&novoJogo, sizeof(Jogo), 1, arquivo);
    printf("Novo jogo inserido:\n");
    printf("ID: %d\nTítulo: %s\nAno: %s\nGênero: %s\nProdutora: %s\nPlataforma: %s\n",
           novoJogo.id, novoJogo.titulo, novoJogo.ano, novoJogo.genero, novoJogo.produtora, novoJogo.plataforma);
}

int main() {
    // Resto do código da função main

    // Exemplo de uso das funções buscar e inserir
    //buscar(arquivo, 22);

    //inserir(arquivo, 147, "Resident Evil 2", "1998", "Survival horror", "Capcom", "PlayStation");

}
