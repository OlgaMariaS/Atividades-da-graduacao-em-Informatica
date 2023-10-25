/*TRABALHO 02 - ORD
Olga RA: 130002
Emilly RA: 117482*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "libarvb.h"

#define ORDEM 5
#define NULO -1
#define TAMBUFFER 500
#define LIMITADOR "|"
#define TAM_STR 30
#define TAM_MAX_REG 256

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

// Funções da arvore de indices 
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

int inicializa_pagina(PAGINA *pag){ 
    int i;
    pag->num_chaves = 0;
    for(i = 0; i < ORDEM-1; i++){
        pag->chaves[i] = NULO;
        pag->offset[i] = NULO;
        pag->filhos[i] = NULO;
    }
    pag->filhos[i] = NULO;
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
    inicializa_pagina(&pag);

    for(i = 0; i < MEIO; i++){
        pag->chaves[i] = PAGAUX.chaves[i];
        pag->offset[i] = PAGAUX.offset[i];
        pag->filhos[i] = PAGAUX.filhos[i];
        pag->num_chaves++;
    }
    pag->filhos[i] = PAGAUX.filhos[i];

/* Copie as chaves e ponteiros que vêm depois de CHAVE_PRO para NOVAPAG */
    inicializa_pagina(&novapag);

    for(i = 0; i < ORDEM; i++){
        novapag->chaves[novapag->num_chaves] = PAGAUX.chaves[i];
        novapag->offset[novapag->num_chaves] = PAGAUX.offset[i];
        novapag->filhos[novapag->num_chaves] = PAGAUX.filhos[i];
        novapag->num_chaves++;
    }
    novapag->filhos[novapag->num_chaves] = PAGAUX.filhos[i];

}

