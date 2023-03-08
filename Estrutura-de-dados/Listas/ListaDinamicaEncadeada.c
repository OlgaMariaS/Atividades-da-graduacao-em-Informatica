#include<stdio.h>
#include<stdlib.h>
/* Autor: Olga   março/2023 
Objetivo: Fazer uma lista dinamica com as opções de:
○ Inicializar lista;
○ Inserir um elemento;
○ Remover um elemento;
○ Localizar um elemento;
○ Imprimir a lista;
-----------------------------------------------------------------------*/
//Tipo dos dados dos elementos de dentro da lista
struct cadastro{
    int codigo;
    char nome[20];
    int idade;
};
//Estrutura de como vai ser os elementos da lista
struct elemento{
    //variável que se chama DADOS, o tipo dela é struct cadastro 
    struct cadastro dados;
    //ponteiro que aponta pro proximo elemento da lista;
    struct elemento *proximo;        
};

//Listas, como tipo sendo struct elemento
typedef struct elemento* lista;
typedef struct elemento auxiliar;
/*------------------------------------------------------------------------------*/
/*Verificando se a lista esta nula e atribuindo o vazio ao elemento principal (aterra), este elemento que vai apontar pros demais elementos */
lista* criaLista(){
    lista* principal = (lista*) malloc(sizeof(lista));
    if(principal != NULL)
        *principal = NULL;
    return principal;
}
/*----------------------------------------------------------------------------*/
/*Se principal não estiver vazio, o componente vai apontar pro principal da lista, e o principal vai apontar pro proxima elemento, e o componente vai ser "liberado", sendo assim será liberado todos os elementos da lista, um por vez até que a lista aponte pra NULL*/
void libera_lista (lista* principal){
    if (principal != NULL){
        auxiliar* componente;
        while((*principal) != NULL){ 
            componente = *principal; 
            *principal = (*principal)->proximo;
            free(componente);
        }
    }
}
/*-------------------------------INSERÇÃO--------------------------------------*/
/*Para todos os tipos de inserções, a função recebe uma lista para ser inserido um elemento e qual elemento a inserir, se a lista exister null, retorna 0, se não, um novo componente será criado, se tiver memória pro novo componente, contiuamos, dentro do novo componente colocamos os dados de elemento a ser inserido a lista*/

