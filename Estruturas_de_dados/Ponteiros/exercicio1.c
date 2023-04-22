#include<stdio.h>
#include<stdlib.h>
/*
Autor: Olga
Data: dezembro/2022
Objetivo:  Escreva um programa que declare um inteiro, um real e um char, e ponteiros para inteiro, real, e char.  Associe as varia´veis aos ponteiros (use &).  Modifique os valores de cada  varia´vel  usando  os  ponteiros.   Imprima  os  valores  das  variaeveis  antes  e  apos  a modificacao.

PLANEJAMENTO:
-receber os valores do usuário;
-atribuir os valores a ponteiros;
-alterar o valor pelos ponteiros, pedindo o valor ao usuário;
-mostrar na tela o valor final
*/
void pulaLinha(){
    printf("\n------------------------------\n");
}
main(){
    int inteiro, *pInteiro;
    float real, *pReal;
    char caracter[1], *pCaracter;

    printf("Digite um valor inteiro: ");
    scanf("%i", &inteiro);
    printf("Digite um valor real: ");
    scanf("%f", &real);
    printf("Digite um caracter: ");
    scanf("%s", &caracter);

    pulaLinha();

    pInteiro = &inteiro;
    pReal = &real;
    pCaracter = &caracter;

    printf("Digite um novo valor inteiro: ");
    scanf("%i", pInteiro);
    printf("Digite um novo valor real: ");
    scanf("%f", pReal);
    printf("Digite um novo caracter: ");
    scanf("%s", pCaracter);

    pulaLinha();

    printf("Inteiro: %i \n", inteiro);
    printf("Real: %.2f \n", real);
    printf("Caracter: %s \n", caracter);
    
}