#include <stdio.h>
#include <stdlib.h>
/* Autor: Olga    
março/2023 
Objetivo: Fazer um deque
-Inicializar;
-verificar se esta vazio;
-inserção pela direita e esquerda
-remoção pela direita e esquerda
-Exibir o deque
    -da esquerda pra direita 
    -da direita pra esquerda 
-Encerrar */

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
    struct tipo_celula *del;
    if(!vazia(l)){
        del=l->sentinela->prox;
        *x=del->item;
        l->sentinela->prox = del->prox;
        del->prox->ant = l->sentinela;
        free(del);
    }else{
        printf("Deque vazio");
    }
}
int remove_direita(struct tipo_deque *l, struct tipo_item *x){
    struct tipo_celula *del;
    if(!vazia(l)){
        del=l->sentinela->ant;
        *x=del->item;
        l->sentinela->ant = del->ant;
        l->sentinela->ant->prox = l->sentinela;
        free(del);
    }else{
        printf("Deque vazio");
    }
}
/*___________________________________Impressão ___________________________________________*/
void impressaoEsqDir(struct tipo_deque *d){
    struct tipo_celula *aux;
    if(!vazia(d)){
        aux = d->sentinela->prox;
        while (aux != d->sentinela->ant->prox) {
            printf(" %i ", d->sentinela->item.chave );
            aux = aux->prox;
        }
    }else{
        printf("Deque vazio");
    } 
}
void impressaoDirEsq(struct tipo_deque *d){
    struct tipo_celula *aux;
    if(!vazia(d)){
        aux = d->sentinela->ant;
        while (aux != d->sentinela->prox->ant) {
            printf(" %i ", d->sentinela->item.chave );
            aux = aux->ant;
        }
    }else{
        printf("Deque vazio");
    } 
}
/*_________________________________________________________________________________________*/
int main(){
    /*Criação do deque */
    struct tipo_deque *dequePrincipal;
    inicializa(dequePrincipal); 

    struct tipo_item elemento;

    int menu;

    printf("Algoritmo de Deque \n Escolha uma opcao \n  1 - Inserir a esquerda \n  2 - Inserir a direita \n  3 - Remover a esquerda \n  4 - Remover a direita \n  5 - Imprimir esq->dir \n  6 - Imprimir da dir->esq \n  7 - Encerrar \n");
    scanf("%i", &menu);

    if (menu == 1){
        printf("Informe o elemento para inserir: ");
        scanf("%i", &elemento.chave);

        insere_direita(dequePrincipal, elemento);
    }
    if (menu == 2){
        printf("Informe o elemento para inserir: ");
        scanf("%i", &elemento.chave);

        insere_esquerda(dequePrincipal, elemento);
    }
    if (menu == 3){
        remove_esquerda(dequePrincipal, &elemento);
    }
    if (menu == 4){
        remove_direita(dequePrincipal, &elemento);
    }
    if (menu == 5){
        impressaoEsqDir(dequePrincipal);
    }
    if (menu == 6){
        impressaoDirEsq(dequePrincipal);
    }
    if (menu == 7){
        exit;
    }
    
    return 1;

}