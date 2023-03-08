#include<stdio.h>
#include<stdlib.h>
/* Autor: Olga   março/2023 
Objetivo: Fazer uma lista duplamente ligada com sentinela*/

//tipo do dado
struct tipo_item{
    int chave;
};
//tipo de cada celula da lista
struct tipo_celula{
    struct tipo_item item;
    struct tipo_celula *prox;
    struct tipo_celula *ant;
};
//criação do tipo da lista sendo o sentinela uma sentinela
struct tipo_lista{
    struct tipo_celula *sentinela;
};
//Inicializa a lista onde o sentinela elemento é criado com o ant e prox apontando pra ele
void inicializa(struct tipo_lista *l){
    l->sentinela=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    l->sentinela->prox=l->sentinela;
    l->sentinela->ant=l->sentinela;
}
//lista vazia é quando o proximo elemento e o sentinela são iguais
int vazia(struct tipo_lista *l){
    return l->sentinela->prox == l->sentinela;
}
/*Criado um auxiliar, que vai percorrer a partir do proximo do sentinela a lista, verificando se encontra a chave e se não encontrar e dar a volta na lista, o codigo para*/
struct tipo_celula* buscar(struct tipo_lista *l, int chave){
    struct tipo_celula *auxiliar;
    auxiliar=l->sentinela->prox;
    while((auxiliar!=l->sentinela) && (chave != auxiliar->item.chave)){
        auxiliar=auxiliar->prox;
    }
    if(auxiliar!=l->sentinela){
        return auxiliar;
    }else{
        return NULL;
    }
}

void insere_sentinela(struct tipo_lista *l, struct tipo_item x){
    struct tipo_celula *novo;
    novo=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->item=x;
    novo->prox = l->sentinela->prox;
    novo->ant = l->sentinela;
    l->sentinela->prox->ant = novo;
    l->sentinela->prox = novo;
}

void insere_ultimo(struct tipo_lista *l, struct tipo_item x){
    struct tipo_celula *novo;
    novo=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->item=x;
    novo->prox=l->sentinela;
    novo->ant=l->sentinela->ant;
    l->sentinela->ant->prox=novo;
    l->sentinela->ant=novo;
}

int insere_auxiliar(struct tipo_lista *l, struct tipo_item x, int pos){
    struct tipo_celula *novo,*auxiliar;
    int i=0;
    auxiliar=l->sentinela;
    while((auxiliar->prox!=l->sentinela) && (i<pos)){
        auxiliar=auxiliar->prox;
        i++;
    }
    if(pos == i){
        novo=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
        novo->item=x;
        novo->ant=auxiliar;
        novo->prox=auxiliar->prox;
        auxiliar->prox->ant=novo;
        auxiliar->prox=novo;
        return 1;
    }
    return 0;
}

int remove_sentinela(struct tipo_lista *l, struct tipo_item *x){
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
int remove_chave(struct tipo_lista *l, int chave, struct tipo_item *x){
    struct tipo_celula *auxiliar;
    auxiliar=buscar(l,chave);
    if(auxiliar==NULL){
        return 0;
    }else{
        *x=auxiliar->item;
        auxiliar->prox->ant = auxiliar->ant;
        auxiliar->ant->prox = auxiliar->prox;
        free(auxiliar);
        return 1;
    }
}

int main(){

}