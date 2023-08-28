#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short leia_reg(FILE* arq){
    int acumulador = 6;
    char comp_reg;

    fseek(arq,acumulador, SEEK_SET);

    comp_reg = fgetc(arq);
    printf("%c",comp_reg);
    return 0;
}

int main(){
    FILE *dados;
    dados = fopen("dados.dat", "r");
    
    if (dados == NULL) {
        printf("Erro na abertura do arquivo --- programa abortado\n");
        exit(1);
    }

    leia_reg(dados);
}