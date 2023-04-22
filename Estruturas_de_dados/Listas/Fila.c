#include<stdio.h>
#include<stdlib.h>
/* Autor: Olga   março/2023 
Objetivo: Fazer uma fila dinamica*/

/*Criação da fila dinamica*/
struct tipo_item{
    int valor;
};
struct tipo_dos_dados{
    struct tipo_item elemento;
    struct tipo_dos_dados *prox;
};
struct tipo_da_fila{
    struct tipo_dos_dados *primeiro;
    struct tipo_dos_dados *ultimo;
};
struct tipo_dos_dados auxiliar;

void inicializa_fila(struct tipo_da_fila *fila){
    fila->primeiro = (struct tipo_dos_dados *) malloc(sizeof(struct tipo_dos_dados));
    fila->ultimo = fila->primeiro;
    fila->ultimo->prox = NULL;
}

int verificaSeFilaVazia(struct tipo_da_fila *fila){
    return fila->primeiro->prox == NULL;
}

void inserir_fila(struct tipo_da_fila *fila, struct tipo_item x){
    struct tipo_dos_dados *novo;
    novo = (struct tipo_dos_dados *)malloc(sizeof(struct tipo_dos_dados));
    novo->prox = NULL; //o proximo do novo recebe null, pois a inserção sempre é no fim
    novo->elemento = x;
    fila->ultimo->prox = novo;
    fila->ultimo =novo;
}

int remove_fila(struct tipo_da_fila *fila, struct tipo_item *x){
    struct tipo_dos_dados *elementoAremover;
    if(!verificaSeFilaVazia(fila)){
        elementoAremover = fila->primeiro->prox;
        fila->primeiro->prox = elementoAremover->prox;
        *x = elementoAremover->elemento;
        free(elementoAremover);
    if(verificaSeFilaVazia(fila)){
        fila->ultimo = fila->primeiro;
    }
        return 1;
    }else{
        return 0;
    }
}

int main(){
    struct tipo_item teste;

    struct tipo_da_fila *filaPrincipal;

    inicializa_fila(filaPrincipal);

    inserir_fila(filaPrincipal, teste);

    remove_fila(filaPrincipal, &teste);

    return 1;
}
