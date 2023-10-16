#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libarvb.h"

#define ORDEM 5
#define NULO -1
#define TAMBUFFER 500
#define LIMITADOR "|"
#define TAM_STR 30
#define TAM_MAX_REG 256

//Função que armazena um registro no buffer
short leia_reg(char * buffer, int tam, FILE * dados){
    short comp_reg;

    if (fread(&comp_reg, sizeof(comp_reg), 1, dados) == 0) {
        return 0;
    }
    if (comp_reg < tam) {
        fread(buffer, sizeof(char), comp_reg, dados);
        buffer[comp_reg] = '\0';
        return comp_reg;
    } else {
        return 0;
    }
}
/*  Lê as chaves a serem armazenadas na árvore-B e chama a função
    insere()
    – Cria uma nova raiz quando houver divisão da raiz atual
    • Quando a função insere() retornar PROMOÇÃO
    • Cria a página que será a nova raiz
    • Atualiza o RRN da raiz*/
void gerenciadora(int RAIZ, FILE *dados){
    int i = 0;
    int chave;
    int offset = 4;
    int *filho_d_pro;
    int *chave_pro;
    int *offset_pro;
    int qtde_reg;
    char buffer[TAM_MAX_REG];
    char *campo;
    short tamanho;
    PAGINA novapag;
    
    //armazena o tamanho do 1° registro
    rewind(dados);
    fread(&qtde_reg,sizeof(qtde_reg),1,dados);

    while (i <= qtde_reg){

        fseek(dados, offset,SEEK_SET);
        tamanho = leia_reg(buffer, TAM_MAX_REG, dados);
        campo = strtok(buffer, LIMITADOR);
        chave = atoi(campo);
        
        if(insere(RAIZ, chave, offset, filho_d_pro, chave_pro, offset_pro) == PROMOCAO){

            inicializa_pagina(novapag);
            novapag.chaves[i] = *chave_pro;
            novapag.offset[i] = *offset_pro;
            novapag.filhos[i] = RAIZ;
            novapag.filhos[i+1] = *filho_d_pro;
            novapag.num_chaves++;
            RAIZ = novo_rrn();
            escreve_pagina(RAIZ, &novapag);
        }   
        offset = offset + tamanho + sizeof(tamanho);
        i++;
    }
    rewind(dados);
    fwrite(RAIZ, sizeof(RAIZ), 1, arvb); 
}

int main(){
    CABECALHO raiz;
    PAGINA pag;
    FILE *dados;

    dados = fopen("dados.dat", "r+w");
    arvb = fopen("btree.dat", "r+w");
    
    //Criação de uma pagina em branco
    raiz.rrn_raiz = 0;
    rewind(arvb);
    fwrite(&raiz.rrn_raiz, sizeof(raiz.rrn_raiz), 1, arvb); 
    inicializa_pagina(pag);
    escreve_pagina(raiz.rrn_raiz, &pag);

    gerenciadora(raiz.rrn_raiz, dados);

    fclose(dados);
    fclose(arvb);
}
