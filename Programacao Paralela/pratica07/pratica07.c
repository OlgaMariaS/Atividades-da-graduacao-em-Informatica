/*
Pratica 07: busca maior e menor elementos dentro de um vetor gerado aleatoriamente usando k threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define maxThreads 50
#define maxElem 100

void *buscaMaiorMenor(void *ptr);

void geraVetor(int n);

int vet[maxElem];

struct tipoPack {
   int tid, ini, fim, posMaior, posMenor;
};

typedef struct tipoPack tipoPack;

/* Considere o main() como sendo a thread 0. Assim, as k threads sao enumeradas de
1 a k. Entretanto, as estruturas vetoriais associadas a k threads sao indexadas de
0 a k-1 */
void main(void)
{
     pthread_t thread[maxThreads];

     int  i, iret[maxThreads], kThreads;
     int ini, fim, faixa, restante, nElem, posMaior, posMenor;

     tipoPack pack[maxThreads];

     srand(time(NULL));

     printf("Programa Multithread para Buscar Maior e Menor Elementos\n");

     nElem=0;
     while (nElem<1) {
        printf("\nEntre com numero de elementos do vetor (nao nulo) => ");
        scanf("%d", &nElem);
     }

     geraVetor(nElem);

     kThreads=0;
     while ((kThreads<1)||(kThreads>nElem)) {
        printf("\nO numero de threads nao pode ser nulo e nem maior que o numero de elementos!");
        printf("\nEntre com o numero de threads => ");
        scanf("%d", &kThreads);
     }

     faixa = nElem/kThreads;
     restante = nElem % kThreads;

     ini = 0;
     fim = faixa-1;

     if (restante>0)
     {
         fim++;
         restante--;
     }

     for (i=0; i<kThreads; i++)
     {
            pack[i].tid=i+1;
            pack[i].ini = ini;
            pack[i].fim = fim;
            pack[i].posMaior=ini;
            pack[i].posMenor=ini;

            ini=fim+1;
            fim=ini+faixa-1;

            if (restante>0)
            {
                fim++;
                restante--;
            }
     }

     for (i=0; i<kThreads; i++)
        iret[i] = pthread_create(&(thread[i]), NULL, buscaMaiorMenor, (void*) &pack[i]);

     for (i=0; i<kThreads; i++)
        pthread_join(thread[i], NULL);

     printf("\nThread %d: achou Maior = %d e Menor = %d\n", 1, vet[pack[0].posMaior], vet[pack[0].posMenor]);
     posMaior=pack[0].posMaior;
     posMenor=pack[0].posMenor;

     for (i=1; i<kThreads; i++)
     {
         printf("\nThread %d: achou Maior = %d e Menor = %d\n", i+1, vet[pack[i].posMaior], vet[pack[i].posMenor]);
         if (vet[posMaior] < vet[pack[i].posMaior])
             posMaior=pack[i].posMaior;
         else if (vet[posMenor] > vet[pack[i].posMenor])
             posMenor=pack[i].posMenor;
     }

     printf("\nThread Main: Maior de Todos = %d e Menor de Todos = %d\n", vet[posMaior], vet[posMenor]);

     exit(0);
}

void *buscaMaiorMenor(void *ptr)
{    int i;

     tipoPack *pack;

     pack = (tipoPack *) ptr;

     printf("Thread %d: vou procurar o Maior e o Menor de %d a %d\n", pack->tid, pack->ini, pack->fim);
    
     for (i=pack->ini+1; i<=(pack->fim); i++){
         if (vet[pack->posMaior]<vet[i])
             pack->posMaior=i;
         else if (vet[pack->posMenor]>vet[i])
             pack->posMenor=i;
     };

}

void geraVetor(int n){
int i;

  printf("\nGeracao do Vetor:\n");

  for (i=0; i<n-1; i++){
      vet[i]=rand()%1000;
      printf("%d, ",vet[i]);
  }
  vet[i]=rand()%1000;
  printf("%d\n",vet[i]);
}