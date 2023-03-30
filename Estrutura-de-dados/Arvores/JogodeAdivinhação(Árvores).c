#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da árvore binária
typedef struct no {
    char* pergunta;
    struct no* sim;
    struct no* nao;
} No;

// Função para criar um novo nó com a pergunta informada
No* criarNo(char* pergunta) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->pergunta = (char*) malloc((strlen(pergunta) + 1) * sizeof(char));
    strcpy(novoNo->pergunta, pergunta);
    novoNo->sim = NULL;
    novoNo->nao = NULL;
    return novoNo;
}

// Função para percorrer a árvore e fazer as perguntas ao usuário
void fazerPerguntas(No* noAtual) {
    char resposta;
    if (noAtual->sim == NULL && noAtual->nao == NULL) { // Chegou a uma folha da árvore, ou seja, encontrou o animal
        printf("O animal que voce pensou eh: %s\n", noAtual->pergunta);
        printf("Eu acertei? (s/n) ");
        scanf(" %c", &resposta);
        if (resposta == 's') {
            printf("Oba! Sou o mestre da adivinhacao :).\n\n");
        } else {
            printf("Ah, que pena! Vamos tentar de novo.\n\n");
            char* novoAnimal = (char*) malloc(50 * sizeof(char));
            printf("Qual animal voce pensou? ");
            scanf(" %[^\n]", novoAnimal);
            char* novaPergunta = (char*) malloc(50 * sizeof(char));
            printf("O que diferencia um(a) %s de um(a) %s? ", novoAnimal, noAtual->pergunta);
            scanf(" %[^\n]", novaPergunta);
            printf("Vlw por informar!.\n\n");
            // Cria um novo nó com a nova pergunta e liga com o nó atual e o nó que representa o novo animal
            No* novoNo = criarNo(novaPergunta);
            novoNo->nao = noAtual;
            novoNo->sim = criarNo(novoAnimal);
            *noAtual = *novoNo;
            free(novoNo);
            printf("O animal que voce pensou possui essa caracteristica: ");
            fazerPerguntas(noAtual);
        }
    } else {
        printf("%s (s/n) ", noAtual->pergunta);
        scanf(" %c", &resposta);
        if (resposta == 's') {
            fazerPerguntas(noAtual->sim);
        } else {
            fazerPerguntas(noAtual->nao);
        }
    }
}

int main() {
    printf("Vamos jogar um jogo!\n");
    printf("Pense em um animal e eu vou tentar adivinhar qual eh.\n");
    printf("As perguntas que eu fizer so podem ser respondidas com s (sim) ou n (nao).\n\n");
    // Cria a árvore com a primeira pergunta

    No* raiz = criarNo("O animal que voce pensou tem pelos?");
    raiz->nao = criarNo("papagaio");
    raiz->sim = criarNo("cachorro");
    fazerPerguntas(raiz);
    return 0;
}
