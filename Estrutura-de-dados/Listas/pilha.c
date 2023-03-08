#include<stdio.h>
#include<stdlib.h>
/* Autor: Olga   março/2023 
Objetivo: Fazer uma pilha dinamica*/

struct tipo_item{
    int chave;
};
struct tipo_celula{
    struct tipo_celula *prox;
    struct tipo_item item;
};
struct tipo_pilha{
    struct tipo_celula *topo;
};

void inicializa(struct tipo_pilha *p){
    p->topo=NULL;
}

int vazia(struct tipo_pilha *p){
    return p->topo == NULL;
}

void empilha(struct tipo_pilha *p, struct tipo_item x){
    struct tipo_celula *novo;
    novo=(struct tipo_celula*)malloc(sizeof(struct tipo_celula));
    novo->prox=p->topo;
    novo->item=x;
    p->topo=novo;
}

int desempilha(struct tipo_pilha *p, struct tipo_item *x){
    struct tipo_celula *del;
    if(!vazia(p)){ // se a pilha não for vazia
        del=p->topo;
        *x=del->item;
        p->topo=del->prox;
        free(del);
        return 1;
    }
    return 0;
}

int topo(struct tipo_pilha *p, struct tipo_item *x){
    if(!vazia(p)){
        *x = p->topo->item;
        return 1;
    }
    return 0;
}

main(){
 
}