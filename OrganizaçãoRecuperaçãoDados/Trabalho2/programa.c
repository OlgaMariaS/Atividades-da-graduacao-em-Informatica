#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libarvb.h"

#define ORDEM 5
#define NULO -1
#define TAMBUFFER 500
#define LIMITADOR "|"

void gerenciadora(int RAIZ){
    int i = 0;
    int qtde_registros;
    int *chave;
    int *offset;
    int *filho_d_pro;
    int *chave_pro;
    int *offset_pro;
    PAGINA *novapag;
    
    FILE *dados;

    //e que ele armazenará o total de registros do arquivo no cabeçalho como um número inteiro.
    rewind(dados);
    fread(&qtde_registros,sizeof(qtde_registros),1,dados);

   // leia_chave(dados, chave, offset);

    while ((i < qtde_registros)){
        if((insere(RAIZ, chave,offset, filho_d_pro, chave_pro, offset_pro)) == PROMOCAO){

            inicializa_pagina(*novapag);
            novapag->chaves[i] = chave_pro;
            novapag->offset[i] = offset_pro;
            novapag->filhos[i] = RAIZ;
            novapag->filhos[i+1] = filho_d_pro;
            novapag->num_chaves++;
            RAIZ = novo_rrn();
            escreve_pagina(RAIZ, novapag);
        }   
        leia_chave(dados); // --> deve retornar o byteoffset e a chave lida, passar por parametros
    }
    fseek(arvb,0,SEEK_SET);
    fwrite(RAIZ, sizeof(RAIZ), 1, arvb); 
}
/*
    Lê as chaves a serem armazenadas na árvore-B e chama a função
    insere()
    – Cria uma nova raiz quando houver divisão da raiz atual
    • Quando a função insere() retornar PROMOÇÃO
    • Cria a página que será a nova raiz
    • Atualiza o RRN da raiz*/

int main(){
    CABECALHO raiz;
    PAGINA *pag;
    FILE *dados;
    FILE *arvb;

    dados = fopen("dados.dat", "r+w");
    arvb = fopen("btree.dat", "r+w");

    //Criação de uma pagina em branco
    raiz.rrn_raiz = 0;
    rewind(arvb);
    fwrite(&raiz.rrn_raiz, sizeof(raiz.rrn_raiz), 1, arvb); 
    inicializa_pagina(*pag);
    escreve_pagina(raiz.rrn_raiz, pag);

    gerenciadora(raiz.rrn_raiz);

    fclose(dados);
    fclose(arvb);
}
