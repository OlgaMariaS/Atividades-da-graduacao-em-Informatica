#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Autor: Olga 
Data: janeiro/2023
Objetivo: Um quadrado mágico é uma matriz com números distintos na qual a soma dos elementos de cada linha, coluna e diagonal é igual. Elabore um algoritmo que encontre e imprima na tela quando é um quadrado mágico de tamanho 3x3.

PLANEJAMENTO:
-criar as matrizes de forma dinamica;
-pedir que o usuário preenche a matriz;
-primeiro somar a diagonal;
-se a soma da diagonal for igual a da linha e da coluna o programa para;
-se soma da primeira linha for igual a da diagonal, ai fará a soma das coluna -e se esta também for igual, será um quadrado magico;
*/
void pulaLinha(){
    printf("______________________\n");
}
main(){

    int **matriz; // criação de um ponteiro de duas dimensões (linhas e colunas)
    int dimensao = 2;
    int soma = 0;
    int auxiliar = 15;
    int tamanho = 3, i, j;

    //a variavel matriz cria um vetor de ponteiros, com a primeira dimensão, sendo as linhas 
    matriz = malloc ( tamanho * sizeof( int *));

    for (i=0; i < tamanho; i++){
        //Cria colunas para cada linha da matriz, com tipos inteiros 
        matriz[i] = malloc (tamanho * sizeof(int));
    }

    //Preenche a matriz
    
    for(i = 0; i < tamanho; i++){
        for (j=0; j < tamanho; j++){
            printf("Posicao [%i][%i]: ", i, j);
            scanf("%i", &matriz[i][j]);
        }
    }

    pulaLinha();
    //-------------------------------------------------------------------

    //Verificação se é ou não quadrado mágico 

    //Diagonal principal
    for ( i = 0; i < tamanho; i++){
        soma += matriz[i][i];
        //soma dos elementos cujos os indices são iguais, ou seja 0x0, 1x1, 2x2
    }
    printf("Soma da diagonal principal %i \n", soma);

    auxiliar = soma;

    if( soma == auxiliar ){
       
        //Calculo das linhas 
        for (i=0; i < tamanho; i++){
            soma = 0;
            for (j=0; j < tamanho; j++){
                soma += matriz[i][j];  
            }
            printf("total da %i linha: %i \n", i, soma);

            if (auxiliar != soma){
                printf(" Nao e um quadrado magico! \n");
                exit(1);
            }
        }       

        //Calculo das colunas  
        for (i=0; i < tamanho; i++){
            soma = 0;
            for (j=0; j < tamanho; j++){
                soma += matriz[j][i];  
            }
            printf("total da %i coluna: %i \n", j, soma);

            if (auxiliar != soma){
                printf(" Nao e um quadrado magico! \n");
                exit(1);
            }
        }
        pulaLinha();
        printf("Esta matriz eh um quadrado magico \n");
    
    }else {
        printf(" Nao e um quadrado magico! ");
        exit(1);
    }
}