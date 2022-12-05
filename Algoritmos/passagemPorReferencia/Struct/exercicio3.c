#include<stdio.h>
#include<string.h>
/*
Faca um programa que defina um vetor de struct e cadastre 10 produtos com codigo, nome e preço. Faça uma função o que receba estes registros e retorne a media de preço dos produtos cadastrados.
PLANEJAMENTO:
-Criar um struct de cadastro de produtos;
-pedir ao usuário os dados dos produtos dentro da main;
-chamar a função media, passar a struct[] como parametro;
-dentro da função vai somar todos os preços do produtos e fazer media e retorna-lá;
-será exibido a media dentro da main;
TESTE:
-Preços: 
10; 20; 3; 40; 55; 65; 5; 18; 9.8; 12.3 ---> 238.1 / 10 = 23,81
*/

void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void pulaLinha(){
    printf("\n---------------------\n");
}

typedef struct cadastro{
    int codigo;
    char nome[20];
    float preco;
};

float media(struct cadastro mediaPreco[], int tamanho){

    float media = 0;

    for (int i = 0; i < tamanho; i++){
        media += mediaPreco[i].preco;
        
    }

    return media / tamanho;
    
}

main(){
    struct cadastro produto[10];
    float mediaPrecos;
    int tamanho = 10;

    for (int i = 0; i < tamanho; i++){
        printf("Codigo do produto: ");
        scanf("%i", &produto[i].codigo);

        flush_in();
        printf("Nome do produto: ");
        fgets(produto[i].nome, 20, stdin);

        printf("Preco do produto: ");
        scanf("%f", &produto[i].preco);

        pulaLinha();
    }

    mediaPrecos = media(produto, tamanho);
    
    printf("A media dos precos dos produtos e: %.2f", mediaPrecos);
    
}