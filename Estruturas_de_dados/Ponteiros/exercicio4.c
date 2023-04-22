#include<stdio.h>
#include<stdlib.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo:  Faca um programa que leia 2 valores inteiros e chame uma funcao que receba estas 2 variaveis e troque o seu conteudo,  ou seja,  esta funcao e  chamada passando duas variáveis A e B por exemplo e, apos a execucao da funcao, A contera  o valor de B e B tera o valor de A.

PLANEJAMENTO:
-receber ddois valores;
-chamar a função e passar o parametro;
-dentro da função, trocaremos o apontamento do ponteiro, ou seja se o ponteiro aponta para B, ele vai passar a apontar a A, e se aponta para A. vai passar a apontar para B.
-mostrar ao usuário 
*/
void troca(int *pA, int *pB){

    int Xa, Xb;
    Xa = *pB;
    Xb = *pA;

    printf("\nValor de A, substituido: %i ", Xa);
    printf("\nValor de B, substituido: %i ", Xb);
}

main(){
    int A, B;

    printf("Digite A: ");
    scanf("%i", &A);
    printf("Digite B: ");
    scanf("%i", &B);

    troca(&A, &B);

}