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
FILE * arvb;

// Funções
int le_pagina(int rrn, PAGINA *pag);

int escreve_pagina(int rrn, PAGINA *pag);

int novo_rrn();

void inicializa_pagina(PAGINA pag);

void insere_na_pagina(int chv_pro, int off_pro, int rrn_pro, int chaves[], int offset[], int filhos[], int *num_chaves);

void divide(int chave_i,int off_i, int rrn_i, PAGINA *pag, int *chave_pro, int *filho_d_pro, PAGINA *novapag);

int insere(int rrn_atual, int chave, int offset, int *filho_d_pro, int *chave_pro, int *offset_pro);

int busca_na_pagina(int chave, PAGINA pag, int *pos);

int busca(int rrn, int chave, int *rrn_encontrado, int *pos_encontrada);

int imprime_pagina(int rrn);

int imprime_arvore();

#endif // ARVB_H_INCLUDED