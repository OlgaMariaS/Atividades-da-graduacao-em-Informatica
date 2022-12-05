#include<stdio.h>

/*
Escreva um programa que contenha uma função para ler 7 n ́umeros do usu ́ario e retorne quantos ńumeros s ̃ao maiores do que 8.
PLANEJAMENTO:
-Receber 7 numeros do usuário por meio do for;
-se o numero for maior que 8, será adiciona 1 na variavel AUXILIAR;
-Apresentar ao usuário a quantidade maior que 8;
*/
int maior(){

    int i, numero, qtdeMaiorOito;

    for(i = 1; i <= 7; i++){

        printf("Digite um numero: ");
        scanf("%i", &numero);

        if(numero > 8){
           qtdeMaiorOito++;
        }
    }

    return qtdeMaiorOito;
}
main(){

    int qtdeMaior;

    qtdeMaior = maior();

    printf("Quantidade de valores maiores que 8 e de: %i ", qtdeMaior);


}
