#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Autor: Olga 
Data: janeiro/2023
Objetivo: Utilizando alocação dinâmica, escreva um programa que aloca uma matriz de 3 dimensões e preenche cada elemento dessa matriz com a soma dos índices do elemento. Por exemplo, Matriz[1][2][3] = 1 + 2 + 3 = 6

PLANEJAMENTO:
-Criar as matrizes com 3 dimensões;
-um for percorre a matriz, e baseandona ideia de uma cubo,  vai somar a linha + coluna + profundidade, e atribuir a aquele endereço da matriz
-Mostrar ao usuário a matriz preenchida;
*/
main(){
    //declarando matriz com 3 dimensões
    int ***matriz;
    int i, j, k;
    int linha = 3, coluna = 3, profundidade = 3;
    //Criar as linhas da matriz, apontando para ponteiros de ponteiros
    matriz = malloc ( linha * sizeof( int **));

    //Cria as colunas, aponta para ponteiros
    for ( i = 0; i < coluna; i++){
        matriz[i] = malloc ( coluna * sizeof(int *));
    }

    //Cria a profundidade
    for ( i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            matriz[i][j] = malloc ( profundidade * sizeof( int ));
        }
    }
    
    //-------------------------------------------------------------
    //Preenche a matriz 
    for (i = 0; i < linha; i++){
        for ( j = 0; j < coluna; j++){
            for ( k = 0; k < profundidade; k++){
                matriz[i][j][k] = i+j+k;
            }
        }
    }

    //Mostra para o usuário a matriz final 
    for (i = 0; i < linha; i++){
        for ( j = 0; j < coluna; j++){
            for ( k = 0; k < profundidade; k++){
                printf("Linha: %i| Coluna: %i| Prof: %i| == %i \n", i, j, k, matriz[i][j][k]);
            }
        }
    }
    
}
    