#include<stdio.h>
/*
Considere o exercicio anterior, mas depois de exibir a media dos preços, chame uma função que vai mostrar todos os produtos que custem menos de 10 reais.
PLANEJAMENTO:
-programa vai seguir contudo que o exercicio 3 fazia;
- terá uma segunda função que verifica os precos < 10;
- se é menor mostrar na tela;
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
void menor10(struct cadastro menor[], int tamanho){

    pulaLinha();
    printf("Produtos com preco menor que R$ 10: ");

    for (int i = 0; i < tamanho; i++){
        if (menor[i].preco <= 10.00){

            printf("\n%sR$ %.2f", menor[i].nome, menor[i].preco);
            pulaLinha();
        } 
    }

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
    
    menor10(produto, tamanho);
}