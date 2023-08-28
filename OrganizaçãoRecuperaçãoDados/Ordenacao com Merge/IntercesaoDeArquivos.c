#include<stdio.h>
#include<string.h>

#define TAM_MAX 50
#define VALOR_BAIXO ""
#define VALOR_ALTO "~"
#define TRUE 1
#define FALSE 0

int input(char * str, int size) {
    int i = 0;    
    char c = getchar();    
    while (c != '\n') {        
        if (i < size - 1) {            
            str[i] = c;            
            i++;                 
        }        
        c = getchar();   
    }    
    str[i] = '\0';    
    return i;
}

void inicialize( FILE **lista1, FILE **lista2, FILE **saida, char *ant1, char *ant2, int *existem_mais_nomes ){
    char nomelista1[10];
    char nomelista2[10];
    char nomelista3[10];

    strcpy(ant1, VALOR_BAIXO);
    strcpy(ant2, VALOR_BAIXO);

    printf("Digite o nome do primeiro arquivo: ");
    input(nomelista1, TAM_MAX);
    FILE *lista1;

    printf("Digite o nome do segundo arquivo: ");
    input(nomelista2, TAM_MAX);
    FILE *lista2;

    if (((lista1 = fopen(nomelista1, "r")) != NULL) && ((lista2 = fopen(nomelista2, "r")) != NULL)) {
        *existem_mais_nomes = 1; // recebe verdadeiro
    }else{
        printf("Erro na abertura das listas\n");
        exit(1);
    }

    printf("Digite o nome do arquivo de saida: ");
    input(nomelista3, TAM_MAX);
    FILE *lista3;
    lista3 = fopen(nomelista3, "w");

    if(lista3 == NULL){
        printf("Erro na criacao das lista de saida\n");
        exit(1);
    }
}

void leia_nome( FILE *lista, char *nome, char *nome_ant, char *nome_ant_outra_lista, int *existem_mais_nomes ){

    nome = fgets(nome, TAM_MAX, lista);

    if(nome == NULL){
       if(strcmp(nome_ant_outra_lista, VALOR_ALTO) == 0){
            *existem_mais_nomes = 0;
       }else{
            *existem_mais_nomes = 1;
       }
    }else{
        if( strcmp(nome_ant, nome) == 0 || strcmp(nome_ant, nome) > 0 ){
            printf("Erro de sequencia");
            exit(1);
        }
    }

    strcmp(nome_ant, nome);

}

void merge(){

}

int main(){
    merge();
    return 0;
}