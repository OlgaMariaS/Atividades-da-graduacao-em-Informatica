/*
========
Desafio: faça as seguintes modificações no programa e ao final entregue o código fonte.
========

1- Adicione mais uma thread, com mensagem especifica para ela.
2- Crie uma identificação para cada thread (número inteiro) e passe esta identificação como parametro da função da thread. As ações de cada thread devem ser direcionadas por esta identificação.
3 - Para que cada thread imprima em loop uma sequencia de TAM1 vezes a mensagem passada como parametro.
4 - Acrescente o seguinte:
    - declare um vetor de 3000 posicoes de numeros inteiros
    - faca cada thread preencher TAM1 posicoes do vetor com o seu numero (a thread
      1 preenche 1 nas TAM1 primeiras posicoes, a thread 2 preenche 2 nas TAM1
      posicoes intermediarias e a thread 3 preenche 3 nas TAM1 ultimas posicoes)
    - apos a finalizacao das threads faca o programa principal imprimir o vetor
      resultante para ver se deu certo o preenchimento do vetor
5 - acrescente explicacoes de funcionamento no programa 3 e entregue na plataforma utilizada.

obs: se tiver duvidas, fale com o professor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM1 1000
#define TAM2 3000

int vetor[TAM2];

void *funcaoThread(void *ptr){
   int *id = (int *)ptr;

   // Imprime 1000 vezes
   for (int i = 0; i < TAM1; i++){
      printf("%d - Thread %d\n", i+1, *id);
   }

   // Define indice inicio e fim no vetor
   int inicio = (*id - 1) * TAM1;
   int fim = inicio + TAM1;

   // Preenche vetor
   for (int i = inicio; i < fim; i++){
      vetor[i] = *id;
   }

   pthread_exit(NULL);
}

int main(void){
   pthread_t thread1, thread2, thread3;

   int ids[3] = {1, 2, 3};

   int iret1, iret2, iret3;

   iret1 = pthread_create(&thread1, NULL, funcaoThread, (void *)&ids[0]);
   iret2 = pthread_create(&thread2, NULL, funcaoThread, (void *)&ids[1]);
   iret3 = pthread_create(&thread3, NULL, funcaoThread, (void *)&ids[2]);

   printf("Criacao da thread 1 retornou: %d\n", iret1);
   printf("Criacao da thread 2 retornou: %d\n", iret2);
   printf("Criacao da thread 3 retornou: %d\n", iret3);

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   pthread_join(thread3, NULL);

   printf("\n===== Vetor =====\n");
   for (int i = 0; i < TAM2; i++){
      printf("%d ", vetor[i]);
      if ((i + 1) % 50 == 0)
         printf("\n");
   }

   printf("\n\nFinalizou!\n");

   return 0;
}