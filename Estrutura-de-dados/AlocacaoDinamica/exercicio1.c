#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Autor: Olga 
Data: dezembro/2022
Objetivo: Utilizando alocação dinâmica de matrizes, escreva um programa para receber duas matrizes de tamanho 3x3 e calcular seu produto.

*/
void pulaLinha(){
    printf("------------------------\n");
}
main(){

    //Variaveis
    int *matriz1, *matriz2, *matriz3;
    int i, j, l = 3, c = 3;

    //Declarando as matrizes dinamicas
    matriz1 = malloc (l * c * sizeof (int));
    matriz2 = malloc (l * c * sizeof (int));
    matriz3 = malloc (l * c * sizeof (int));

    //Criação das matrizes e pedindo ao usuário os valores 

    //Matriz 1
    printf("Digite os valores da matriz 1 \n");
    for (i=0; i < l; i++){
        for (j=0; j < c; j++){
            printf("Posicao [%i][%i]: ", i, j);
            scanf("%i", &matriz1[(i*c) + j]);
        }
    }
    pulaLinha();

    //Matriz 2
    printf("Digite os valores da matriz 2 \n");
    for (i=0; i < l; i++){
        for (j=0; j < c; j++){
            printf("Posicao [%i][%i]: ", i, j);
            scanf("%i", &matriz2[(i*c) + j]);
        }
    }
    pulaLinha();

    //Matriz 3
    printf("Matriz 3 \n");
    for (i=0; i < l; i++){
        for (j=0; j < c; j++){
            
            // a matriz 3 recebe a multiplicação da matriz 1 e 2 e é mostrado na tela esta multiplicação
            matriz3[(i*c) + j] = matriz1[(i*c) + j] * matriz2[(i*c) + j];

            printf(" %i x %i = %i \n ", matriz1[(i*c) + j], matriz2[(i*c) + j], matriz3[(i*c) + j]);
        }
    }

}