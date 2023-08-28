#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ID 5
#define LIMITADOR '|'

void le_identificador(char *campo, FILE *dados, int acumulador){
    fseek(dados,acumulador, SEEK_SET);
    int i = 0;
    char caracter = fgetc(dados);
    while (caracter != LIMITADOR)
    {
        if (i < TAM_ID-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(dados);
    }
    campo[i] = '\0';
}

void le_tamanho_do_registro(FILE *dados, char *chave_a_encontrar){
    #define bytes_do_tamanho 2
    int acumulador = 4;
    short tamanho_registro;
    short achou = 0;
    char chave_primaria[TAM_ID];

    while(achou != 1){

        fseek(dados,acumulador, SEEK_SET);
        fread(&tamanho_registro, sizeof(tamanho_registro), 1, dados);

        acumulador += bytes_do_tamanho;
        fseek(dados, acumulador, SEEK_SET);
        le_identificador(chave_primaria, dados, acumulador);

        if(strcmp(chave_primaria,chave_a_encontrar) == 0){
            printf("Chave encontrada: %s", chave_primaria);
            achou = 1;
        }else{
            acumulador += tamanho_registro;
            achou = 0;
        }
    }
}

int main(){
    char chave[TAM_ID] = "71";

    FILE *dados;
    dados = fopen("dados.dat", "r");
    
    le_tamanho_do_registro(dados, chave);
}