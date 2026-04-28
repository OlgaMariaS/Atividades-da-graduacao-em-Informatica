/*

Pratica 06: implementacao do desafio da pr�tica 04 - fatorial �nica com k threads.
Uma unica fatorial sera calculada por k threads trabalhando em conjunto. Cada thread
calcula o seu intervalo de fatorial e no final, a thread main() ira calcula a
"fatorial" total por meio de uma multiplicacao de todas as fatoriais individuais.
Por exemplo, 10! (fatorial de 10) eh calculada da seguinte forma:

10!=10*9*8*7*6*5*4*3*2*1

ou ainda

 = (10*9*8*7)*(6*5*4)*(3*2*1)

assim, nesse exemplo, poderiamos dividir o calculo da fatorial entre 3 threads,
cada uma calculando uma parte diferente da fatorial total, por exemplo, a thread 1
calcula o produto 10*9*8*7, a threads 2 calcula 6*5*4 e a thread 3 calcula 3*2*1 e
ao final multiplicamos todos os valores parciais em um unico produto.

===========
Experimento
===========

Digite o codigo em C a seguir em um editor de texto e salve o arquivo com o seguinte
nome:

pratica06.c

Depois, compile o programa em linha de comando da seguinte forma:

cc -lpthread pratica06.c -o pratica06  {ou use -pthread ao inves de -lpthread}

Corrija os erros de compilacao. Quando a compilacao for bem sucedida, o arquivo
executavel "pratica06" serah criado.

Entao, execute o programa com a seguinte linha de comando:

./pratica06

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define maxThreads 50

void *calculaFatorial(void *ptr);

struct tipoPack {
   int tid, ini, fim;
   double fatParcial;
};

typedef struct tipoPack tipoPack;

/* Considere o main() como sendo a thread 0. Assim, as k threads sao enumeradas de
1 a k. Entretanto, as estruturas vetoriais associadas �s k threads sao indexadas de
0 a k-1 */
void main(void)
{
     pthread_t thread[maxThreads];

     int  i, iret[maxThreads], kThreads;
     char str_nt[3];
     int ini, fim, faixa, restante, N;
     double fatTotal = 1.0;

     tipoPack pack[maxThreads];

     printf("Programa Multithread para Calculo de Fatorial\n");

     printf("\nEntre com o numero de threads => ");
     scanf("%d", &kThreads);

     printf("\nEntre com N para o calculo da fatorial => ");
     scanf("%d", &N);

     faixa = N/kThreads;
     restante = N % kThreads;

     ini = 1;
     fim = faixa;

     if (restante>0)
     {
         fim++;
         restante--;
     }

     for (i=0; i<kThreads; i++)
     {
            pack[i].tid=i+1;
            pack[i].fatParcial = 1.0;
            pack[i].ini = ini;
            pack[i].fim = fim;

            ini=fim+1;
            fim=fim+faixa;

            if (restante>0)
            {
                fim++;
                restante--;
            }
     }

     for (i=0; i<kThreads; i++)
        iret[i] = pthread_create(&(thread[i]), NULL, calculaFatorial, (void*) &pack[i]);

     for (i=0; i<kThreads; i++)
        pthread_join(thread[i], NULL);

     for (i=0; i<kThreads; i++)
     {
         printf("\nThread %d: Fatorial Parcial = %.2lf\n", i+1, pack[i].fatParcial);
         fatTotal=fatTotal*pack[i].fatParcial;
     }

     printf("\nThread Main: Fatorial Total = %.2lf\n", fatTotal);

     exit(0);
}

void *calculaFatorial(void *ptr)
{    int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     printf("Thread %d: vou calcular a fatorial de %d a %d\n", pack->tid, pack->ini, pack->fim);

     for (i=pack->ini; i<=(pack->fim); i++)
	     (pack->fatParcial) = (pack->fatParcial) * i;

}

/* Desafio: Ordene um vetor com n elementos inteiros usando Sele��o Direta com 2 threads. Fa�a a leitura do n e gere o vetor aleatoriamente. Um thread procura pelos menores e vai
colocando no in�cio do vetor e a outra thread procura pelos maiores e vai colocando
no final do vetor. Ambas as threads trabalham at� a metade do vetor, n�o sobrepondo
posi��es de ordena��o.

OBS: na sele��o direta, a cada passo, procura-se o menor (ou maior) elemento,
comparando todos os elementos ainda n�o ordenados e o coloca na sua posi��o de
ordena��o. Repete o processo at� ordenar todo o vetor.

*/