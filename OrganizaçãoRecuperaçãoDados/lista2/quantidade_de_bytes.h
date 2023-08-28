#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Faça um programa que solicite ao usuário o nome de um arquivo de texto e então calcule e apresente o
seu tamanho em bytes e o número de linhas.*/

int quantidade_de_bytes(char nome[]){
    int bytes = 0;
    FILE *arquivo;
  
    arquivo = fopen(nome,"rb");

    if((arquivo == NULL)){
        printf("Erro ao gerar arquivo");
        exit(1);
    }

    while (fgetc(arquivo) != EOF) {
        ++bytes;
    }

    if (feof(arquivo)) {
       // puts("End-of-File reached.");
        printf("Tamanho dem bytes do nome do seu arquivo e: %i ", bytes);
    }

    fclose(arquivo);
}
