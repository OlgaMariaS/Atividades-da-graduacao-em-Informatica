#include<stdio.h>
#include<stdlib.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo:   Faca um programa que leia dois valores inteiros e chame uma funcao que receba estes 2  valores  de  entrada  e  retorne  o  maior  valor  na  primeira  variavel  e  o  menor  valor  na segunda variavel. Escreva o conteudo das 2 variaveis na tela.

PLANEJAMENTO:
-ler dois valores dados pelo usuário;
-chamar a função troca,e passar os parametros os valores digitados pelo usuário, mas em forma de ponteiros;
-se o valor apontado por pA é maior que pB, ele será apresentado em A, se não será apresentado em B.
*/
void troca(int *pA, int *pB){

    int maior, menor;

    if (*pA > *pB){
        maior = *pA;
        menor = *pB;
        
    }else{
        maior = *pB;
        menor = *pA;
    }

    printf("\nPrimeira variavel: %i ", maior);
    printf("\nSegunda variavel: %i ", menor);
}

main(){
    int A, B;

    printf("Digite um primeiro valor: ");
    scanf("%i", &A);
    printf("Digite um segundo valor: ");
    scanf("%i", &B);

    troca(&A, &B);

}