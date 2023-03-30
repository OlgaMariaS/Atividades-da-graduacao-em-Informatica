#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tipo_no{
    int dado;
    struct tipo_no *esq, *dir;
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

struct tipo_no *cria_no(int x){
    struct tipo_no *novo;
    novo = (struct tipo_no *)malloc(sizeof(struct tipo_no));
    novo->dado=x;
    novo->dir=NULL;
    novo->esq=NULL;
    return novo;
}

int insereRaiz(struct tipo_arvore *a, int x){
    return insere_no(&(a->raiz),x);
}
struct tipo_no *inserir_no(struct tipo_no *n, int x){
    if(n==NULL){
        n=cria_no(x);
    }else if(n->dado < x){
        n->dir=inserir_no(n->dir,x);
    }else if(n->dado > x){
        n->esq=inserir_no(n->esq,x);
    }
    return n;
}

struct tipo_no *busca(struct tipo_arvore *a, int x){
    return busca_no(a->raiz,x);
}

struct tipo_no *busca_no(struct tipo_no *n, int x){
    if(n==NULL){
        return NULL;
    }else if(n->dado == x){
        return n;
    }else if(n->dado > x){
        return busca_no(n->esq,x);
    }else if(n->dado < x){
        return busca_no(n->dir,x);
    }
}

struct tipo_no *maior(struct tipo_no *n){
    if(n->dir != NULL){
        return maior(n->dir);
    }else{
        return n;
    }
}

struct tipo_no *remove_no(struct tipo_no *n, int ch){
    struct tipo_no *aux;
    if(n!=NULL){
        if(ch < n->dado){
        n->esq = remove_no(n->esq,ch);
    }else if( ch > n->dado){
        n->dir = remove_no(n->dir,ch);
    }else{
        if(n->dir == NULL){
            n=n->esq;
        }else if(n->esq == NULL){
            n=n->dir;
        }else{
            aux=maior(n->esq);
            n->dado = aux->dado;
            n->esq=remove_no(n->esq,aux->dado);
        }
    }
    }
    return n;
}

int main(){
    int elemento;
    char resposta[1];
    struct tipo_arvore *principal;
    inicializa(principal);

    printf("Quer inserir dados (s/n): \n");
    scanf("%s", &resposta);

    while (resposta == 's'){
        if(!(vazia(principal))){
            printf("Informe o primeiro elemento: \n");
            scanf("%i", &elemento);
            insereRaiz(principal, &elemento);
        }else{
            printf("Informe o elemento: \n");
            scanf("%i", elemento);
            insere_no(principal,elemento);
        }

        printf("Continua (s/n): \n");
        scanf("%s", &resposta);
    }

    
    
}