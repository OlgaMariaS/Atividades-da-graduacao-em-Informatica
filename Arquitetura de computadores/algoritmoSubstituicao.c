#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*ALGORITMO QUE SIMULA ALOCAÇÕES NA MEMORIA CACHE, QUANDO ESTA CHEIA*/

//Variaveis globais
int contador_de_acessos_recentes[5] = {0,0,0,0,0};
int contador_da_frequencia_acessos[5] = {0,0,0,0,0};
int tamanho = 5;
int tempo = 0;

//Função que pula a linha
void pulaLinha(){
    printf("_________________________\n");
}

//Função que imprime na tela os valores do vetor 
void imprime(int vetor[5]){
    for (int i = 0; i < tamanho; i++){
        printf(" %i |", vetor[i]);
    }
}

//Função pro usuário acessar a memória, que vai auxiliar nas funções de contagem do menos recente e menos frequente
void acessa_memoria(int memoria[5]){
    char querAcessar[1];
    strcpy(querAcessar,"s");
    int posicao;

    pulaLinha();
    printf("Para sabermos qual o menos recente e o menos frequente, preciso que acesse sua memoria \n\n");

    while((strcmp(querAcessar,"s")==0)){
        printf("\nQual posicao quer ver na memoria: ");
        scanf("%i", &posicao);

        for(int i = 0; i < tamanho; i++){
            if(posicao == i){
                printf("Posicao %i contem o valor: %i\n", posicao, memoria[i]);

                menosFrequente(posicao);
                menosRecente(posicao);
            }
        }
        printf("Continuar acessando: (s/n) ");
        scanf("%s", querAcessar);
        pulaLinha();
    }
    if(strcmp(querAcessar,"n")==0){
        printf(" \n Terminou os acessos \n");
    }
}

void menosRecente(int posicaoAcessada){
    tempo++;
    contador_de_acessos_recentes[posicaoAcessada] = tempo;
}
void menosFrequente(int posicaoAcessada){
    contador_da_frequencia_acessos[posicaoAcessada]++;
}

//Funcões que fazem a substituição na memória
void LRU (int memoria[5], int valor_a_alocar){
    int menosAcessadoRecentemente = 0;
   
    for (int i = 1; i < tamanho; i++) {
        if (contador_de_acessos_recentes[i] < contador_de_acessos_recentes[menosAcessadoRecentemente]) {
            menosAcessadoRecentemente = i; 
        }
    }
    memoria[menosAcessadoRecentemente] = valor_a_alocar;
    pulaLinha();
    printf("Substituicao pela posicao %i, que foi o usado menos recentemente: \n", menosAcessadoRecentemente);

}
void FIFO(int vetor[5], int valor_a_alocar){
    vetor[0] = valor_a_alocar;

    printf("\n Alocado na primeira posicao: \n\n");
}
void LFU (int memoria[5], int valor_a_alocar){
    int menosAcessadoFrequentemente = 0;
   
    for (int i = 1; i < tamanho; i++) {
        if (contador_da_frequencia_acessos[i] < contador_da_frequencia_acessos[menosAcessadoFrequentemente]) {
            menosAcessadoFrequentemente = i; 
        }
    }
    memoria[menosAcessadoFrequentemente] = valor_a_alocar;
    pulaLinha();
    printf("Substituicao pela posicao %i, que foi menos acessado frequentemente: \n", menosAcessadoFrequentemente);
}

void aleatorio(int vetor[5], int valor_a_alocar){
    srand( (unsigned)time(NULL) );
    int posicaoAleatorio = (rand() % 4);
    vetor[posicaoAleatorio] = valor_a_alocar;

    printf("Alocado na posicao %i, aleatoriamente: \n", posicaoAleatorio);
}
/*----------------------------------------------------------------*/
int main (){
    int memoria[5];
    int opcao;
    int i;
    int valor_sem_alocar;
       
    for(i = 0; i < tamanho; i++){

        printf("Informe um valor pra memoria: ");
        scanf("%i", &memoria[i]);

        if(i >= (tamanho-1) ){
            printf(" \nFalta lugar na memoria \n Escolha uma das opcoes para substituicao \n");
            printf("  1- Usado menos recentemente \n  2- O primeiro que entrou \n  3- Usado com menos frequencia \n  4- Escolha aleatoria \n\n");
            scanf("%i", &opcao);

            printf("Qual o valor quer alocar: ");
            scanf("%i", &valor_sem_alocar);
        }

        switch (opcao){
            case 1:
                acessa_memoria(memoria);
                LRU(memoria,valor_sem_alocar);
                imprime(memoria);
            break;
            case 2:
                FIFO(memoria,valor_sem_alocar);
                imprime(memoria);
            break;
            case 3:
                acessa_memoria(memoria);
                LFU(memoria, valor_sem_alocar);
                imprime(memoria);
            break;
            case 4:
                aleatorio(memoria, valor_sem_alocar);
                imprime(memoria);
            break;
            default:
                break;
        }

    }
}