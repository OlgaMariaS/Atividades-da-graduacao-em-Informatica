#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constantes
#define TAM_CAMPOS 250
#define TAM_OPERACAO 2
#define QUEBRA_DE_LINHA '\n'
#define TAM_ID 5
#define LIMITADOR '|'

// Funcao que le somente o primeiro caracter de cada linha do arquivo_de_operacões, que representa a operação a ser realizada
int leia_operacao(char *campo, FILE *arquivo_de_operacoes){
    int i = 0;
    // leia a 1a letra
    char caracter = fgetc(arquivo_de_operacoes);
    if (caracter != EOF) {
        campo[i] = caracter;
        // finalize a string
        campo[++i] = '\0';
        // leia o espaco em branco após a letra da operacao e descarte
        fgetc(arquivo_de_operacoes);
    }
    return i;
}

// Funcao que le as chaves do arquivo_de_operacões (armazena somente após o digito de operação e espaço até o \n)
void leia_chave(char *campo, int tam, FILE *arquivo_de_operacoes){
    int i = 0;
    char caracter = fgetc(arquivo_de_operacoes);
    while (caracter != EOF && caracter != QUEBRA_DE_LINHA)
    {
        if (i < tam-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(arquivo_de_operacoes);
    }
    campo[i] = '\0';
}

int main(){ //executa_operacoes
    char chave[TAM_CAMPOS];
    char operacao[TAM_OPERACAO];
    
    FILE *arquivo_de_operacoes;
    arquivo_de_operacoes = fopen("arquivo_de_operacoes.txt", "r");

    if (arquivo_de_operacoes == NULL) {
        printf("Erro na abertura do arquivo --- programa abortado\n");
        exit(1);
    }
    
    int comprimento = leia_operacao(operacao, arquivo_de_operacoes);
    leia_chave(chave, TAM_CAMPOS, arquivo_de_operacoes);      
    
    while (comprimento > 0){   
        //*chama a função baseado na operação do arquivo, passando qual chave deve manipular
        if( strcmp(operacao,"b") == 0 ){
            printf("BUSCAR a chave: %s\n", chave);
            //chamar função buscar(chave);
        }else if( strcmp(operacao,"r") == 0 ){
            printf("REMOVER a chave: %s\n", chave);
           // remove(chave);
        }else if( strcmp(operacao,"i") == 0 ){
            printf("INSERIR a chave: %s\n", chave);
            //chamar função inserir(chave);
        }
        
        comprimento = leia_operacao(operacao, arquivo_de_operacoes);
        leia_chave(chave, TAM_CAMPOS, arquivo_de_operacoes);
    }
   
    fclose(arquivo_de_operacoes);
}



