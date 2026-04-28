/*
Implementar o desafio da Pratica 04 - k threads calculam a mesma Fatorial de forma conjunta
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 100

long long int resultado[MAX_THREADS];
int n, k;

void *calculaFatorial(void *ptr);

int main(void)
{
   pthread_t thread[MAX_THREADS];
   int i, tid[MAX_THREADS];

   printf("Programa Multithreaded - Calculo de Fatorial com n-threads\n");

   printf("Digite o valor de n (fatorial) > ");
   scanf("%d", &n);

   printf("Digite o numero de threads (k) > ");
   scanf("%d", &k);

   if (k <= 0 || k > MAX_THREADS){
      printf("Numero de threads invalido!\n");
      exit(1);
   }

   for (i = 0; i < k; i++){
      tid[i] = i;
      if (pthread_create(&thread[i], NULL, calculaFatorial, (void *)&tid[i]) != 0){
         printf("Erro ao criar thread %d\n", i);
         exit(1);
      }
   }

   for (i = 0; i < k; i++)
      pthread_join(thread[i], NULL);

   long long int fatorial = 1;
   for (i = 0; i < k; i++)
      fatorial *= resultado[i];

   printf("\nFatorial de %d = %lld\n", n, fatorial);

   return 0;
}

void *calculaFatorial(void *ptr)
{
   int id = *((int *)ptr);

   int base = n / k;
   int resto = n % k;

   int inicio, fim;

   if (id < resto){
      inicio = id * (base + 1) + 1;
      fim = inicio + base;
   }else{
      inicio = id * base + resto + 1;
      fim = inicio + base - 1;
   }

   printf("Thread %d: intervalo [%d - %d]\n", id, inicio, fim);

   long long int parcial = 1;

   for (int i = inicio; i <= fim; i++)
      parcial *= i;

   resultado[id] = parcial;

   pthread_exit(NULL);
}