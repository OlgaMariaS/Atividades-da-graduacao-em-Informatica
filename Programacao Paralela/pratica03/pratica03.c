/*

Pratica 03: testar a passagem de uma informacao composta para as threads, permitindo o retorno privado de calculos realizados por elas. Aqui, duas threads calculam a soma de numeros sequenciais inteiros que v�o de 1 ao tamanho fornecido pelo usu�rio.

===========
Experimento
===========

Digite o codigo em C a seguir em um editor de texto e salve o arquivo com o seguinte nome:

pratica03.c

Depois, compile o programa em linha de comando da seguinte forma:

cc -lpthread pratica03.c -o pratica03  {ou use -pthread ao inves de -lpthread}

Corrija os erros de compilacao.  Quando a compilacao for bem sucedida, o arquivo
executavel "pratica03" serah criado.

Entao, execute o executavel com a seguinte linha de comando:

./pratica03

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoSomaSequencial(void *ptr);

struct tipoPack {
   char mensagem[16];
   int tam, soma;
};

typedef struct tipoPack tipoPack;

void main(void)
{
     pthread_t thread1, thread2;

     int  iret1, iret2;

     tipoPack pack1, pack2;

     strcpy(pack1.mensagem,"\nSou a thread 1");
     pack1.soma=0;

     strcpy(pack2.mensagem,"\nSou a thread 2");
     pack2.soma=0;

     printf("\nDigite o tamanho da sequencia 1 > ");
     scanf("%d",&(pack1.tam));

     printf("\nDigite o tamanho da sequencia 2 > ");
     scanf("%d",&(pack2.tam));

     iret1 = pthread_create(&thread1, NULL, funcaoSomaSequencial, (void*) &pack1);

     iret2 = pthread_create(&thread2, NULL, funcaoSomaSequencial, (void*) &pack2);

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);

     printf("\nThread 1 somou: %d\n",pack1.soma);
     printf("\nThread 2 somou: %d\n",pack2.soma);
     exit(0);
}

void *funcaoSomaSequencial(void *ptr)
{    int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     printf("%s: vou realizar uma somatoria", pack->mensagem);

     pack->soma = 0;
     for (i=1; i<=(pack->tam); i++)
	     (pack->soma) = (pack->soma) + i;

}

/*

Desafios para Entregar:

1) Primeira Implementacao: Altere o exemplo para que as threads calculem e retornem a fatorial de um numero. Crie identifica��o pr�pria para cada thread. Vetorize as vari�veis e estruturas das threads para index�-las pela pr�pria identifica��o de cada uma. Cada thread deve calcular uma fatorial diferente, conforme informado pelo usuario. Ajuste a estrutura e os nomes das variaveis. Compile, execute e analise. Entregue o c�digo fonte.

2) Segunda Implementacao: Modifique o exemplo para que as threads calculem e retornem o n-esimo elemento da sequencia de fibonacci, conforme n fornecido pelo
usuario. Crie identifica��o pr�pria para cada thread. Vetorize as vari�veis e estruturas das threads para index�-las pela pr�pria identifica��o de cada uma. As threads devem trabalhar em conjunto para calcular esse valor. Crie uma solucao da melhor forma que voce puder. Ajuste a estrutura e os nomes das variaveis. Compile, execute e analise. Entregue o c�digo fonte.

*/