int insere(int rrn_atual, int chave, int offset, int *filho_d_pro, int *chave_pro, int *offset_pro){
    int *rrn_pro;
    int *chv_pro;
    int *off_pro;
    int *POS;
    int ACHOU;
    int RETORNO;
    PAGINA novapag;
    PAGINA pag;

    if(rrn_atual == NULO){
        *chave_pro = chave;
        *filho_d_pro = NULO;
        return PROMOCAO;
    }else{
        le_pagina(rrn_atual, &pag);
        ACHOU = busca_na_pagina(chave, pag, &POS);
    }
    
    if(ACHOU == 0){
        printf("Erro: chave '%i' ja existente", chave);
        return ERRO;
    }
                                           
    RETORNO = insere(pag.filhos[*POS], chave, offset, rrn_pro, chv_pro, off_pro);
    
    if((RETORNO == SEM_PROMOCAO) || (RETORNO == ERRO)){
        return RETORNO;
    }else{
        if(pag.num_chaves < ORDEM-1){
           insere_na_pagina(*chv_pro, *off_pro, *rrn_pro, pag.chaves, pag.offset, pag.filhos, &pag.num_chaves);
           escreve_pagina(rrn_atual, &pag);
           return SEM_PROMOCAO;
        }else{
            divide(*chv_pro, *off_pro, *rrn_pro, &pag, chave_pro, filho_d_pro, &novapag);
            escreve_pagina(rrn_atual, &pag);
            escreve_pagina(*filho_d_pro, &novapag);
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
    PAGINA pag;

    if(rrn == NULO){
        return NAO_ENCONTRADO; /* condição de parada */
    }else{
        le_pagina(rrn, &pag);
        int ACHOU = busca_na_pagina(chave, pag, &POS); //achou é int ou char?

        if(ACHOU == 1){
            *rrn_encontrado = rrn; /* RRN da página que contém a chave */
            *pos_encontrada = POS; /* posição da chave na página*/
            return ENCONTRADO;
        }else{ /* siga o ponteiro para a próxima página da busca */
            return (busca(pag.filhos[POS], chave, rrn_encontrado, pos_encontrada));
        }
    }
}
/*----------------------------------------------------------------------------------------------------------------------------*/
//FUNÇÕES AUXILIARES para a executa_operacao e gerenciadora
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
//Função que le o caracter que representa a operação a ser realizada
int leia_operacao(char *campo, FILE *arquivo_de_operacoes){
    int i = 0;
    // leia a 1a letra
    char caracter = fgetc(arquivo_de_operacoes);
    if (caracter != EOF) {
        campo[i] = caracter;
        // finalize a string
        campo[++i] = '\0';
        // leia o espaco em branco após a letra da operacao e descarte
        fgetc(arquivo_de_operacoes);
    }
    return i;
}
//Função que le a chave após a operação, do arquivo de operações
int leia_chave(char *campo, int tam, FILE *arquivo_de_operacoes){
    int i = 0;
    char caracter = fgetc(arquivo_de_operacoes);
    while (caracter != EOF && caracter != '\n')
    {
        if (i < tam-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(arquivo_de_operacoes);
    }
    campo[i] = '\0';
    return i;
}
/*--------------------------------------------------------------------------------------------------*/
//Função imprime uma pagina da arvore
int imprime_pagina(int rrn){
    int i;
    int retorno;
    PAGINA pag;
    retorno = le_pagina(rrn, &pag);

    if(retorno == 1){
        printf("Chaves: ");
        for(i = 0; i < pag.num_chaves; i++){
            if(i == pag.num_chaves){
                printf(" %i \n", pag.chaves[i]);
            }else{
                printf(" %i|", pag.chaves[i]);
            }
        }
        printf("Offsets: "); 
        for(i = 0; i < pag.num_chaves; i++){
            if(i == pag.num_chaves){
                printf(" %i \n", pag.offset[i]);
            }else{
                printf(" %i|", pag.offset[i]);
            }
        }
        printf("Filhos: ");
        for(i = 0; i < ORDEM; i++){
            if(i == ORDEM){
                printf(" %i \n\n", pag.filhos[i]);
            }else{
                printf(" %i|", pag.filhos[i]);
            }
        }
        return 1;
    }else{
        return 0;
    }    
}
//Chama a função imprima_pagina e vai imprimindo a arvore toda, e quando encontra a raiz, será impresso diferente
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

//FUNÇÕES PRINCIPAIS
/*executa_operacoes é responsável por ler as operações e chaves, executar na arvb e com os dados
da arvb é realizada a operação em dados (busca ou inserção)*/
int executa_operacoes(char *nome_arquivo_operacoes, FILE *dados, FILE *arvb){ //executa_operacoes
    char chave[TAM_MAX_REG];
    char *campo;
    char operacao[2];
    int chave_primaria;
    short tam;
    int rrn, rrn_encontrado, pos_encontrado;
    PAGINA pag;
    FILE *arquivo_de_operacoes;

    arquivo_de_operacoes = fopen(nome_arquivo_operacoes, "r");

    rewind(arvb);
    fread(&rrn, sizeof(rrn), 1, arvb);
    int comprimento = leia_operacao(operacao, arquivo_de_operacoes);
    tam = leia_chave(chave, TAM_MAX_REG, arquivo_de_operacoes);      
    
    while (comprimento > 0){   
        //*chama a função baseado na operação do arquivo, passando qual chave deve manipular
        if(strcmp(operacao,"b") == 0 ){
            int RETORNO;
            RETORNO = busca(rrn, chave, &rrn_encontrado, &pos_encontrado);

            if(RETORNO = ENCONTRADO){
                short tamanho;
                char chave_encontrada[TAM_MAX_REG];

                fseek(arvb, rrn_encontrado,SEEK_SET);
                fread(&pag, sizeof(pag), 1, arvb); 

                fseek(dados, (pag.offset[pos_encontrado]-2),SEEK_SET);
                fread(&tamanho, sizeof(tamanho), 1, arvb); 
                fseek(dados, pag.offset[pos_encontrado],SEEK_SET);
                fread(&chave_encontrada, tamanho, 1, arvb); 

                printf("Busca pelo registro de chave %i",  pag.chaves[pos_encontrado]);
                printf("%s (%i bytes - offset %i)",  chave_encontrada, tamanho, pag.offset[pos_encontrado]);
            }else{
                printf("Erro: registro nao encontrado!");
            }
            
        }else if( strcmp(operacao,"i") == 0 ){
            int filho_d_pro;
            int chave_pro;
            int offset_pro;
            int offset;
            
            campo = strtok(chave, "|");
            chave_primaria = atoi(campo);
            fseek(dados,0,SEEK_END);
            offset = ftell(dados);
            int RETORNO = insere(rrn, chave_primaria, offset, &filho_d_pro, &chave_pro, &offset_pro);
            
            if(RETORNO == ERRO){
                    return 0;
            }else {
                    fseek(dados,0,SEEK_END);
                    fwrite(&tam, sizeof(short), 1, dados); 
                    fwrite(&chave, tam, 1, dados); 
                }
            }
            comprimento = leia_operacao(operacao, arquivo_de_operacoes);
            tam = leia_chave(chave, 250, arquivo_de_operacoes);
    }
}

/*  Lê as chaves de dados.dat a serem armazenadas na árvore-B e chama a função
    insere()
    – Cria uma nova raiz quando houver divisão da raiz atual
    • Quando a função insere() retornar PROMOÇÃO
    • Cria a página que será a nova raiz
    • Atualiza o RRN da raiz*/
int gerenciadora(int RAIZ, FILE *dados){
    int i = 0;
    int chave;
    int offset = 4;
    int filho_d_pro;
    int chave_pro;
    int offset_pro;
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
        
        if(insere(RAIZ, chave, offset, &filho_d_pro, &chave_pro, &offset_pro) == PROMOCAO){

            inicializa_pagina(&novapag);
            novapag.chaves[i] = chave_pro;
            novapag.offset[i] = offset_pro;
            novapag.filhos[i] = RAIZ;
            novapag.filhos[i+1] = filho_d_pro;
            novapag.num_chaves++;
            RAIZ = novo_rrn();
            escreve_pagina(RAIZ, &novapag);
        }   
        offset = offset + tamanho + sizeof(tamanho);
        i++;
    }
    rewind(dados);
    fwrite(&RAIZ, sizeof(RAIZ), 1, arvb); 
    return 1;
}

//Principal 
int main(int argc, char *argv[]) {
    CABECALHO raiz;
    PAGINA pag;
    FILE *arvb;
    FILE *dados;

    dados = fopen("dados.dat", "r+");
    arvb = fopen("btree.dat", "w+");

    if (argc == 3 && strcmp(argv[1], "-c") == 0) {

        //Criação de uma pagina em branco
        raiz.rrn_raiz = 0;
        rewind(arvb);
        fwrite(&raiz.rrn_raiz, sizeof(raiz.rrn_raiz), 1, arvb); 
        inicializa_pagina(&pag);
        escreve_pagina(raiz.rrn_raiz, &pag);
    
        if(gerenciadora(raiz.rrn_raiz, dados) == 1){
                printf("Criacao do arquivo de índices 'btree.dat' criada com sucesso!");
        }else{
                printf("Falha na criacao do arquivo de indices");
        }

    } else if (argc == 2 && strcmp(argv[1], "-e") == 0) {
        
        //Chama a função que executa o arquivo de operações, e insere ou busca em btree.dat
        executa_operacoes(argv[2], dados, arvb);

    } else if (argc == 1 && strcmp(argv[1], "-p") == 0) {
        //chama a função que imprime a arvore
        imprime_arvore();
        
    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s -e nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fclose(dados);
    fclose(arvb);
    return 0;
}

