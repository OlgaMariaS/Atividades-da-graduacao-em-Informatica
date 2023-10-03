#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libarvb.h"

struct registro {
    short tamanho_chave;
    int chave_primaria; 
    int offset;    
} REGISTRO;

void le_chave(FILE *dados, int offset){

    fseek(dados,offset,SEEK_SET);
    fread(&REGISTRO.tamanho_chave,sizeof(REGISTRO.tamanho_chave),1,dados);
    fseek(dados,(offset+2),SEEK_SET);
    fread(&REGISTRO.chave_primaria,sizeof(REGISTRO.chave_primaria),1,dados);
    REGISTRO.offset = offset+2;
}

void main (){
    //abre o arquivo que o nome deve ser passado por comando
    FILE *dados;
    dados = fopen("dados.dat", "r");


    
}