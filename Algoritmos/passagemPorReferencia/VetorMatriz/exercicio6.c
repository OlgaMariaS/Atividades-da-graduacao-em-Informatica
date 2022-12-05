#include<stdio.h>
/*
Faça um programa que passe uma matriz 5x5 e um vetor de tamanho 5 por parametro para uma função. Esta função deve  armazenar a diagonal principal da matriz no vetor. Quando finalizar a execução da fução imprima os valores do vetor.
PLANEJAMENTO:
-Receber uma matriz do usuário por for;
-criar um vetor com tamanho 5;
- envia o vetor e a matriz a uma função, que percorrerá a matriz, se encontrar a linha e a coluna forem iguais, este elemento será atribuido ao vetor;
- apresentar ao usuário;
*/
void diagonalPrincipal (int matriz[][5], int linha, int vetor[],int tamanhoVetor){

    for (int l = 0; l < 5; l++){
        for (int c = 0; c < 5; c++){
            if (c == l){
                vetor[l] = matriz[l][c];
            }
        }
    }

    printf("\n Diagonal principal: ");
    for (int i = 0; i < tamanhoVetor; i++){
        printf("%i|", vetor[i]);
    }
}

main(){
    int matrizMain[5][5], vetorMain[5];

    for (int l = 0; l < 5; l++){
        for (int c = 0; c < 5; c++){
            printf("Informe um valor: ");
            scanf("%i", &matrizMain[l][c]);
        }
    }

    diagonalPrincipal(matrizMain,5, vetorMain, 5);
    

}