#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ID 5
#define LIMITADOR '|'
#define bytes_do_tamanho 2

/*Função de Led (Lista de Espaços Disponiveis), responsável por armazenar e ordenar os espaços marcados como removidos*/
void led(FILE *dados, int byteOffset_do_registro_removido, short tamanho_registro_removido){
    int byteOffsett_topo_da_led;
    short tamanho_topo_led;
    short led_vazia = -1;    
    
    //Aponta pro inicio do arquivo,se o inicio do arquivo estiver vazio, ou seja em binario (-1), então a led está vazia
    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1, dados); 
    printf("byte offsett led %i\n", byteOffsett_topo_da_led);
    
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
    
        printf("tamanho led %i\n", tamanho_topo_led);

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

/*Funcao REMOVER é responsavel por encontrar o registro a partir da chave primaria, e sinalizar ele como removido com caracter '*' */
void remover(FILE *dados, int byteOffsett, short tamanho_registro, char *chave_primaria){
    //Marca a chave como removida e envia o tamanho disponivel a LED
    byteOffsett -= 1;
    fseek(dados,byteOffsett, SEEK_SET);
    fputs("*", dados);
    byteOffsett -= 1;
    led(dados, byteOffsett, tamanho_registro);
    
    printf("Remocao do registro de chave '%s' \nRegistro removido! (%i bytes)\nLocal: offset = %i bytes \n\n", chave_primaria, tamanho_registro, byteOffsett);         
}

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
            if((strcmp(operacao,"b")) == 0){
                char registro[tamanho_registro];
                //leia_chave(registro, tamanho_registro, dados);
                printf("Busca pelo registro de chave %s\n", chave_primaria);
                printf("%s|%s", chave_primaria, registro);
                printf(" (%i bytes) \n\n", tamanho_registro);

            }else if((strcmp(operacao,"i")) == 0){
                printf("Insercao do registro de chave %s (%i bytes)\n", chave_primaria,tamanho_registro);
                printf("Local: Offsett = %i \n", byteOffsett);
            }else if ((strcmp(operacao,"r")) == 0){
                //caso a operação não seja de busca ou verificar uma inserção, ela será de remover, assim deve chamar a função que remove
                remover(dados, byteOffsett, tamanho_registro, chave_primaria);
            }
            achou = 1;
        }else{
            byteOffsett += tamanho_registro;
            achou = 0;
        }
    }
}

/*Função retorna quem é o proximo byteOffsett que a led aponta */
int ajusta_topo_led(FILE *dados){
    int byteOffsett_topo_da_led;
    int novo_byteOffsett_topo_da_led;

    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 4, dados); 
    fseek(dados,(byteOffsett_topo_da_led+2),SEEK_SET);
    fread(&novo_byteOffsett_topo_da_led, sizeof(novo_byteOffsett_topo_da_led), 4, dados); 

    return novo_byteOffsett_topo_da_led;
}

void inserir(FILE *dados, char *registro){
    int byteOffsett_topo_da_led;
    int novo_byteOffsett_disponivel;
    int novo_byteOffsett_topo_da_led;
    short tamanho_topo_led;
    short novo_tamanho_disponivel;
    short tamanho_registro = strlen(registro) + bytes_do_tamanho;

    //Pega somente o identificador do registro a inserir
    int tam_id = sizeof(registro) - 3;
    char id_registro[tam_id];
    memcpy(id_registro, &registro[0], 3);
    
    /*Aponta pro byteOffsett do topo da led e o guarda tamanho */
    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1, dados);
    fseek(dados, byteOffsett_topo_da_led, SEEK_SET);
    fread(&tamanho_topo_led, sizeof(tamanho_topo_led), 1, dados); 

    printf("tamanho registro %i\n", tamanho_registro);
    printf("tamanho led %i\n", tamanho_topo_led);
    printf("byte offsett led %i\n", byteOffsett_topo_da_led);

    //verifica se o tamanho disponivel na led é capaz de armazenar o tamanho do registro novo
    if((tamanho_topo_led >= tamanho_registro) && (byteOffsett_topo_da_led != -1)){
        
        //Armazena o tamanho que vai sobrar da inserção, e onde será o byte offsett da sobra
        novo_tamanho_disponivel = (tamanho_topo_led - tamanho_registro) - bytes_do_tamanho;
        novo_byteOffsett_disponivel = byteOffsett_topo_da_led + tamanho_registro + bytes_do_tamanho;

        //Recebo o offsett de quem era o proximo da led, ou seja o 2° maior espaço, e escreve ele no topo da led        
        novo_byteOffsett_topo_da_led = ajusta_topo_led(dados);
        
        //Aponta pro byteoffsett disponivel, e escreve o tamanho do registro, depois escreve o registro
        fseek(dados, byteOffsett_topo_da_led, SEEK_SET);
        fwrite(&tamanho_registro, sizeof(tamanho_registro), 1,dados);
        fputs(registro, dados);

        //Aponta para o byteOffsett que começa as sobras, e escreve o tamanho disponivel, adiciona *
        fseek(dados, novo_byteOffsett_disponivel,SEEK_SET);
        fwrite(&novo_tamanho_disponivel, sizeof(novo_tamanho_disponivel), 1,dados);
        fputs("*", dados);

        //Escreve o novo topo da led
        rewind(dados);
        fwrite(&novo_byteOffsett_topo_da_led, sizeof(novo_byteOffsett_topo_da_led), 1,dados);

        //chama a função led passando o espaço que sobrou para ela ser alocada
        //led(dados, novo_byteOffsett_disponivel, novo_tamanho_disponivel);

        //Função de busca pra verificar se foi inserido
        buscar(dados,id_registro,"i");
        printf("Tamanho de espaco reutilizado: %i bytes (Sobra de %i bytes)\n\n", tamanho_registro, novo_tamanho_disponivel);

    }else{//Caso o espaço na led não seja suficiente pro arquivo que vou inserir, então deverá ser inserido no fim do arquivo

        /*Aponta pro fim do arquivo, e escreve o tamanho do registro, depois escreve o novo registro, e faz uma busca pra verificar se foi inserido*/
        fseek(dados,0,SEEK_END);
        fwrite(&tamanho_registro, sizeof(tamanho_registro), 1,dados);
        fputs(registro,dados);
        buscar(dados,id_registro,"i");
        printf("Tamanho de espaco reutilizado: 0 bytes (Sobra de 0 bytes)\n\n");
    }
}

int main(){
    //char chave[200] = "148|Ms. Pac-Man|1982|Maze|Midway|Arcade|";
    char re[TAM_ID] = "3";

    FILE *dados;
    dados = fopen("dados.dat", "r+");
    
    //inserir(dados, chave);
    buscar(dados, re, "r");

    fclose(dados);
}