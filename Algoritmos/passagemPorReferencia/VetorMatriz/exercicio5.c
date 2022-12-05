#include<stdio.h>
/*
Faca uma função que receba uma matriz 3x3 e retorne o maior elemento da matriz.
PLANEJAMENTO:
-Criar uma matriz 3x3, e receber os valores do usuário por meio de for;
-chamar a função que encontra o MAIOR, e passa a matriz de parametro;
-dentro da função, vai ser percorrido a matriz, e se o numero for maior que o maior, será atribuido a ele;
-apresentar ao usuário o maior valor;
*/
void maior (int matriz[][3], int linha){
    int maior = 0;
    
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < 3; j++){
            if (matriz[i][j] > maior)
            {
                maior = matriz[i][j];
            }
        }
    }

    return printf("O maior elemento da matriz e: %i", maior);
}

main(){
    int matrizMain[3][3];

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            printf("Informe um valor para a matriz: ");
            scanf("%i", &matrizMain[i][j]);
        }
        
    }

    maior(matrizMain, 3);
    
}