/*na inserção no inicio,o proximo elemento no novo componente é o proximo que o principal da lista estava apontando, e o principal da lista aponta pro novo elemento*/
int insere_inicio_lista(lista* principal, struct cadastro cad){
    if(principal == NULL)
        return 0;
    auxiliar* novo = (auxiliar*) malloc(sizeof(auxiliar));
    if (novo == NULL)
        return 0;
    novo->dados = cad;
    novo->proximo = (*principal); 
    *principal = novo;
    return 1;
}
/*o proximo do novo elemento aponta pra NULL, e se a lista for vazia, vai inseriri no inicio, se não, vai criar um auxiliar que vai verificar os proximos dos elementos, até achar o elemento que o proximo seja NULL, ou seja é o ultimo elemento, sendo assim o proximo deste elemento vai apontar pro novo elemento.*/
int insere_final_lista(lista* principal, struct cadastro cad){
    if(principal == NULL)
        return 0;
    auxiliar* novo = (auxiliar*) malloc(sizeof(auxiliar));
    if (novo == NULL)
        return 0;
    novo->dados = cad;
    novo->proximo = NULL; 
    if( (*principal) == NULL)
        *principal = novo;
    else{
        auxiliar* aux = *principal;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    return 1;
}
/*------------------------------REMOÇÃO----------------------------------------*/
/*Todas as funções verificam se a lista é valida e se é vazia*/

/*Criado um elemento a remover, que recebe quem está sendo apontando por principal (primeiro elemento da lista), depois principal aponto pro proximo do seu primeiro elemento, ou seja aponta pro segundo elemento (pode ser até NULL), e liberamos o elemento apontado por elemento a remover*/
int remove_inicio_lista(lista* principal, struct cadastro cad){
    //Se a lista existe
    if(principal == NULL)
        return 0;
    //Se a lista está vazia
    if (*principal == NULL)
        return 0;

    auxiliar *elementoAremover = *principal;
    *principal = elementoAremover->proximo;
    free(elementoAremover);
    return 1;
}
/*criado o ponteiro anterior, e o elemento a remover que recebe quem está sendo apontado por principal(primeiro elemento da lista), se o proximo deste primeiro elemento NÃO for NULL, ou seja é não é o ultimo, o elemento a remover passa a apontar pra este proximo, e anterior passa a apontar pro antigo elemento a remover, até que encontremos o NULL, este acaba sendo o ultimo elemento, e o anterior aponta pro proximo do elemento a ser removido, que no caso é NULL, e o elemento é removido */
int remove_fim_lista(lista* principal){
    //Se a lista existe
    if(principal == NULL)
        return 0;
    //Se a lista está vazia
    if (*principal == NULL)
        return 0;

    auxiliar *anterior, *elementoAremover = *principal;
    while(elementoAremover->proximo != NULL){
        anterior = elementoAremover;
        elementoAremover = elementoAremover->proximo;
    }
    if(elementoAremover == (*principal))
        *principal = elementoAremover->proximo;
    else 
        anterior->proximo = elementoAremover->proximo;
    free(elementoAremover);
    return 1;
}
/*--------------------------------------CONSULTA-------------------------------*/
/*Verificamos se a lista é válida e se a posição também, Uma struct buscador vai apontar pro primeiro da lista, e enquanto este não chagarmos na posição/conteudo e o buscador não é null, vai continuar a percorrer a lista, se encontrar a posição/conteudo e o buscador não for null, vai copiar os dados pra dentro da estrutura fornecida pelo usuário*/
int consulta_por_posicao(lista* principal, int posicao, struct cadastro *cad){
    if(principal == NULL || posicao <= 0) 
        return 0;
    auxiliar *buscador = *principal;
    int i = 1;
    while(buscador != NULL && i<posicao){
        buscador = buscador->proximo;
        i++;
    }   
    if(buscador == NULL)
        return 0;
    else{
        *cad = buscador->dados;
        return 1;
    }
}

int consulta_por_conteudo(lista* principal, int conteudo, struct cadastro *cad){
    if(principal == NULL) 
        return 0;
    auxiliar *buscador = *principal;
    
    while(buscador != NULL && buscador->dados.codigo != conteudo){
        buscador = buscador->proximo;
    }   
    if(buscador == NULL)
        return 0;
    else{
        *cad = buscador->dados;
        return 1;
    }
}
/*-------------------------Impressão na tela-----------------------------------*/
void imprime_lista(lista* principal){
    if (principal == NULL)
        return printf("Lista inválida");
    if(*principal == NULL)
        return printf("Lista sem elementos");
    
    auxiliar *imprimeElemento = *principal;
    while(imprimeElemento != NULL){
        printf(" %i %s %i ", imprimeElemento->dados);
    }
    
}
/*-----------------------------------------------------------------------------*/
main(){
    /*principal aponta pra lista que é uma struct elemento, que já é ponteiro, ou seja principal é um ponteiro que aponta pra ponteiro (precisa ser assim para poder armazenar o endereço de outro ponteiro).*/
    lista *principal;

    principal = criaLista();
    libera_lista(principal);

    //struct do tipo cadastro, com os dados do X cadastro a ser inserido, removido, buscado... dentro da lista
    struct cadastro x_cadastro;

    //INSERÇÕES; recebem 0 ou 1 como retorno das funções;
    int insercaoInicio = insere_inicio_lista(principal, x_cadastro);
    int insercaoFim = insere_Final_lista(principal, x_cadastro);

    //Remoções
    int removeInicio = remove_inicio_lista(principal, x_cadastro);
    int removeFim = remove_Fim_lista(principal);

    //Consultas
    int posicao;
    int conteudo;

    int consultaPosicao = consulta_por_posicao(principal, posicao, &x_cadastro);
    int consultaConteudo = consulta_por_conteudo(principal, conteudo, &x_cadastro);
    
}