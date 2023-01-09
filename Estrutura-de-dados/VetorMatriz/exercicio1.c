#include<stdio.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo: Ler uma matriz A de duas dimensões com tamL linhas e 7 colunas. Ao final  apresentar o total de elementos pares e o total de elementos impares existentes dentro da matriz. Apresentar tamLbém o percentual de elementos pares e impares  em  relação ao total de elementos da matriz. Supondo a existência de 20 elementos pares e 50 elementos impares, ter-se-ia 28,5% de elementos pares e 71,5% de elementos impares.

PLANEJAMENTO:
-Crias a matriz, e pedir que o usuário preencha;
-com um for ler a matriz, e contabilizar quantidade de elementos que dividem 2, e mostra-los na tela;
-com outros for contabilizar a quantidade que não divide dois e mostra-la na tela como impares;
-fazer os calculos de porcentagem, sabendo a qtde de impares e pares, e total de elementos que é 70 e mostrar ao usuário;
*/

void pulaLinha(){
    printf("\n------------------------------\n");
}
main(){
    int A [3][3], qtdeImpar = 0, qtdePar = 0, qtdeTotal = 70, l, c, tamL = 10, tamC = 7;
    float percentualImpar, percentualPar;

    //Preencher matriz
    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            printf("Digite um valor: ");
            scanf("%i", &A[l][c]);
        }
    }

    pulaLinha();

    //Contabilizar e mostrar valores pares
    printf("Numeros Pares: ");
    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            if ( (A[l][c] % 2) == 0 ){
                printf(" %i |", A[l][c]);
                qtdePar++;
            }   
        }
    }

    pulaLinha();

    //Contabilizar e mostrar valores impares
    printf("Numeros Impares: ");
    for (l = 0; l < tamL; l++){
        for (c = 0; c < tamC; c++){
            if ( (A[l][c] % 2) != 0 ){
                printf(" %i |", A[l][c]);
                qtdeImpar++;
            }
        }
    }

    pulaLinha();

    //Calculo do percentual de valores pares e impares
    percentualImpar = (qtdeImpar * 100) / qtdeTotal ;
    percentualPar = (qtdePar * 100) / qtdeTotal;

    printf("Percentual de valores pares: %.2f ", percentualPar);
    pulaLinha();
    printf("Percentual de valores impares: %.2f ", percentualImpar);

}