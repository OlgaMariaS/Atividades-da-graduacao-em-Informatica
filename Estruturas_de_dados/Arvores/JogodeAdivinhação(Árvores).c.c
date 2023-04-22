#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    novoNo->pergunta = (char*) malloc((strlen(pergunta) + 1) * sizeof(char));
    if (novoNo->pergunta == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strcpy(novoNo->pergunta, pergunta);
    novoNo->sim = NULL;
    novoNo->nao = NULL;
    return novoNo;
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArvore(raiz->sim); // Libera a subárvore "sim"
    liberarArvore(raiz->nao); // Libera a subárvore "nao"

    // Libera a memória alocada para a pergunta e o nó atual
    free(raiz->pergunta);
    free(raiz);
}

/*Essa abordagem utiliza uma chamada recursiva para percorrer a árvore de perguntas em pós-ordem,
ou seja, primeiro libera as subárvores "sim" e "nao" de cada nó antes de liberar o nó atual. */

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
            char novoAnimal[50];
            printf("Qual animal voce pensou? ");
            scanf(" %[^\n]", novoAnimal);
            char novaPergunta[50];
            printf("O que diferencia um(a) %s de um(a) %s? ", novoAnimal, noAtual->pergunta);
            scanf(" %[^\n]", novaPergunta);
            printf("Vlw por informar!\n\n");
            
            // Cria um novo nó com a nova pergunta e liga com o nó atual e o nó que representa o novo animal
            No* novoNo = criarNo(novaPergunta);
            novoNo->nao = noAtual;
            novoNo->sim = criarNo(novoAnimal);
            *noAtual = *novoNo;

        }

    } else {
        printf("%s (s/n) ", noAtual->pergunta);
        scanf(" %c", &resposta);
        if (resposta == 's') {
            fazerPerguntas(noAtual->sim); // Percorre para o nó "sim"
        } else {
            fazerPerguntas(noAtual->nao); // Percorre para o nó "nao"
        }
    }
}


int main() {
    char jogarNovamente = 's';
    // loop principal
  
        printf("Vamos jogar um jogo!\n");
        printf("Pense em um animal e eu vou tentar adivinhar qual eh.\n");
        printf("As perguntas so podem ser respondidas com 's' para sim ou 'n' para nao.\n");

        // Cria a árvore inicial com a primeira pergunta
        No* raiz = criarNo("O animal que voce pensou eh mamifero?");
        No* sim = criarNo("humano");
        No* nao = criarNo("galinha");
        raiz->sim = sim;
        raiz->nao = nao;

     while (jogarNovamente == 's') {
        // Faz as perguntas ao usuário
        fazerPerguntas(raiz);

        // Pergunta ao usuário se deseja jogar novamente
        printf("Deseja jogar novamente? (s/n) ");
        scanf(" %c", &jogarNovamente);

        if(jogarNovamente == 'n'){
            printf("Obrigado por jogar! Ate a proxima.\n");
             // Libera a memória alocada para a árvore
            liberarArvore(raiz);
        }
    }
    return 0;
}
