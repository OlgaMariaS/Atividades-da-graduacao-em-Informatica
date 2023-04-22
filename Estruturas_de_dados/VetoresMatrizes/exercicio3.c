#include<stdio.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo:  Ler 15 elementos de uma matriz A do tipo vetor. Construir uma matriz B de mesmo tipo. Observando a seguinte lei de formação: “Todo elemento de B deverá ser o quadrado do elemento de A correspondente”. Apresentar as matrizes A e B.

PLANEJAMENTO:
-preencher a matriz A, tendo dimensões 3x5;
-percorrer com for a matriz A, multiplicar os elementos por eles mesmo e atribuir a matriz B;
-apresentar B;
*/
void pulaLinha(){
    printf("\n------------------------------\n");
}
main(){
    int A[3][5], B[3][5], l, c, tamL = 3, tamC = 5;

    //Preenche a matriz A
    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            printf("Digite um valor: ");
            scanf("%i", &A[l][c]);
        }   
    }

    pulaLinha();

    //Percorre a matriz A e atribui a B
    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            B[l][c] = A[l][c] * A[l][c];
        }   
    }

    //Apresenta B
    printf("Matriz B \n");

    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            printf(" %i |", B[l][c]);
        }   
    }

}