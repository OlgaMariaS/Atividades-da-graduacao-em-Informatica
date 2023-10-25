#include <stdio.h>

int leia_operacao(char *campo, FILE *arquivo_de_operacoes){
    int i = 0;
    // leia a 1a letra
    char caracter = fgetc(arquivo_de_operacoes);
    if (caracter != EOF) {
        campo[i] = caracter;
        // finalize a string
        campo[++i] = '\0';
        // leia o espaco em branco após a letra da operacao e descarte
        fgetc(arquivo_de_operacoes);
    }
    return i;
}

void leia_chave(char *campo, int tam, FILE *arquivo_de_operacoes){
    int i = 0;
    char caracter = fgetc(arquivo_de_operacoes);
    while (caracter != EOF && caracter != '\n')
    {
        if (i < tam-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(arquivo_de_operacoes);
    }
    campo[i] = '\0';
}


void executa_operacoes(char *nome_arquivo_operacoes){ //executa_operacoes
    char chave[250];
    char *campo;
    int chave_primaria;
    char operacao[2];
    FILE *arquivo_de_operacoes, *dados, *arvb;

    arquivo_de_operacoes = fopen(nome_arquivo_operacoes, "r");
    dados = fopen("dados.dat", "r+");
    arvb = fopen("btree.dat", "w+");

    int comprimento = leia_operacao(operacao, arquivo_de_operacoes);
    leia_chave(chave, 250, arquivo_de_operacoes);      
    
    while (comprimento > 0){   
        //*chama a função baseado na operação do arquivo, passando qual chave deve manipular
        if(strcmp(operacao,"b") == 0 ){
            printf("buscar: chave:%s \n", chave);
        }else if( strcmp(operacao,"i") == 0 ){
           printf("inserir: chave:%s \n", chave);
           campo = strtok(chave, "|");
           chave_primaria = atoi(campo);
           printf("chave primaria; %i \n", chave_primaria);
        }
        comprimento = leia_operacao(operacao, arquivo_de_operacoes);
        leia_chave(chave, 250, arquivo_de_operacoes);
    }
    
    fclose(dados);
    fclose(arquivo_de_operacoes);
}

int main() {
    char arq[] = "operacoes.txt";
    executa_operacoes(arq);
    //imprime_led();
}