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

//Criação de um nó arbitrário
struct tipo_no *cria_no(int x){
    struct tipo_no *novo;
    novo = (struct tipo_no *)malloc(sizeof(struct tipo_no));
    novo->dado = x;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

/*Para inserir um no na arvore, será verificado se esta vazio, se sim será criado o no com o elemento, se não 
será verificado se o elemento é menor ou maior que o valor atual, e se maior será alocado a direita, se estiver vazia, se menor será alocado a esquerda se vazia, se não será comparado com o valor do novo nó  */
struct tipo_no *inserir_no(struct tipo_no *n, int x){
    if(n==NULL){
        n=cria_no(x);
    }else if(n->dado < x){
        n->dir=inserir_no(n->dir,x);
    }else if(n->dado > x){
        n->esq=inserir_no(n->esq,x);
    }
    
}

//função que insere o primeiro elemento na raiz, enviado pra inserirno, a raiz da arvore passado pelo usuário e o elemento
void insereRaiz(struct tipo_arvore *a, int x){
    inserir_no(a->raiz,x);
}

//função auxiliar pra buscar um no, o usuário passa o elemento e em qual arvore
struct tipo_no *busca(struct tipo_arvore *a, int x){
    return busca_no(&(a->raiz),x);
}

//Recebe o elemento a busca e sempre começa dai raiz, se for igual a raiz vai apresentar se for menor, vai xamar a funcao passando o no a esquerda, se maior, passará o a direita
struct tipo_no *busca_no(struct tipo_no *n, int x){
    if(n==NULL){
        return printf(" No ou arvores vazios !! \n");
    }else if(n->dado == x){
        return n;
    }else if(n->dado > x){
        return busca_no(n->esq,x);
    }else if(n->dado < x){
        return busca_no(n->dir,x);
    }
}

//para ser maior que o valor a remover, estará a direita dele mas se não tiver, retorna ele mesmo 
struct tipo_no *maior(struct tipo_no *n){
    if(n->dir != NULL){
        return maior(n->dir);
    }else{
        return n;
    }
}

/*verifica se o no é valido, se sim, vai comparando os valores, para ir descendo para os lados esquerdos e direitos, se chegar a comparação, que não é nem menor, nem maior é igual, logo ele vai encontrar o maior do lado esquerdo do elemento a remover (esquerdo é menor que os filhos direitos e maior que seus pais), e quando encontrar, este será trocado de lugar com o elemento a ser removido, depois chamará a funcão novamente até que o no seja NULL, e não haja então deslocamentos
*/
struct tipo_no *remove_no(struct tipo_no *n, int x){
    struct tipo_no *aux;
    if(n != NULL){
        if(x < n->dado){
            n->esq = remove_no(n->esq,x);
        }
        else if( x > n->dado){
            n->dir = remove_no(n->dir,x);
        }
        else{ 
            if(n->dir == NULL){
                n = n->esq;
            }else if(n->esq == NULL){
                n = n->dir;
            }else{  
                aux = maior(n->esq);
                n->dado = aux->dado;
                n->esq = remove_no(n->esq,aux->dado);
            }
        }
    }
    return n;
}

int main(){
    int elemento;
    char* resposta;
    struct tipo_arvore *principal;
    inicializa(principal);

    printf("Quer inserir dados (s/n): \n");
    scanf("%c", &resposta);

    while (resposta == 's'){
        if(vazia(principal)){
            printf("Informe o primeiro elemento: \n");
            scanf("%i", &elemento);
            insereRaiz(principal, elemento);
        }else{
            printf("Informe o elemento: \n");
            scanf("%i", &elemento);
            insere_no(principal, elemento);
        }

        printf("que continua (s/n): \n");
        scanf("%c", &resposta);
    }

    
    
}