/*
Pratica 05: Resolve o desafio 02 da Pratica 03: testar 2 threads calculando o n-�simo termo da sequencia de Fibonacci em conjunto (cooperada).

===========
Experimento
===========

Digite o codigo em C a seguir em um editor de texto e salve o arquivo com o se -
guinte nome:

pratica05.c

Depois, compile o programa em linha de comando da seguinte forma:

cc -lpthread pratica05.c -o pratica05  {ou use -pthread ao inves de -lpthread}

Corrija os erros de compilacao. Quando a compilacao for bem sucedida, o arquivo
executavel "pratica05" serah criado.

Entao, execute o executavel com a seguinte linha de comando:

./pratica05

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define maxFib 100

int fib[maxFib], tamSeq;

void *geraFibonacci(void *ptr);

typedef struct tipoPack tipoPack;

void main(void)
{
     pthread_t thread[2];

     int  i, iret[2], tid[2]={1,2};

     printf("Programa Multithreaded de Geracao da Sequencia de Fibonacci\n");


     tamSeq=0;
     while (tamSeq<=0) {
            printf("\nDigite o tamanho n da sequencia > ");
            scanf("%d",&tamSeq);
     }

     fib[0]=1;
     fib[1]=1;
     for (i=2; i<tamSeq; i++)
        fib[i]=0;

     iret[0] = pthread_create(&thread[0], NULL, geraFibonacci, (void*) &tid[0]);

     iret[1] = pthread_create(&thread[1], NULL, geraFibonacci, (void*) &tid[1]);

     pthread_join(thread[0], NULL);
     pthread_join(thread[1], NULL);

     printf("\nSequencia Gerada: ");
     for (i=0;i<tamSeq-1;i++)
        printf("%d, ",fib[i]);
     printf("%d\n",fib[tamSeq-1]);
     exit(0);
}

void *geraFibonacci(void *ptr)
{    int i, *tid;
     char tipo[2][10]={"PARES", "IMPARES"};


     tid = (int *) ptr;

     printf("\nThread %d: vai gerar os numeros %s\n", *tid, tipo[*tid-1]);


     for (i=2+(*tid-1); i<tamSeq; i+=2){
	     while (fib[i-1]==0);
	     fib[i]=fib[i-1]+fib[i-2];
     }
}

/*
Desafio: Implementar uma aplica��o com k threads que busca em conjunto o maior e o menor elementos de um vetor compartilhado gerado aleatoriamente. O usu�rio fornece o tamanhho do vetor e o numero k de threads. N�o use fun��es de threads ainda n�o passadas em sala.
*/


