#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

/*
pthread_create() retorna 0, caso contrario, retorna o numero do erro
A espera pelo termino das threads: int pthread_join(pthread_t thread, NULL); pthread_join() retorna 0, caso contrario, retorna o numero do erro
A função pthread_self() retorna o identificador da thread que está executando no momento.

exemplo01.c
compilar: cc -lpthread exemplo01.c -o exemplo01
executar: ./exemplo01
*/

/*=================================*/
/* Exemplo genérico*/

void main(void){
    pthread_t thread1, thread2;
    char mensagem1[16] = "\nSou a thread 1";
    char mensagem2[16] = "\nSou a thread 2";
    int  iret1, iret2;

    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) mensagem1);
    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) mensagem2);

    printf("\nCriacao da thread 1 retornou: %d\n",iret1);
    printf("\nCriacao da thread 2 retornou: %d\n",iret2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nAmbas as threads 1 e 2 ja finalizaram e agora eu (o main) finalizarei...\n");
    exit(0);
}

void *funcaoImprimeMensagem(void *ptr){
     char *mensagem;
     mensagem = (char *) ptr;
     printf("%s \n", mensagem);
}

/*=================================*/
/* Estrutura */

struct tipoPack {
   char mensagem[16];
   int tam, soma;
};
typedef struct tipoPack tipoPack;

// OUTRO MODO DE USAR
// typedef struct tipoPack{
//     int id;
//     int limite;
// } tipoPack;

void main(void){
    pthread_t thread1;
    int iret1;
    tipoPack pack1;

    strcpy(pack1.mensagem,"\nSou a thread 1");
    pack1.soma=0;

    printf("\nDigite o tamanho da sequencia 1 > ");
    scanf("%d",&(pack1.tam));

    iret1 = pthread_create(&thread1, NULL, funcaoSomaSequencial, (void*) &pack1);
    pthread_join(thread1, NULL);
    printf("\nThread 1 somou: %d\n",pack1.soma);
}

void *funcaoSomaSequencial(void *ptr){    
    int i;
    tipoPack *pack;
    pack = (tipoPack *) ptr;

    printf("%s: vou realizar uma somatoria", pack->mensagem);

    pack->soma = 0;
    for (i=1; i<=(pack->tam); i++)
        (pack->soma) = (pack->soma) + i;
}
/*=================================*/

/* Selection sort */
/*
Implementa o desafio da pratica 6 para ordenar um vetor usando selecao
direta com 2 threads. Uma thread ordena os menores na primeira metade do vetor a
outra thread ordena os maiores na segunda metade do vetor. 
*/
#define maxElem 100

void *ordenaSelecaoDireta(void *ptr);

void geraVetor(int n);

int vet[maxElem], auxVet[maxElem], nElem;

void main(void){
    pthread_t thread[2];

    int  i, iret[2],tid[2];

    printf("Programa Dualthread para Ordenar Vetor por Selecao Direta\n");

    srand(time(NULL));
    nElem=0;
    while (nElem<1) {
        printf("\nEntre com numero de elementos do vetor (nao nulo) => ");
        scanf("%d", &nElem);
    }

    geraVetor(nElem);

    tid[0]=1;
    iret[0] = pthread_create(&(thread[0]), NULL, ordenaSelecaoDireta, (void*) &tid[0]);
    pthread_join(thread[0], NULL);

    for (i=nElem/2; i<nElem; i++)
        vet[i]=auxVet[i];

    printf("\nThread Main: Vetor Ordenado\n");

    for (i=0; i<nElem; i++)
        printf("%d, ",vet[i]);

    printf("\n");

    exit(0);
}

void *ordenaSelecaoDireta(void *ptr){    
    int i, posOrd, posPost, posAnt, posMenor, posMaior, aux;

    int *tid;

    tid = (int *) ptr;

    printf("\nThread %d: vou ordenar a minha metade\n", *tid);
    if (*tid==1) {
        printf("De %d a %d\n",0, nElem/2-1);

        for (posOrd=0; posOrd<nElem/2; posOrd++){
                posMenor=posOrd;
                for (posPost=posOrd+1; posPost<nElem; posPost++){
                if (vet[posMenor]>vet[posPost])
                    posMenor=posPost;
                }
                aux=vet[posOrd];
                vet[posOrd]=vet[posMenor];
                vet[posMenor]=aux;
        }

    } else {

        printf("De %d a %d\n",nElem/2, nElem-1);

        for (posOrd=nElem-1; posOrd>=nElem/2; posOrd--){
             posMaior=posOrd;
             for (posAnt=posOrd-1; posAnt>=0; posAnt--){
                if (auxVet[posMaior]<auxVet[posAnt])
                  posMaior=posAnt;
             }
             aux=auxVet[posOrd];
             auxVet[posOrd]=auxVet[posMaior];
             auxVet[posMaior]=aux;
        }
    }

}

