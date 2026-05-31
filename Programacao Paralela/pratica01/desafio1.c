#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define QTDE 3
/*
========
Desafio
========
1- Adicione mais uma thread, com mensagem especifica para ela.
2- Crie uma identificação para cada thread (número inteiro) e passe esta identificação como parametro da função da thread. As ações de cada thread devem ser direcionadas por esta identificação.
3 - Para que cada thread imprima em loop uma sequencia de 1000 vezes a mensagem passada como parametro.
*/
void *imprime(void *arg){
    int *msg, i;
    msg = (int *) arg;

    for(i=0; i<10; i++){ // colocar 1000
        printf("thread %d: %d \n", *msg, i);
    }        

    pthread_exit(NULL);
}

int main(void){
    int i;
    int id[QTDE] = {1,2,3};
    pthread_t thread[QTDE];
    int iret[QTDE];

    for(i = 0; i < QTDE; i++){
        iret[i] = pthread_create(&thread[i],NULL, imprime, (void *)&id[i]);
    }

    for(i = 0; i < QTDE; i++){
        pthread_join(thread[i],NULL);
    }

    exit(0);
}