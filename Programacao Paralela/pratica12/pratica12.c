/*

Pr�tica 12: Implementa o desafio da pratica 11. A ideia � implementar um metodo de ordenacao MergeSort multithread, recursiva e combinado com com Sele��o Direta. Nessa versao paralela, os segmentos esquerdo e direito sao atribuidos a threads diferentes enquanto forem maior que o limite minimo do segmento do vetor, caso contrario, sao resolvidos com Sele��o Direta usando 2 threads cooperantes.

Digite o codigo em C a seguir em um editor de texto e salve o arquivo com o
seguinte nome:

pratica12.c

Depois, compile o programa em linha de comando do Linux, da seguinte forma:

cc -lpthread pratica12.c -o pratica12  {ou use -pthread ao inves de -lpthread}

Corrija os erros de compilacao. Quando a compilacao for bem sucedida, o arquivo
executavel "pratica12" serah criado.


E por fim execute no Linux da seguinte forma:

./pratica12

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define maxVet 10000
#define maxNumero 10000

typedef  int tipoVetor[maxVet];

tipoVetor A, auxA;

typedef struct
{
    int ini, fim, tid;
} tipoPack;

int tamA, limSegmento;


/* efetua a leitura do tamanho, considerando as restricoes
para valores negativos ou acima do limite maximo; retorna
no nome da funcao */

int leTam(char *titulo, int max)
{   int tam;

    do
    {  printf("\nDigite o %s = ", titulo);
       scanf("%d", &tam);
    } while ((tam<1)||(tam>max));

    return tam;
}

/* gera o vetor aleatoriamente, de acordo com o tamanho passado
   como parametro. O valores gerados podem ser positivos ou negativos
   e estao limitados a maxNumero. */

void geraVetor(tipoVetor V, int tam)
{   int i, sinal;

    srand(time(NULL));

    printf("\nGeracao Aleatoria do Vetor\n");

    for (i=0; i<tam; i++)
    {
        V[i]=rand()%maxNumero;
        sinal=(rand()%2)*2-1; /* se rand%2==0, sinal=-1;
                                 se rand%2==1, sinal=+1 */

        V[i]=sinal*V[i];  /* impoe o sinal no n�mero */
    }
}

/* mostra o vetor no video como uma sequencia de elementos
   separados por virgula */

void mostraVetor(char *id, tipoVetor V, int tam)
{   int i;

    printf("\nElementos do Vetor %s:\n", id);
    printf("%d",V[0]);
    for (i=1; i<tam; i++)
    {
        printf(", %d",V[i]);
    }
    printf("\n");
}

void *ordenaSelecaoDireta(void *ptr)
{    int i, posOrd, posPost, posAnt, posMenor, posMaior, aux, nElem, meio;

     tipoPack *pack;

     pack = (tipoPack *)ptr;

     meio=(pack->ini+pack->fim)/2;

     //printf("\nThread %d: vou ordenar a minha metade\n", pack->tid);
     if (pack->tid==1) {

        //printf("De %d a %d\n",pack->ini, meio);

        for (posOrd=pack->ini; posOrd<=meio; posOrd++){
             posMenor=posOrd;
             for (posPost=posOrd+1; posPost<=pack->fim; posPost++){
                if (A[posMenor]>A[posPost])
                  posMenor=posPost;
             }
             aux=A[posOrd];
             A[posOrd]=A[posMenor];
             A[posMenor]=aux;
        }

     } else {

        //printf("De %d a %d\n",meio+1, pack->fim);

        for (posOrd=pack->fim; posOrd>=meio+1; posOrd--){
             posMaior=posOrd;
             for (posAnt=posOrd-1; posAnt>=pack->ini; posAnt--){
                if (auxA[posMaior]<auxA[posAnt])
                  posMaior=posAnt;
             }
             aux=auxA[posOrd];
             auxA[posOrd]=auxA[posMaior];
             auxA[posMaior]=aux;
        }
     }
}

/*  junta/funde duas metades ja ordenadas dentro do segmento do
    vetor que vai de ini at� fim. A primeira metade vai de ini
    ate meio, a segunda vai de meio+1 ate fim. Usa-se 2 vetores
    auxiliares para copiar as metades, percorre-las, comparando
    os elementos e devolver para o segmento original, para que
    este fique totalmente ordenado. */

