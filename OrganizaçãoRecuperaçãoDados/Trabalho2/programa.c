#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libarvb.h"

#define ORDEM 5
#define NULO -1
#define TAMBUFFER 500
#define LIMITADOR "|"

struct cabecalho {
    int rrn_raiz; //vai guardar o rrn da pagina raiz, mas o rrn não pode mudar? 
} CABECALHO;

struct pagina {
    int num_chaves; /* número de chaves na página */
    int chaves[ORDEM-1]; /* vetor com as chaves primarias SÃO INTEIRO OU CHARS?*/
    int offset[ORDEM-1];
    int filhos[ORDEM]; /* vetor com os RRNs dos filhos */
} PAGINA;

struct registro {
    short tamanho_chave;
    int chave_primaria; 
    int offset;    
} REGISTRO;

void gerenciadora(int RAIZ){


}

void main(char *nome_arq_indice){
    FILE *indice;
  
    if(nome_arq_indice != NULL){
        indice = fopen(nome_arq_indice, "r+w");
        rewind(indice);
        fread(&CABECALHO.rrn_raiz, sizeof(CABECALHO.rrn_raiz), 1, indice); 
    }else{
        indice = fopen(nome_arq_indice, "r+w");
        CABECALHO.rrn_raiz = 0;
        rewind(indice);
        fwrite(&CABECALHO.rrn_raiz, sizeof(CABECALHO.rrn_raiz), 1, indice);

        //fwrite(&inicializa_pagina(PAGINA), sizeof(PAGINA), 1, indice);
    }
    gerenciador(CABECALHO.rrn_raiz);
    fclose(indice);
}
