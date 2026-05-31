#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/*
========
Desafio
========
4 - Acrescente o seguinte:
    - declare um vetor de 3000 posicoes de numeros inteiros
    - faca cada thread preencher 1000 posicoes do vetor com o seu numero (a thread
      1 preenche 1 nas 1000 primeiras posicoes, a thread 2 preenche 2 nas 1000
      posicoes intermediarias e a thread 3 preenche 3 nas 1000 ultimas posicoes)
    - apos a finalizacao das threads faca o programa principal imprimir o vetor
      resultante para ver se deu certo o preenchimento do vetor
*/

#define QTDE 3
#define TAM 30

int vetor[TAM];

typedef struct tipoPack{
    int id;
    int limite;
} tipoPack;

void *preencheVetor(void *arg){
    int i, inicio, fim;
    tipoPack *pack;
    pack = (tipoPack *) arg;

    printf("Executando thread %d: \n", pack->id);

    // Calcula a faixa que vai preencher
    inicio = (pack->id * pack->limite) - pack->limite;
    fim    =  pack->id * pack->limite;

    for(i=inicio; i<fim; i++){
        vetor[i] = pack->id;
    }
    pthread_exit(NULL);
}

int main(void){
    int i;
    int id[QTDE] = {1,2,3};
    pthread_t thread[QTDE];
    int iret[QTDE];
    tipoPack pack[QTDE];

    for(i = 0; i < QTDE; i++){
        pack[i].id = id[i];
        pack[i].limite = TAM / QTDE;
        iret[i] = pthread_create(&thread[i],NULL, preencheVetor, (void*)&pack[i]);
    }

    for(i = 0; i < QTDE; i++){
        pthread_join(thread[i],NULL);
    }

    // imprime vetor
    printf("Vetor final: \n");
    for(i=0;i<TAM;i++){
        printf(" %d |", vetor[i]);
    }

    exit(0);
}

// limite = 10
// 1*10-10 até 1 * 10 [0-10]
// 2*10-10 até 2 * 10 [10-19]
// 3*10-10 até 3 * 10 [20-29]