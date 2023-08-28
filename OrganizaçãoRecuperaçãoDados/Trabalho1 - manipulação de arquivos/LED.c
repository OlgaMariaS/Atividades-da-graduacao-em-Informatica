#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
  
    FILE *dados;
    dados = fopen("dados.dat", "r+");
    
    //led(dados, 169, 47); 
    //led(dados, 4, 80); 
    
    fclose(dados);
  
}