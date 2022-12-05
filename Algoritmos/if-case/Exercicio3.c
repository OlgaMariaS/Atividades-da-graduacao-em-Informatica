#include <stdio.h>

/*
Faca um programa que leia as 4 idades e informe a idade mais velha,
e utilize SOMENBTE uma função que retorne O maior entre os dois numeros para ajudar resolver o problema

PLANEJAMENTO
-receber 4 variaveis, e adiciona-las as idades;
-função com if, que receberá DUAS idades;
-igualar as idades e armazena a maior;
-comparar a maior a 3° idade e armazenar a maior;
-comparar a 4° idade e apresentar a maior;
*/
int maior(int valor1, int valor2){

    if(valor1 > valor2){
      return valor1;
    }else{
        return valor2;
    }
}
int main(){
    int idade1, idade2, idade3,idade4, auxiliar1, auxiliar2, auxiliar3, maiorIdade;

    printf("Informa a primeira idade ");
    scanf("%i", &idade1);
    printf("Informa a primeira idade ");
    scanf("%i", &idade2);
    printf("Informa a primeira idade ");
    scanf("%i", &idade3);
    printf("Informa a primeira idade ");
    scanf("%i", &idade4);

    auxiliar1 = maior(idade1, idade2);
    auxiliar2 = maior(auxiliar1, idade3);
    maiorIdade = maior(auxiliar2, idade4);

    printf("Maior valor e: %i", maiorIdade);
}
