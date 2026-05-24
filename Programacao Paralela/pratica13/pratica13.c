/* Pratica 13: Aplicação de Base: Calcula a matriz Cmxp resultante da multiplicacao matricial de duas matrizes Amxn e Bnxp, sendo Cmxp=Amxn*Bnxp.
As matrizes A e B sao geradas aleatoriamente e a matriz C eh calculada. Todas as matrizes sao mostradas na tela.
Utilize uma thread para cada produto escalar linhaxcoluna
*/

/* Desafio: ajustar este codigo para usar multiplas threads, de forma que cada thread deve se responsabilizar pela multiplicação de apenas uma linha de A por uma coluna de B.
Nesse caso, o numero de threads eh definido pelo produto do numero de linhas de A pelo numero de colunas de B.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define maxDim 100

typedef int tipoMatriz[maxDim][maxDim];

tipoMatriz A, B, C;

pthread_t thread[maxDim];

int m, n, p;

struct tipoPack{
    int lin, col, result;
};
typedef struct tipoPack tipoPack;

void *produtoEscalar(void *ptr){   
    int PE, i;
    tipoPack *pack;
    pack = (tipoPack *) ptr;

    printf("\nCalculando PE da posicao: (%d, %d)", pack->lin, pack->col);

    PE = 0;
    for (i=0; i<n; i++)
        PE=PE+A[pack->lin][i]*B[i][pack->col];

    pack->result = PE;
}

void geraMatriz(tipoMatriz M, int nLins, int nCols){
    int l, c;
    for (l=0; l<nLins; l++)
        for (c=0; c<nCols; c++)
            M[l][c]=rand()%10;
}

void mostraMatriz(char *nome, tipoMatriz M, int nLins, int nCols)
{   int l,c;

    printf("\n%s:\n", nome);
    for (l=0; l<nLins; l++){
        for (c=0; c<nCols; c++)
            printf("%3d, ",M[l][c]);
        printf("\n");
    }

}

void multiplicaMatriz(tipoMatriz A, tipoMatriz B, tipoMatriz C, int m, int n, int p)
{   int l, c, i = 0, qtdeThreads;
    qtdeThreads = m * p; 
    int iret[qtdeThreads];
    tipoPack pack[qtdeThreads];

    for (l=0; l<m; l++){
        for (c=0; c<p; c++){
            pack[i].lin = l;
            pack[i].col = c;
            i++;
        }
    }

    for (i=0; i<qtdeThreads; i++)
        iret[i] = pthread_create(&(thread[i]), NULL, produtoEscalar, (void*) &pack[i]);

    for (i=0; i<qtdeThreads; i++)
        pthread_join(thread[i], NULL);

    // Matriz C 
    i = 0;
    for (l=0; l<m; l++){
        for (c=0; c<p; c++){
            C[l][c]=pack[i].result;
            i++;
        }
    }
}

void main(void)
{   int PE, opcao;

    srand(time(NULL));

    do
    {
        system("cls");
        printf("*** Programa para Multiplicacao Matricial ***\n\n");

        printf("\nQuantas linhas na matriz A? => ");
        scanf("%d",&m);

        printf("\nQuantas colunas na matriz A? => ");
        scanf("%d",&n);

        printf("\nQuantas colunas na matriz B? => ");
        scanf("%d",&p);

        geraMatriz(A,m,n);
        mostraMatriz("Matriz A", A, m, n);

        geraMatriz(B,n,p);
        mostraMatriz("Matriz B", B, n, p);

        multiplicaMatriz(A, B, C, m, n, p);

        mostraMatriz("Matriz C (Resultante)", C, m, p);

        printf("\nDeseja nova execucao <1>Sim ou <2>Nao? > ");
        scanf("%d",&opcao);
    } while (opcao==1);

}
