#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tipo_item{
    int chave;
};
struct tipo_no{
    struct tipo_item dado;
    int altura;
    struct tipo_no *esq;
    struct tipo_no *dir;
};
struct tipo_arvore{
    struct tipo_no *raiz;
};

void inicializa(struct tipo_arvore *a){
    a->raiz = NULL;
}
int vazia(struct tipo_arvore *a){
    return a->raiz == NULL;
}

int altura_no(struct tipo_no *n){
    int altura_sad=0, altura_sae=0;
    if(n!=NULL){
        if(n->esq != NULL){
            altura_sae = n->esq->altura;
        }
        if(n->dir != NULL){
            altura_sad = n->dir->altura;
        }
        if (altura_sad>altura_sae)
            return altura_sad+1;
        else
            return altura_sae+1;
    }else{
        return 0;
    }
}

void rotaciona_esquerda(struct tipo_no **p){
    struct tipo_no *q,*aux;
    q=(*p)->dir;
    (*p)->dir = q->esq;
    q->esq = *p;
    aux=*p;
    *p=q;
    q=aux;
    q->altura = altura_no(q);
    (*p)->altura=altura_no(*p);
}
void rotaciona_direita(struct tipo_no **p){
    struct tipo_no *q,*aux;
    q=(*p)->esq;
    (*p)->esq = q->dir;
    q->dir = *p;
    aux=*p;
    *p=q;
    q=aux;
    q->altura = altura_no(q);
    (*p)->altura=altura_no(*p);
}

void balanceia(struct tipo_no **n){
    int asd,ase;
    asd = altura_no((*n)->dir);
    ase = altura_no((*n)->esq);
    if(asd > ase+1){
        if(altura_no((*n)->dir->esq) > altura_no((*n)->dir->dir)){
        rotaciona_direita(&(*n)->dir);
        }
        rotaciona_esquerda(n);
    }else if(ase > asd+1){
        if(altura_no((*n)->esq->dir) > altura_no((*n)->esq->esq)){
            rotaciona_esquerda(&(*n)->esq);
        }
        rotaciona_direita(n);
    }
}

int insere_no(struct tipo_no **n, struct tipo_item x){
    int ret;
    if(*n==NULL){
        *n=cria_no(x);
        ret=1;
    }else if( (*n)->dado.chave < x.chave ){
        ret=insere_no(&((*n)->dir),x);
    }else if( (*n)->dado.chave > x.chave){
        ret=insere_no(&((*n)->esq),x);
    }else{
        ret=0;
    }
    (*n)->altura = altura_no(*n);
    balanceia(n);
    return ret;
}

int main(){

    int vetor[6] = {3,12,57,14,0,22};

    return 0;
}