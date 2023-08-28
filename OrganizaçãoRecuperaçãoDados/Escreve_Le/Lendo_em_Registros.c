#include <stdio.h>
#include <stdlib.h>

//Constantes
#define TAM_CAMPOS 30
#define BARRA '|'

// Implementacao da funcao input, le uma string do stdin e retorna o comprimento da string lida
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
// Implementacao da funcao que le os campos do arquivo
int leia_campo(char *campo, int tam, FILE *entrada){

    int i = 0;
    char ch = fgetc(entrada);
    while (ch != EOF && ch != BARRA)
    {
        if (i < tam-1) {
            campo[i] = ch;
            i++;
        }
        ch = fgetc(entrada);
    }
    campo[i] = '\0';
    return i;
}

int main(){
    // Declaracoes constantes
    char campo[TAM_CAMPOS];
    char nome_arq[TAM_CAMPOS];
    int conta_campo;
    int comprimento;

    printf("Digite o nome do arquivo que quer abrir: ");
    input(nome_arq, TAM_CAMPOS);

    FILE *entrada;
    entrada = fopen(nome_arq, "r");

    if (entrada == NULL) {
        printf("Erro na abertura do arquivo --- programa abortado\n");
        exit(1);
    }

    conta_campo = 0;
    comprimento = leia_campo(campo, TAM_CAMPOS, entrada);
    while (comprimento > 0)
    {
        printf("\tCampo #%d: %s\n", ++conta_campo, campo);
        comprimento = leia_campo(campo, TAM_CAMPOS, entrada);
    }
    
    fclose(entrada);
    return 0;
}


