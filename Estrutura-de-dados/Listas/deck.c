#include <stdio.h>
#include <stdlib.h>
/*Autor: Olga    
março/2023 
Objetivo: Fazer um deque
-Inicializar;
-verificar se esta vazio;
-inserção pela direita e esquerda
-remoção pela direita e esquerda
-Exibir o deque
    -da esquerda pra direita 
    -da direita pra esquerda */

/*____________________________________CRIAÇÃO DO DEQUE_________________________________*/
struct tipo_item{
    int chave;
};

struct tipo_celula{
    struct tipo_item item;
    struct tipo_celula *prox;
    struct tipo_celula *ant;
};

struct tipo_deque{
    struct tipo_celula *sentinela;
};

void inicializa(struct tipo_deque *deque){
    deque->sentinela=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    deque->sentinela->prox=deque->sentinela;
    deque->sentinela->ant=deque->sentinela;
}
/*_______________________________Verifica se está vazia_________________________________*/

int vazia(struct tipo_deque *deque){
    return deque->sentinela->prox == deque->sentinela;
}
/*______________________________________INSERÇÕES_______________________________________*/

void insere_esquerda(struct tipo_deque *l, struct tipo_item x){
    struct tipo_celula *novo;
    novo=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->item=x;
    novo->prox = l->sentinela->prox;
    novo->ant = l->sentinela;
    l->sentinela->prox->ant = novo;
    l->sentinela->prox = novo;
}

void insere_direita(struct tipo_deque *l, struct tipo_item x){
    struct tipo_celula *novo;
    novo=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->item=x;
    novo->prox=l->sentinela;
    novo->ant=l->sentinela->ant;
    l->sentinela->ant->prox=novo;
    l->sentinela->ant=novo;
}
/*______________________________________REMOÇÃO________________________________________*/
int remove_esquerda(struct tipo_deque *l, struct tipo_item *x){
    struct tipo_celula *auxiliar;
    if(!vazia(l)){
        auxiliar=l->sentinela->prox;
        *x=auxiliar->item;
        auxiliar->prox->ant = auxiliar->ant;
        auxiliar->ant->prox = auxiliar->prox;
        free(auxiliar);
        return 1;
    }else{
        return 0;
    }
}
int remove_direita(struct tipo_deque *l, struct tipo_item *x){
    struct tipo_celula *auxiliar;
    if(!vazia(l)){
        auxiliar=l->sentinela->prox;
        *x=auxiliar->item;
        auxiliar->prox->ant = auxiliar->ant;
        auxiliar->ant->prox = auxiliar->prox;
        free(auxiliar);
        return 1;
    }else{
        return 0;
    }
}
/*______________________________________________________________________________________*/

int main(){

}