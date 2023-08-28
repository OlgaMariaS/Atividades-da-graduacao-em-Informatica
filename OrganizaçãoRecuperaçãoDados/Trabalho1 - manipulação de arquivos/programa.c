#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Constantes
#define TAM_CAMPOS 250
#define TAM_OPERACAO 2
#define QUEBRA_DE_LINHA '\n'
#define TAM_ID 5
#define LIMITADOR '|'
#define bytes_do_tamanho 2

// FUNÇÕES AUXILIARES
// Funcao que le somente o primeiro caracter de cada linha do arquivo_de_operacões, que representa a operação a ser realizada
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

// Funcao que le as chaves do arquivo_de_operacões (armazena somente após o digito de operação e espaço até o \n)
void leia_chave(char *campo, int tam, FILE *arquivo_de_operacoes){

    int i = 0;
    char caracter = fgetc(arquivo_de_operacoes);
    while (caracter != EOF && caracter != QUEBRA_DE_LINHA)
    {
        if (i < tam-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(arquivo_de_operacoes);
    }
    campo[i] = '\0';
}
/*Função que le para onde o byteOffset está apontando, neste caso vai ser chamada para ler somente os identificadores dos registros*/
void le_identificador(char *campo, FILE *dados, int byteOffset){
    fseek(dados,byteOffset, SEEK_SET);
    int i = 0;
    char caracter = fgetc(dados);
    while (caracter != LIMITADOR)
    {
        if (i < TAM_ID-1) {
            campo[i] = caracter;
            i++;
        }
        caracter = fgetc(dados);
    }
    campo[i] = '\0';
}
/*--------------------------------------------------------------------------------------------------------------------------------*/

/*Função de Led (Lista de Espaços Disponiveis), responsável por armazenar e ordenar os espaços marcados como removidos*/
void led(FILE *dados, int byteOffset_do_registro_removido, short tamanho_registro_removido){
    int byteOffsett_topo_da_led;
    short tamanho_topo_led;
    short led_vazia = -1;    
    
    //Aponta pro inicio do arquivo,se o inicio do arquivo estiver vazio, ou seja em binario (-1), então a led está vazia
    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1, dados); 
    
    if(byteOffsett_topo_da_led == led_vazia){
        /* Caso o topo da led seja -1, ela está vazia, sendo assim, nosso registro recebe o que esta no topo da led (-1), e a led
        recebe o byte offsett do registro que foi removido */
        fseek(dados, (byteOffset_do_registro_removido+2), SEEK_SET);
        fwrite(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1,dados);
        rewind(dados); 
        fwrite(&byteOffset_do_registro_removido, sizeof(byteOffset_do_registro_removido), 1,dados);
     
    }else{
        //Verifica qual tamanho do elemento que ocupa o topo da led
        fseek(dados, byteOffsett_topo_da_led, SEEK_SET);
        fread(&tamanho_topo_led, sizeof(tamanho_topo_led), 1, dados); 

        if(tamanho_topo_led > tamanho_registro_removido){ //Caso o tamanho da led seja maior que o registro, devemos então percorrer ela
            int byte_offsett_atual; 
            short tamanho_atual;
            int byteOffsett_anterior;

            //Apontamos e lemos o byte Offsett do proximo da led e seu tamanho
            byteOffsett_anterior = byteOffsett_topo_da_led;
            fseek(dados,(byteOffsett_topo_da_led+2),SEEK_SET); 
            fread(&byte_offsett_atual, sizeof(byte_offsett_atual), 1, dados); 
            fseek(dados, byte_offsett_atual,SEEK_SET);
            fread(&tamanho_atual, sizeof(tamanho_atual), 1, dados);

            /*Verificamos se o tamanho prox. da led é menor que o registro removido, caso não seja, então iremos pro proximo dele
            para assim percorrer a led e encontrar um tamanho menor ou o fim da led*/ 
            while(tamanho_atual <= tamanho_registro_removido){

                byteOffsett_anterior = byte_offsett_atual;
                fseek(dados,(byte_offsett_atual+2),SEEK_SET); 
                fread(&byte_offsett_atual, sizeof(byte_offsett_atual), 1, dados); 
                fseek(dados, byte_offsett_atual,SEEK_SET); 
                fread(&tamanho_atual, sizeof(tamanho_atual), 1, dados);
            }

            /*Quando encontrar um registro menor, o byte offsett que apontava pro menor, recebe o offsett do registro novo, e
            o offsett do registro removido recebe o offsett do menor*/
            fseek(dados,(byteOffsett_anterior+2),SEEK_SET);
            fwrite(&byteOffset_do_registro_removido, sizeof(byteOffset_do_registro_removido), 1,dados); 
            fseek(dados,(byteOffset_do_registro_removido+2),SEEK_SET);
            fwrite(&byte_offsett_atual, sizeof(byte_offsett_atual), 1,dados); 
                    
        }else{ //Se tamanho do topo da led é MENOR ou IGUAL ao tamanho do registro
        
            //Aponta pra depois do caracter * do registro removido, e adiciona ali o byteOffsett que esta na led
            fseek(dados,(byteOffset_do_registro_removido+2),SEEK_SET);
            fwrite(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led),1,dados); 

            //Aponta pro topo da led e escreve o byteOffset do maior registro removido no top da led
            rewind(dados);
            fwrite(&byteOffset_do_registro_removido, sizeof(byteOffset_do_registro_removido),1,dados);  
        }
    }
}
/*Funcao REMOVER é responsavel por marcar um * no registro é chamada pela função de busca, 
que encontra o local onde está o registro a remover, depois de marcar o registro, chama a função LED que reorganiza os espaços disponiveis */
void remover(FILE *dados, int byteOffsett, short tamanho_registro, char *chave_primaria){
    //Marca a chave como removida e envia o tamanho disponivel a LED
    byteOffsett -= 1;
    fseek(dados,byteOffsett, SEEK_SET);
    fputs("*", dados);
    byteOffsett -= 1;
    led(dados, byteOffsett, tamanho_registro);
    
    printf("Remocao do registro de chave '%s' \nRegistro removido! (%i bytes)\nLocal: offset = %i bytes \n\n", chave_primaria, tamanho_registro, byteOffsett);         
}

