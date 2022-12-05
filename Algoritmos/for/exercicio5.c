#include<stdio.h>
/*
5. Fa̧ca um programa que leia um nome e imprima as 4 primeiras letras do nome.
PLANEJAMENTO
-Ler um nome
-armazenar na variavel que tenha 4 caracter
-Imprimir ao usuário
*/
main (){

    char nome[5]; //varivel com 20 caracteres

    printf("Qual seu nome? ");
    fgets(nome,5,stdin);// pedido o nome e armazenado  somente 5 caracteres levando em conta o \0

    printf("Quatro primeiras letras do seu nome é: %s",nome); //apresentando as 4 letras ao usuário
}
