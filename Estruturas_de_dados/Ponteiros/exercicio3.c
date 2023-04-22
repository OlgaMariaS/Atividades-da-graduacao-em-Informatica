#include<stdio.h>
#include<stdlib.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo:  Escreva  um  programa  que  contenha  duas  variaveis  inteiras.   Leia  essas  variaveis  do teclado. Em seguida, compare seus enderecos e exiba o conteudo do maior endereco.

PLANEJAMENTO:
-receber dois valores inteiros;
-atribuir eles a ponteiros;
-comparar os ponteiros em if, com *;
-mostrar ao usuário qual variavel tem maior endereço
*/

main(){
    int n1, n2, *pN1, *pN2;

    printf("Digite um valor: ");
    scanf("%i", &n1);
    printf("Digite um valor: \n");
    scanf("%i", &n2);

    pN1 = &n1;
    pN2 = &n2;

    if (pN1 > pN2)
    {
        printf("O endereco da variavel N1 e maior");
    }else{
        printf("O endereco da variavel N2 e maior");
    }
    
}