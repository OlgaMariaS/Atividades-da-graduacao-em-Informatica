#ifndef ARVB_H_INCLUDED
#define ARVB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declarações
#define ORDEM 5
#define NULO -1
#define TAMBUFFER 500

typedef struct _cabecalho {
    int rrn_raiz;
} CABECALHO;

typedef struct _pagina {
    int num_chaves;
    int chaves[ORDEM-1];
    int offset[ORDEM-1];
    int filhos[ORDEM];
} PAGINA;

// possiveis retornos das funções relacionadas a insercao
enum {SEM_PROMOCAO, PROMOCAO, ERRO};

// possiveis retornos das funções relacionadas a busca
enum {NAO_ENCONTRADO, ENCONTRADO};

// ponteiro do arquivo btree.dat
extern FILE * arvb;

// Funções
int le_pagina(int rrn, PAGINA *pag){
    //Byte-offset = tamanho do cabeçalho + RRN * tamanho do registro
    int byte_offset = sizeof(int) + (rrn * sizeof(pag));
    fseek(arvb, byte_offset, SEEK_SET);
    fread(&pag, sizeof(pag), 1, arvb); 
}

int escreve_pagina(int rrn, PAGINA *pag){
    //Byte-offset = tamanho do cabeçalho + RRN * tamanho do registro
    int offset = sizeof(int) + (rrn * sizeof(pag));
    fseek(arvb, offset, SEEK_SET);
    fwrite(&pag, sizeof(pag), 1, arvb); 
}

int novo_rrn(){
    int TAMANHOPAG;
    int TAMANHOCAB;
    int BYTEOFFSET;

    TAMANHOPAG = sizeof(PAGINA);
    TAMANHOCAB = sizeof(int);
    fseek(arvb, 0, SEEK_END);
    BYTEOFFSET = ftell(arvb);

    return ((BYTEOFFSET - TAMANHOCAB)/TAMANHOPAG);
}

void inicializa_pagina(PAGINA pag){ // preciso usar ponteiro?? PAGINA *pag
    int i;
    pag.num_chaves = 0;

    for(i = 0; i < ORDEM-1; i++){
        pag.chaves[i] = NULO;
        pag.offset[i] = NULO;
        pag.filhos[i] = NULO;
    }
    pag.filhos[i] = NULO;
}

void insere_na_pagina(int chv_pro, int off_pro, int rrn_pro, int chaves[], int offset[], int filhos[], int *num_chaves){
    int i = *num_chaves;

    while((i > 0) && (chv_pro < chaves[i-1])){
        chaves[i] = chaves[i-1];
        offset[i] = offset[i-1];
        filhos[i+1] = filhos[i];
        i--;
    }
    num_chaves++;
    chaves[i] = chv_pro;
    offset[i] = off_pro;
    filhos[i+1] = rrn_pro;
}

void divide(int chave_i,int off_i, int rrn_i, PAGINA *pag, int *chave_pro, int *filho_d_pro, PAGINA *novapag){
    int MEIO = ORDEM / 2;
    int i = 0;
    PAGINA PAGAUX;

    PAGAUX.num_chaves = pag->num_chaves;
    for(i = 0; i < pag->num_chaves;i++){
        PAGAUX.chaves[i] = pag->chaves[i];
        PAGAUX.offset[i] = pag->offset[i];
        PAGAUX.filhos[i] = pag->filhos[i];
    }
        PAGAUX.filhos[i+1] = pag->filhos[i+1];
    
    insere_na_pagina(chave_i, off_i, rrn_i,PAGAUX.chaves, PAGAUX.offset, PAGAUX.filhos, &PAGAUX.num_chaves);
   
    *chave_pro = PAGAUX.chaves[MEIO];
    //faça filho_d_pro receber o RRN que o NOVAPAG terá no arquivo árvore-b
    *filho_d_pro = novo_rrn();   

    /* Copie as chaves e ponteiros que vêm antes de CHAVE_PRO para PAG */
    inicializa_pagina(*pag);

    for(i = 0; i < MEIO; i++){
        pag->chaves[i] = PAGAUX.chaves[i];
        pag->offset[i] = PAGAUX.offset[i];
        pag->filhos[i] = PAGAUX.filhos[i];
        pag->num_chaves++;
    }
    pag->filhos[i] = PAGAUX.filhos[i];

/* Copie as chaves e ponteiros que vêm depois de CHAVE_PRO para NOVAPAG */
    inicializa_pagina(*novapag);

    for(i = 0; i < ORDEM; i++){
        novapag->chaves[novapag->num_chaves] = PAGAUX.chaves[i];
        novapag->offset[novapag->num_chaves] = PAGAUX.offset[i];
        novapag->filhos[novapag->num_chaves] = PAGAUX.filhos[i];
        novapag->num_chaves++;
    }
    novapag->filhos[novapag->num_chaves]= PAGAUX.filhos[i];

}

