#include<stdio.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo: Ler uma matriz A de duas dimensões com 6 linhas e 6 colunas. Apresentar o somatório dos elementos na diagonal principal da referida matriz

PLANEJAMENTO:
-preencher uma matriz;
-com um for, percorrer a matriz e se L (linha) for igual a c(coluna), será somado;
-apresentar ao usuário
*/
main(){
    int A[6][6], soma = 0, l, c, tamanho = 6;

    //Preenche a matriz
    for (l = 0; l < tamanho; l++){
        for (c = 0; c < tamanho; c++){
            printf("Digite um valor: ");
            scanf("%i", &A[l][c]);
        }   
    }

    //Percorre a matriz e soma a diagonal principal
    for (l = 0; l < tamanho; l++){
        for (c = 0; c < tamanho; c++){
            if (l == c){
                soma += A[l][c];
            }
        }   
    }

    //Apresentar ao usuário
    printf("Soma da diagonal principal: %i ", soma);
    
}