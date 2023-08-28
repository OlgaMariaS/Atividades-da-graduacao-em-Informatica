#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quantidade_de_bytes.h"

/*Faça um programa que solicite ao usuário o nome de um arquivo de texto e então calcule e apresente o
seu tamanho em bytes e o número de linhas.*/
int input(char str[], int size) {
    int i = 0;
    char c = getchar();

    while (c != '\n') {
        if (i < size-1) {
        str[i] = c;
        i++;
    }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

int main( ){
    char l[50];
    
    printf("Qual nome do arquivo deseja abrir: ");
    input(l, 50);

    quantidade_de_bytes(l);
}