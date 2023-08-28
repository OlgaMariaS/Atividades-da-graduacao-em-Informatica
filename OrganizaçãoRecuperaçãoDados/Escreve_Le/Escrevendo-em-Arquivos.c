#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementacao da funcao input que le uma string d para str e retorna o comprimento da string lida
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
void pulaLinha(){
    printf("---------------------------\n");
}

int main(){
    #define TAMANHO 20
    #define BARRA "|"
    //Declaracoes de variaveis
    char sobrenome[TAMANHO];
    char nome[TAMANHO];
    char endereco[TAMANHO];
    char cidade[TAMANHO];
    char estado[TAMANHO];
    char cep[TAMANHO];
    char nome_arq[TAMANHO];
    int comprimento;

    //avisos
    pulaLinha();
    printf("Programa que cria um arquivo para coletar dados de pessoas \n");
    pulaLinha();


    //Pergunta o nome do arquivo que o usuario quer
    printf("Qual nome do arquivo deseja criar: ");
    input(nome_arq, TAMANHO);

    //Criando arquivo e testando se gerou corretamente
    FILE *arquivo;
    arquivo = fopen("nome_arq", "w");

    if(arquivo == NULL){
        printf("Erro ao gerar arquivo");
        exit(1);
    }

    //Pede sobrenome e calcula o tamanho dele
    printf("Digite o nome ou ENTER para sair: ");
    comprimento = input(nome, TAMANHO);

    while(comprimento > 0){
        //Pede que o usu�rio preencha as informa��es da pessoa
        printf("Sobrenome: ");
        input(sobrenome,TAMANHO);
        printf("Endereco: ");
        input(endereco,TAMANHO);
        printf("Cidade: ");
        input(cidade,TAMANHO);
        printf("Estado: ");
        input(estado,TAMANHO);
        printf("CEP: ");
        input(cep,TAMANHO);

        //Escreve as informacoes no arquivo
        //Nome
        fputs (nome, arquivo);
        fputs (BARRA, arquivo);
        //sobrenome
        fputs (sobrenome, arquivo);
        fputs (BARRA, arquivo);
        //endere�o
        fputs (endereco, arquivo);
        fputs (BARRA, arquivo);
        //cidade
        fputs (cidade, arquivo);
        fputs (BARRA, arquivo);
        //Estado
        fputs (estado, arquivo);
        fputs (BARRA, arquivo);
        //CEP
        fputs (cep, arquivo);
        fputs (BARRA, arquivo);

        /*Novo cadastro de pessoa, ent�o pede novamente sobrenome*/
        printf("\nAtencao, novo cadastro!");
        printf("\nDigite o sobrenome ou ENTER para sair ");
        comprimento = input(sobrenome, TAMANHO);

    }

    //Fechando arquivo e fim do programa
    fclose(arquivo);
    exit(1);

    return 0;
}

