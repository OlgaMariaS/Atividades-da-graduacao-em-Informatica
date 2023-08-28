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
    char nome_arq[TAMANHO];
    char campo[20];
    char cadastro[200];
    int comprimento;

    //avisos
    printf("Programa que cria um arquivo para coletar dados de pessoas \n");
    pulaLinha();


    //Pergunta o nome do arquivo que o usuario quer
    printf("Qual nome do arquivo deseja criar: ");
    input(nome_arq, TAMANHO);

    //Criando arquivo e testando se gerou corretamente
    FILE *arquivo;
    arquivo = fopen(nome_arq, "w");

    if(arquivo == NULL){
        printf("Erro ao gerar arquivo");
        exit(1);
    }

    //Pede sobrenome e calcula o tamanho dele
    printf("Digite o nome ou ENTER para sair: ");
    comprimento = input(campo, TAMANHO);

    while(comprimento > 0){
        //Limpa o cadastro para assim receber um novo
        cadastro[0] = '\0';

        //Pede as informações ao usuario, guarda em campos que são concatenados ao cadastro        
        //Nome
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);
        //Sobrenome
        printf("Sobrenome: ");
        input(campo, TAMANHO);
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);
        //Endereco
        printf("Endereco: ");
        input(campo, TAMANHO);
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);
        //Cidade
        printf("Cidade: ");
        input(campo, TAMANHO);
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);
        //Estado
        printf("Estado: ");
        input(campo, TAMANHO);
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);
        //Cep
        printf("CEP: ");
        input(campo, TAMANHO);
        strcat(cadastro,campo);
        strcat(cadastro,BARRA);

        //Escreve as informacoes no arquivo
        short int tam = strlen(cadastro); //calcula tamanho do cadastro
        fwrite(&tam, sizeof(tam),1, arquivo); //coloca o numero do cadastro antes dos dados
        fwrite(cadastro, sizeof(char),tam,arquivo);

        /*Novo cadastro de pessoa, entao pede novamente sobrenome*/
        pulaLinha();
        printf("Atencao, novo cadastro!");
        printf("\nDigite o nome ou ENTER para sair ");
        comprimento = input(campo, TAMANHO);

    }

    //Fechando arquivo e fim do programa
    fclose(arquivo);
    exit(1);

    return 0;
}

