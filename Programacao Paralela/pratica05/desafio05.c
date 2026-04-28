/*
Desafio: Ordene um vetor com n elementos inteiros usando Seleção Direta com 2 threads. Faça a leitura do n e gere o vetor aleatoriamente. Um thread procura pelos menores e vai
colocando no inicio do vetor e a outra thread procura pelos maiores e vai colocando
no final do vetor. Ambas as threads trabalham até a metade do vetor, não sobrepondo
posições de ordenação.

OBS: na seleção direta, a cada passo, procura-se o menor (ou maior) elemento,
comparando todos os elementos ainda não ordenados e o coloca na sua posição de
ordenação. Repete o processo até ordenar todo o vetor.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define maxTam 100

int vetor[maxTam], tam = 0;

void *ordenar(void *ptr);

void main(void)
{
     pthread_t thread[2];

     int  i, iret[2], tid[2]={1,2};

     printf("Programa Dualthreaded de ordenacao de vetores\n");

     while (tam<=0){
            printf("\nDigite o tamanho para o vetor: ");
            scanf("%d",&tam);
     }

     for(i=0; i<=tam; i++)
        vetor[i] = rand() % 100 // numeros de 0 a 99

     iret[0] = pthread_create(&thread[0], NULL, ordenar, (void*) &tid[0]);
     iret[1] = pthread_create(&thread[1], NULL, ordenar, (void*) &tid[1]);

     pthread_join(thread[0], NULL);
     pthread_join(thread[1], NULL);

     printf("\nVetor ordenado: \n");
     for (i=0;i<tam-1;i++)
        printf(" %d |",vetor[i]);
     printf("%d\n",vetor[tam-1]);
     exit(0);
}

// o problema que pode ocorrer é chamado colisão
// quando uma thread tentar ordenar (realocar) enquanto a outra está escrevendo/lendo a mesma posição
void *ordenar(void *ptr)
{    int i, *tid;
     char tipo[2][10]={"DIREITA", "ESQUERDA"};

     tid = (int *) ptr;
     /*
     Pego o tamanho, e o resto da divisão dele por 2 pra dividir em duas partes
     Se sobra, soma na parte direita
     cada um trabalha na ordenação da sua parte
     */

     printf("\nThread %d: vai ordenar  %s\n", *tid, tipo[*tid-1]);

    // muda essa logica
     for (i=2+(*tid-1); i<tamSeq; i+=2){
	     while (fib[i-1]==0);
	     fib[i]=fib[i-1]+fib[i-2];
     }
}