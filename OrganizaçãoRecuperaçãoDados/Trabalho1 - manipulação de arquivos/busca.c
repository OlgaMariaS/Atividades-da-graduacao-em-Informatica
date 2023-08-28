#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ID 5
#define LIMITADOR '|'
#define bytes_do_tamanho 2
#define TAM_CAMPOS 256
#define QUEBRA_DE_LINHA '\n'

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

void le_identificador(char *campo, FILE *dados, int byteOffset){
    fseek(dados,byteOffset, SEEK_SET);
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

void buscar(FILE *dados, char *chave_a_encontrar, char *operacao){
    int byteOffsett = 4; 
    short tamanho_registro;
    short achou = 0; 
    char chave_primaria[TAM_ID];

    while(achou != 1){
        fseek(dados,byteOffsett, SEEK_SET); 
        fread(&tamanho_registro, sizeof(tamanho_registro), 1, dados);

        byteOffsett += bytes_do_tamanho; 
        fseek(dados, byteOffsett, SEEK_SET);
        le_identificador(chave_primaria, dados, byteOffsett); 

        if(strcmp(chave_primaria,chave_a_encontrar) == 0){
            if(strcmp(operacao,"b") == 0){
                char registro[tamanho_registro];

                leia_chave(registro, tamanho_registro, dados);
                printf("Busca pelo registro de chave %s\n", chave_primaria);
                
                //fseek(dados, byteOffsett, SEEK_SET);
                printf("%s|%s", chave_primaria, registro);
                printf(" (%i bytes) \n\n", tamanho_registro);

            }else if((strcmp(operacao,"i")) == 0){
                printf("Insercao do registro de chave '%s' (%i bytes)\n", chave_primaria,tamanho_registro);
                printf("Local: Offsett = %i ", byteOffsett);
            }
            achou = 1;
        }else{
            byteOffsett += tamanho_registro;
            achou = 0;
        }
    }
}

int main(){
    char chave[TAM_ID] = "20";

    FILE *dados;
    dados = fopen("dados.dat", "r+");
    
    buscar(dados, chave, "i");

    fclose(dados);
}