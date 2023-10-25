#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaracoes constantes
#define DELIM_STR "|"
#define TAM_STR 30
#define TAM_MAX_REG 256

// Implementacao da funcao leia_reg
short leia_reg(char * buffer, int tam, FILE * arq){
    short comp_reg;

    if (fread(&comp_reg, sizeof(comp_reg), 1, arq) == 0) {
        return 0;
    }
    if (comp_reg < tam) {
        fread(buffer, sizeof(char), comp_reg, arq);
        buffer[comp_reg] = '\0';
        return comp_reg;
    } else {
        printf("Buffer overflow\n");
        return 0;
    }
}

// Implementacao da funcao main
int main(){
    FILE *dados;
    int offset = 4; 
    int i = 0;
    int qtde_reg;
    char buffer[TAM_MAX_REG];
    int chave;
    char * campo;
    short tamanho;

    dados = fopen("dados10.dat", "r");

    //armazena o tamanho do 1° registro
    fseek(dados, 0,SEEK_SET);
    fread(&qtde_reg,sizeof(qtde_reg),1,dados);
    
    while(i <= qtde_reg){

        fseek(dados, offset,SEEK_SET);
        tamanho = leia_reg(buffer, TAM_MAX_REG, dados);
        campo = strtok(buffer, DELIM_STR);
        chave = atoi(campo);
        
        printf("chave: %i \n", chave);
        offset = offset + tamanho + sizeof(tamanho);
        i++;
    }
    
    fclose(dados);
    return 0;
}