int insere(int rrn_atual, int chave, int offset, int *filho_d_pro, int *chave_pro, int *offset_pro){
    int *rrn_pro;
    int *chv_pro;
    int *off_pro;
    int POS;
    int ACHOU;
    int RETORNO;
    PAGINA *novapag;
    PAGINA *pag;

    if(rrn_atual == NULO){
        *chave_pro = chave;
        *filho_d_pro = NULO;
        return PROMOCAO;
    }else{
        le_pagina(rrn_atual, &pag);
        ACHOU = busca_na_pagina(chave, *pag, &POS);
    }
    
    if(ACHOU == 0){
        printf("Erro: chave '%i' ja existente", chave);
        return ERRO;
    }
                                           
    RETORNO = insere(pag->filhos[POS], chave, offset, rrn_pro, chv_pro, off_pro);
    //retorno é int, ele vai receber o que pra comparar com o tipo enum
    if((RETORNO == SEM_PROMOCAO) || (RETORNO == ERRO)){
        return RETORNO;
    }else{
        if(pag->num_chaves < ORDEM-1){
           insere_na_pagina(*chv_pro, *off_pro, *rrn_pro, pag->chaves, pag->offset, pag->filhos, &pag->num_chaves);
           escreve_pagina(rrn_atual, pag);
           return SEM_PROMOCAO;
        }else{
            divide(*chv_pro, *off_pro, *rrn_pro, pag, chave_pro, filho_d_pro, novapag);
            escreve_pagina(rrn_atual, pag);
            escreve_pagina(*filho_d_pro, novapag);
            return PROMOCAO;
        }
    }
}

int busca_na_pagina(int chave, PAGINA pag, int *pos){
    int i = 0;

    while((i < pag.num_chaves) && chave > pag.chaves[i]){
        i++;
        *pos = i;
        if((*pos < pag.num_chaves) && (chave = pag.chaves[*pos])){
            return ENCONTRADO;
        }else{
            return NAO_ENCONTRADO;
        }
    }
}

int busca(int rrn, int chave, int *rrn_encontrado, int *pos_encontrada){
    int POS;
    PAGINA *pag;

    if(rrn == NULO){
        return NAO_ENCONTRADO; /* condição de parada */
    }else{
        le_pagina(rrn, pag);
        int ACHOU = busca_na_pagina(chave, *pag, &POS); //achou é int ou char?

        if(ACHOU == 1){
            *rrn_encontrado = rrn; /* RRN da página que contém a chave */
            *pos_encontrada = POS; /* posição da chave na página*/
            return ENCONTRADO;
        }else{ /* siga o ponteiro para a próxima página da busca */
            return (busca(pag->filhos[POS], chave, rrn_encontrado, pos_encontrada));
        }
    }
}

int imprime_pagina(int rrn){
    int i;
    int retorno;
    PAGINA *pag;
    retorno = le_pagina(rrn, pag);

    if(retorno == 1){
        printf("Chaves: ");
        for(i = 0; i < pag->num_chaves; i++){
            if(i == pag->num_chaves){
                printf(" %i \n", pag->chaves[i]);
            }else{
                printf(" %i|", pag->chaves[i]);
            }
    
        }
        printf("Offsets: ");
        for(i = 0; i < pag->num_chaves; i++){
            if(i == pag->num_chaves){
                printf(" %i \n", pag->offset[i]);
            }else{
                printf(" %i|", pag->offset[i]);
            }
    
        }
        printf("Filhos: ");
        for(i = 0; i < ORDEM; i++){
            if(i == ORDEM){
                printf(" %i \n\n", pag->filhos[i]);
            }else{
                printf(" %i|", pag->filhos[i]);
            }
    
        }
        return 1;
    }else{
        return 0;
    }    
}

int imprime_arvore(){
    int rrn_da_pag = 0;
    CABECALHO raiz;

    fseek(arvb, 0, SEEK_SET);
    fread(&raiz, sizeof(CABECALHO), 1, arvb); 

    printf("Pagina %i \n", rrn_da_pag);
    
    while ((imprime_pagina(rrn_da_pag)) == 1){

       if(rrn_da_pag == raiz.rrn_raiz){    

            printf("- - - - - - - - - - - - - - - - - - - - - - -");
            rrn_da_pag++;
            printf("Pagina %i \n", rrn_da_pag);
       }else{   

            if(rrn_da_pag == (raiz.rrn_raiz-1)){
                printf("- - - - - - - - - - Raiz  - - - - - - - - - -");
            }
            rrn_da_pag++;
            printf("Pagina %i \n", rrn_da_pag);
       }
    }

    printf("Impressao realizada com sucesso!");
    return 1;
}

#endif // ARVB_H_INCLUDED