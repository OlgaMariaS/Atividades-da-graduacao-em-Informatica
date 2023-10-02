#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 5
#define VAZRIO -1
#define TAMBUFFER 500

typedef struct cabecalho {
    int rrn_raiz; //vai guardar o rrn da pagina raiz, mas o rrn não pode mudar? 
} CABECALHO;

typedef struct pagina {
    int NUM_CHAVES; /* número de chaves na página */
    int CHAVES[ORDEM-1]; /* vetor com as chaves primarias SÃO INTEIRO OU CHARS?*/
    int offset[ORDEM-1];
    int FILHOS[ORDEM]; /* vetor com os RRNs dos filhos */
} PAGINA;

//Primeiro de tudo, fazer a função GERENCIADORA 


