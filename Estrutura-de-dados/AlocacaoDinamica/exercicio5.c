#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Autor: Olga 
Data: janeiro/2023
Objetivo: Reescreva o programa anterior utilizando desta vez alocação única para alocar a matrizrizriz de 3 dimensões.
*/
main(){
 
    int *matriz;
    int i, j, k;
    int l = 2, c = 2, p = 2;

    // aloca um vetor com todos os elementos da matriz
    matriz = malloc (l * c * p  * sizeof (int)) ;
    //é alocado dentro da matriz a quantidade total de elemento (sendo a multiplicação de l, c, p) x o tamanho de bytes de inteiros 

    //Preenche a matriz 
    for (i = 0; i < l; i++){
        for ( j = 0; j < c; j++){
            for ( k = 0; k < p; k++){
                matriz[(i*j*p)+k] = i+j+k;
            }
        }
    }

    //Mostra para o usuário a matriz final 
    for (i = 0; i < l; i++){
        for ( j = 0; j < c; j++){
            for ( k = 0; k < p; k++){
                printf("l: %i| c: %i| Prof: %i| == %i \n", i, j, k, matriz[(i*j*p)+k]);
            }
        }
    }


}