void mergeMetades(tipoVetor V, int ini, int meio, int fim)
{   tipoVetor auxV1, auxV2;
    int tam1=0, tam2=0, maior, i, i1, i2;

    /* copia primeira metade V[ini..meio] para auxV1 */
    for (i=ini; i<=meio; i++)
    {
        auxV1[tam1]=V[i];
        tam1++;
    }

    /* copia segunda metade V[meio+1..fim] para auxV2 */
    for (i=meio+1; i<=fim; i++)
    {
        auxV2[tam2]=V[i];
        tam2++;
    }

    /* descobre um valor maior que todos do segmento */

    if (auxV1[tam1-1]> auxV2[tam2-1])
        maior = abs(auxV1[tam1-1])+1;
    else maior = abs(auxV2[tam2-1])+1;

    /* insere o valor maior que todos logo apos o ultimo de
       cada metade, o qual servira como uma sentinela/barreira */

    auxV1[tam1]=maior;
    auxV2[tam2]=maior;

    /* avan�a em cada metade retirando o menor elemento e
       colocando de volta no segmento, para que todo o segmento
       fique ordenado */

    i1=0;
    i2=0;
    for (i=ini; i<=fim; i++)
    {
        if (auxV1[i1]<auxV2[i2])
        {
            V[i]=auxV1[i1];
            i1++;
        }
        else {
            V[i]=auxV2[i2];
            i2++;
        }
    }

}

/* solucao paralela e recursiva do Merge Sort para o segmento do vetor que vai
   de ini ate fim. Na primeira chamada, esse intervalo alcan�a todo o vetor.
   Em cada chamada, se houver pelo menos "limSegmento" elementos no segmento,
   o mesmo eh dividido em duas metades e para cada metade uma thread eh criada
   para fazer a mesma coisa, caso contrario, se houver mais do que 1 elemento no
   segmento, o mesmo eh dividido em duas metades e para cada metade, a funcao eh
   chamada de novo (recursivamente). A recursividade prossegue at� que surgem
   metades unitarias, quando ent�o ocorre o retorno da recursividade. No retorno,
   as metades unitarias sao juntadas (merge) e geram segmentos duplos, e da mesma
   forma, as metades duplas sao juntadas e geram  segmentos quadruplos, metades
   quadruplas geram segmentos octuplos e assim sucessivamente ate que todo o
   vetor esteja ordenado. */

void *mergeSort(void *ptr)
{   int i, meio, iretEsq, iretDir;
    tipoPack packEsq, packDir, *pack;
    pthread_t threadEsq, threadDir;

    pack=(tipoPack *)ptr;

    if (pack->fim-pack->ini>=limSegmento)
    {
        meio = (pack->ini+pack->fim)/2;

        packEsq.tid=1;
        packEsq.ini=pack->ini;
        packEsq.fim=meio;
        iretEsq = pthread_create(&threadEsq, NULL, mergeSort, (void*) &packEsq);

        packDir.tid=2;
        packDir.ini=meio+1;
        packDir.fim=pack->fim;
        iretDir = pthread_create(&threadDir, NULL, mergeSort, (void*) &packDir);

        pthread_join(threadEsq, NULL);
        pthread_join(threadDir, NULL);

        mergeMetades(A,pack->ini,meio,pack->fim);
    }
    else if (pack->fim>pack->ini) {
            packEsq.tid=1;
            packEsq.ini=pack->ini;
            packEsq.fim=pack->fim;
            iretEsq = pthread_create(&(threadEsq),NULL,ordenaSelecaoDireta,(void*)&packEsq);


            packDir.tid=2;
            packDir.ini=pack->ini;
            packDir.fim=pack->fim;
            iretDir = pthread_create(&(threadDir),NULL,ordenaSelecaoDireta,(void*)&packDir);

            pthread_join(threadEsq, NULL);
            pthread_join(threadDir, NULL);

            meio = (pack->ini+pack->fim)/2;

            for (i=meio+1; i<=pack->fim; i++)
                A[i]=auxA[i];

         }

}

void main(void)
{ int resp, i;
  tipoPack pack;

  do
  {

    tamA=leTam("Tamanho do Vetor", maxVet);

    limSegmento=leTam("Limite Minimo do Segmento", tamA);

    geraVetor(A, tamA);

    for (i=0; i<tamA; i++)
       auxA[i]=A[i];

    mostraVetor("A Original", A, tamA);

    printf("\nOrdenando A por Merge Sort ...\n");

    pack.ini=0;
    pack.fim=tamA-1;
    mergeSort((void*)&pack);

    mostraVetor("A Ordenado", A, tamA);

    printf("\nDeseja Nova Execucao, <1>Sim <2>Nao? => ");
    scanf("%d",&resp);

  } while (resp==1);
}

/*
Desafio: Implemente a multiplica��o matricial AxB=C, usando multiplas threads, de forma que cada thread deve se responsabilizar pela multiplica��o de apenas uma linha de A por uma coluna de B. Nesse caso, o numero de threads eh definido pelo produto do numero de linhas de A pelo numero de colunas de B.
*/