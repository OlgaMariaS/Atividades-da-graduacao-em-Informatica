#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CAMPOS 250
#define TAM_ID 5
#define LIMITADOR '|'
#define bytes_do_tamanho 2

int ajusta_topo_led(FILE *dados){
    int byteOffsett_topo_da_led;
    int novo_byteOffsett_topo_da_led;

    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1, dados); 
    fseek(dados,(byteOffsett_topo_da_led+2),SEEK_SET);
    fread(&novo_byteOffsett_topo_da_led, sizeof(novo_byteOffsett_topo_da_led), 1, dados); 

    return novo_byteOffsett_topo_da_led;
}

void inserir(FILE *dados, char *registro){
    int byteOffsett_topo_da_led;
    int novo_byteOffsett_disponivel;
    int novo_byteOffsett_topo_da_led;
    short tamanho_topo_led;
    short novo_tamanho_disponivel;
    int tamanho_registro = strlen(registro);

    //Pegando somente o identificador do registro a inserir
    int tam_id = sizeof(registro) - 3;
    char id_registro[tam_id];
    memcpy(id_registro, &registro[0], 3);

    printf("tamanho registro %i", tamanho_registro);
    printf("id registro %s", id_registro);

    rewind(dados);
    fread(&byteOffsett_topo_da_led, sizeof(byteOffsett_topo_da_led), 1, dados);
    fseek(dados, byteOffsett_topo_da_led, SEEK_SET);
    fread(&tamanho_topo_led, sizeof(tamanho_topo_led), 1, dados); 

    if(tamanho_topo_led >= tamanho_registro){

        novo_tamanho_disponivel = tamanho_topo_led - tamanho_registro;
        novo_byteOffsett_disponivel = byteOffsett_topo_da_led + tamanho_registro + bytes_do_tamanho;

        fseek(dados, byteOffsett_topo_da_led, SEEK_SET);
        fwrite(&tamanho_registro, sizeof(tamanho_registro), 1,dados);
        fseek(dados,2,SEEK_END);
        fputs(registro, dados);

        fseek(dados, novo_byteOffsett_disponivel,SEEK_SET);
        fwrite(&novo_tamanho_disponivel, sizeof(novo_tamanho_disponivel), 1,dados);
        fseek(dados,1,SEEK_END);
        fputs("*", dados);

        rewind(dados);
        novo_byteOffsett_topo_da_led = ajusta_topo_led(dados);
        fwrite(&novo_byteOffsett_topo_da_led, sizeof(novo_byteOffsett_topo_da_led), 1,dados);

        led(dados, novo_byteOffsett_disponivel, novo_tamanho_disponivel);

    }else{//Caso o espaço na led não seja suficiente pro arquivo que vou inserir, então deverá ser inserido no fim do arquivo

        fseek(dados,1,SEEK_END);
        fwrite(&tamanho_registro, sizeof(tamanho_registro), 1,dados);
        fseek(dados,2,SEEK_END);
        fputs(registro,dados);

        buscar(dados,id_registro,"i");
        printf("Sem espaços reutilizado, inserido no fim");
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

            }else if(strcmp(operacao,"i") == 0){
                printf("Insercao do registro de chave %s (%i bytes)\n", chave_primaria,tamanho_registro);
                printf("Local: Offsett = %i ", byteOffsett);
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

int main(){
    char chave[TAM_ID] = "148|Ms. Pac-Man|1982|Maze|Midway|Arcade|";

    FILE *dados;
    dados = fopen("dados.dat", "r+");
    
    inserir(dados, chave);

    fclose(dados);
}