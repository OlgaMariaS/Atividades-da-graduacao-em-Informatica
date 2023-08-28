#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaracoes constantes
#define DELIM_STR "|"
#define TAM_STR 30
#define TAM_MAX_REG 256

// Declaracoes funcoes
short leia_reg(char *, int, FILE*);
int input(char *, int);

// Implementacao da funcao main
int main(){
    FILE *entrada;
    char buffer[TAM_MAX_REG];
    char nome_arq[TAM_STR];
    short comp_reg;
    int achou = 0;
    char * campo;
    char * sobrenome;
    char sobrenome_a_buscar[TAM_STR];
    int conta_campo, conta_reg;

    printf("Digite o nome do arquivo a ser aberto: ");
    input(nome_arq, TAM_STR);

    if ((entrada = fopen(nome_arq, "rb")) == NULL) {
        printf("Erro na abertura do arquivo --- programa abortado\n");
        exit(EXIT_FAILURE);
    }

    printf("Qual o sobrenome deseja buscar: ");
    input(sobrenome_a_buscar,TAM_STR);

    conta_reg = 0;
    comp_reg = leia_reg(buffer, TAM_MAX_REG, entrada);

    while ((comp_reg > 0) && (achou == 0))
    {
        sobrenome = strtok(buffer, "|");

        if(strcmp(sobrenome, sobrenome_a_buscar)==0){
            achou = 1;
        }else{
            comp_reg = leia_reg(buffer, TAM_MAX_REG, entrada);
        }
    }

    if(achou == 1){

        printf("%s \n", sobrenome);
        campo = strtok(NULL, "|");

        while (campo != NULL){
            conta_campo = 0;
            printf("\tCampo %d: %s\n", ++conta_campo, campo);
            campo = strtok(NULL, DELIM_STR);
        }
        printf("\n");
    }else{
        printf("Erro ao ler");
    }

    fclose(entrada);
    return 0;
    }


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

// Implementacao da funcao input
int input(char * str, int size) {
    int i = 0;
    char c = getchar();
    while (c != '\n') {
        if (i < size - 1) {
            str[i] = c;
            i++;
        }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