void geraVetor(int n){
int i;
    // usar srand(time(NULL));
  printf("\nGeracao do Vetor:\n");

  for (i=0; i<n-1; i++){
      vet[i]=rand()%1000;
      printf("%d, ",vet[i]);
      auxVet[i]=vet[i];
  }
  vet[i]=rand()%1000;
  printf("%d\n",vet[i]);
  auxVet[i]=vet[i];
}

/*=================================*/

/* Maior e menor */
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

/* Lógica de dividir um range entre threads 

faixa = N/kThreads;
restante = N % kThreads;

ini = 1;
fim = faixa;

if (restante>0){
    fim++;
    restante--;
}

for (i=0; i<kThreads; i++){
    pack[i].tid=i+1;
    pack[i].fatParcial = 1.0;
    pack[i].ini = ini;
    pack[i].fim = fim;

    ini=fim+1;
    fim=fim+faixa;

    if (restante>0){
        fim++;
        restante--;
    }
}
*/

/*=================================*/


/* Auxiliares

- sizeof() // tamanho de vetores
- Matrizes:
#define maxDim 100

typedef int tipoMatriz[maxDim][maxDim];

tipoMatriz A, B, C;

Colocar matriz dentro de pack
pack[l][c].A = (tipoMatriz*) A;

Ler elemento de matriz em uma struct que foi passado por parametro
PE=PE+(*pack->A)[pack->lin][i]*(*pack->B)[i][pack->col];


| Função      | Descrição                                       |
| ----------- | ----------------------------------------------- |
| `sizeof()`  | Retorna o tamanho em bytes de uma variável/tipo |
| `malloc()`  | Aloca memória dinamicamente                     |
| `calloc()`  | Aloca memória e inicializa com zero             |
| `realloc()` | Redimensiona memória alocada                    |
| `free()`    | Libera memória                                  |
| `rand()`    | Gera número aleatório                           |
| `srand()`   | Define semente do `rand()`                      |
| `time()`    | Retorna tempo atual (usado com `srand`)         |
| `printf()`  | Imprime na tela                                 |
| `scanf()`   | Lê entrada do usuário                           |
| `fgets()`   | Lê string                                       |
| `strcmp()`  | Compara strings                                 |
| `strcpy()`  | Copia strings                                   |
| `strlen()`  | Retorna tamanho da string                       |
| `memcpy()`  | Copia blocos de memória                         |
| `memset()`  | Preenche memória com valor                      |
| `exit()`    | Finaliza programa                               |
| `sleep()`   | Pausa execução por segundos                     |
| `usleep()`  | Pausa em microssegundos                         |

*/

/*
| Função                      | Descrição                                   |
| --------------------------- | ------------------------------------------- |
| `pthread_create()`          | Cria uma thread                             |
| `pthread_join()`            | Espera thread terminar                      |
| `pthread_exit()`            | Finaliza thread                             |
| `pthread_self()`            | Retorna ID da thread atual                  |
| `pthread_equal()`           | Compara IDs de threads                      |
| `pthread_cancel()`          | Cancela uma thread                          |
| `pthread_detach()`          | Libera thread automaticamente após terminar |
| `pthread_mutex_init()`      | Inicializa mutex                            |
| `pthread_mutex_lock()`      | Trava mutex                                 |
| `pthread_mutex_unlock()`    | Destrava mutex                              |
| `pthread_mutex_destroy()`   | Destrói mutex                               |
| `pthread_cond_init()`       | Inicializa variável de condição             |
| `pthread_cond_wait()`       | Faz thread esperar condição                 |
| `pthread_cond_signal()`     | Acorda uma thread esperando                 |
| `pthread_cond_broadcast()`  | Acorda todas as threads esperando           |
| `pthread_cond_destroy()`    | Destrói variável de condição                |
| `pthread_barrier_init()`    | Inicializa barreira                         |
| `pthread_barrier_wait()`    | Sincroniza threads na barreira              |
| `pthread_barrier_destroy()` | Destrói barreira                            |

*/
