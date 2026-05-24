/* Pratica 14: Aplicação multithread para calcular a matriz Cmxp resultante da multiplicacao matricial de duas matrizes Amxn e Bnxp, sendo Cmxp=Amxn*Bnxp.
As matrizes A e B sao geradas aleatoriamente e a matriz C eh calculada.
Cada thread deve se responsabilizar pela multiplicação de apenas uma linha de A por uma coluna de B.
Nesse caso, o numero de threads eh definido pelo produto do numero de linhas de A pelo numero de colunas de B.

*** Desafio: ajustar este codigo para usar multiplas threads, de forma que cada thread deve se responsabilizar pela multiplicação de uma linha de A por toda a matriz B.
Nesse caso, o numero de threads eh definido pelo numero de linhas de A.***
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define maxDim 100

typedef int tipoMatriz[maxDim][maxDim];

tipoMatriz A, B, *result[maxDim];

typedef struct{
    int lin, col, nElem, cij;
    tipoMatriz *A, *B;
} tipoPack;

int m, n, p;

void *produtoEscalar(void *ptr){
    int PE, i;
    tipoPack *pack;

    pack = (tipoPack *)ptr;

    PE = 0;
    for (i = 0; i < pack->nElem; i++)
        PE = PE + (*pack->A)[pack->lin][i] * (*pack->B)[i][pack->col];

    pack->cij = PE;
}

void geraMatriz(tipoMatriz M, int nLins, int nCols){
    int l, c;

    for (l = 0; l < nLins; l++)
        for (c = 0; c < nCols; c++)
            M[l][c] = rand() % 10;
}

void mostraMatriz(char *nome, tipoMatriz M, int nLins, int nCols){
    int l, c;

    printf("\n%s:\n", nome);
    for (l = 0; l < nLins; l++)
    {
        for (c = 0; c < nCols; c++)
            printf("%3d, ", M[l][c]);
        printf("\n");
    }
}

void multiplicaMatriz(tipoMatriz A, tipoMatriz B, int m, int n, int p){
    int l, c, i, iret[m][p];
    tipoMatriz matrizAux;
    pthread_t thread[m][p];
    tipoPack pack[m][p];

    // criar pack que recebem qual linha de A são, e pra cada um desses deve multiplicar toda a linha de A por todas as colunas de b
    for (l = 0; l < m; l++){
        for (c = 0; c < p; c++){

            pack[l][c].A = (tipoMatriz *)A[l]; // mudar a linha aqui
            pack[l][c].B = (tipoMatriz *)B;
            pack[l][c].lin = l; // cada linha de A
            pack[l][c].col = c; // todas as colunas de B
            pack[l][c].nElem = n;
            iret[l][c] = pthread_create(&(thread[l][c]), NULL, produtoEscalar, (void *)&(pack[l][c]));
        }
    }

    // Recebe a matriz resultando do pack
    for (l = 0; l < m; l++){
        result[i] = malloc(sizeof(tipoMatriz));
        for (c = 0; c < p; c++){

            pthread_join(thread[l][c], NULL);
            (*result[i])[l][c] = pack[l][c].cij;
        }
    }
}

void main(void)
{
    int i, PE, opcao;

    srand(time(NULL));

    do
    {
        system("cls");
        printf("*** Programa para Multiplicacao Matricial Paralela ***\n");
        printf("Multiplica cada linha de A por toda Matriz B \n\n");

        printf("\nQuantas linhas na matriz A? => ");
        scanf("%d", &m);

        printf("\nQuantas colunas na matriz A? => ");
        scanf("%d", &n);

        printf("\nQuantas colunas na matriz B? => ");
        scanf("%d", &p);

        geraMatriz(A, m, n);
        mostraMatriz("Matriz A", A, m, n);

        geraMatriz(B, n, p);
        mostraMatriz("Matriz B", B, n, p);

        multiplicaMatriz(A, B, m, n, p);

        for (i = 0; i < m; i++){
            mostraMatriz("1) Matriz (Resultante)", *(result[i]), m, p);
        }

        printf("\nDeseja nova execucao <1>Sim ou <2>Nao? > ");
        scanf("%d", &opcao);
    } while (opcao == 1);
}