/*Função que faz a busca de um registro a partir de uma chave, vai comparando somente os byteOffsetts das chaves primarias, quando encontra
a chave, vai verificar se a operação é de busca, se sim imprime os dados na tela, se não, vai chamar a função de remover o registro*/
void buscar(FILE *dados, char *chave_a_encontrar, char *operacao){
    int byteOffsett = 4; 
    short tamanho_registro;
    short achou = 0; 
    char chave_primaria[TAM_ID];

    while(achou != 1){
        fseek(dados,byteOffsett, SEEK_SET); 
        fread(&tamanho_registro, sizeof(tamanho_registro), 1, dados);

        byteOffsett += bytes_do_tamanho; 
        fseek(dados, byteOffsett, SEEK_SET);
        le_identificador(chave_primaria, dados, byteOffsett); 

        if(strcmp(chave_primaria,chave_a_encontrar) == 0){
            if(strcmp(operacao,"b") == 0){
                char registro[tamanho_registro];

                leia_chave(registro, tamanho_registro, dados);
                printf("Busca pelo registro de chave %s\n", chave_primaria);
                
                //fseek(dados, byteOffsett, SEEK_SET);
                printf("%s|%s", chave_primaria, registro);
                printf(" (%i bytes) \n\n", tamanho_registro);

            }else {//caso a operação não seja de busca ela será de remover, assim deve chamar a função que remove
                remover(dados, byteOffsett, tamanho_registro, chave_primaria);
            }
            achou = 1;
        }else{
            byteOffsett += tamanho_registro;
            achou = 0;
        }
    }
}
int executa_operacoes(char *nome_arquivo_operacoes){ //executa_operacoes
    char chave[TAM_CAMPOS];
    char operacao[TAM_OPERACAO];
    
    FILE *arquivo_de_operacoes;
    arquivo_de_operacoes = fopen(nome_arquivo_operacoes, "r");
    FILE *dados;
    dados = fopen("dados.dat", "r+");

    if (arquivo_de_operacoes == NULL) {
        printf("Erro na abertura do arquivo --- programa abortado\n");
        exit(1);
    }
    
    int comprimento = leia_operacao(operacao, arquivo_de_operacoes);
    leia_chave(chave, TAM_CAMPOS, arquivo_de_operacoes);      
    
    while (comprimento > 0){   
        //*chama a função baseado na operação do arquivo, passando qual chave deve manipular
        if( strcmp(operacao,"b") == 0 ){
            buscar(dados, chave, operacao);
        }else if( strcmp(operacao,"r") == 0 ){
            buscar(dados, chave, operacao);
        }else if( strcmp(operacao,"i") == 0 ){
            //chamar função inserir(dados,chave);
        }
        
        comprimento = leia_operacao(operacao, arquivo_de_operacoes);
        leia_chave(chave, TAM_CAMPOS, arquivo_de_operacoes);
    }
    
    fclose(dados);
    fclose(arquivo_de_operacoes);
}

int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        // chamada da funcao que executa o arquivo de operacoes
        // o nome do arquivo de operacoes estara armazenado na variavel argv[2]
        executa_operacoes(argv[2]);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {

        printf("Modo de impressao da LED ativado ...\n");
        // chamada da funcao que imprime as informacoes da led
        imprime_led();

    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s -e nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}