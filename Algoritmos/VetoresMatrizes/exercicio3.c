#include<stdio.h>

/*
Escreva um programa que receba os elementos de uma matriz M[4][3] e retorna a soma deles.

PLANEJAMENTO:
-Criar a matriz, e pedir ao usuário os elementos;
-Passar a matrix em um for e adicionar cada elemento a soma;
-apresentar ao usuário a soma;
*/

main(){
   int matriz[4][3], linha, coluna, soma = 0;

    //Recebe os valores do usuário e armazena na martrix;
    for(linha = 0; linha < 4; linha++){
        for(coluna = 0; coluna < 3; coluna ++){
            printf("Digite um valor para a matrix: ");
            scanf("%i", &matriz[linha][coluna]);
        }
    }

    //Varre a matrix e cada elemento é adicionado na soma
    for(linha = 0; linha < 4; linha++){
        for(coluna = 0; coluna < 3; coluna ++){
            soma += matriz[linha][coluna];
        }
    }

    printf("Somas de todos elementos da matrix: %i", soma);

}
