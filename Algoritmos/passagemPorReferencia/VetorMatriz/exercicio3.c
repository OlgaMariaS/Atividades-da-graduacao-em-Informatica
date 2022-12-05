#include<stdio.h>
/*
Faca um programa estruturado em fucoes que preencha um vetor com 4 elementos, encontre o menor elemento e troque de posicao com o primeiro elemento do vetor.
PLANEJAMENTO:
-Criar um vetor de 4 elementos e pedir que o usuário o preencha;
-chamo a função troca e passo o vetor como parametros;
-dentro da função terá um for que percorrerá o vetor e encontrará o maior;
-o maior será atribuido ao menor, e todos que forem menor que o maior será atribuido ao menor valor;
-depois trocaremos o menor valor com o indice 0 do vetor;
-aprensenta ao usuário o vetor alterado;
*/
void troca( int vetor[], int tamanho){

    /*Bloco que encontra o maior, para assim descobrir o menor valor*/
    int maior = 0; int menor;

    for (int i = 0; i < tamanho; i++){
        if (vetor[i] > maior){
            maior = vetor[i];
        }  
    }

    menor = maior;

    for (int i = 0; i < tamanho; i++){
        if (vetor[i] < menor){
            menor = vetor[i];
        }
        
    }
    printf("O menor valore e: %i \n", menor);
    /*-------------------------------------*/
    /*Bloco que apresenta o vetor alterado */
    
    vetor[0] = menor;

    printf("Vetor alterado o primeiro com o menor: ");
    for (int i = 0; i < tamanho; i++){
        
        printf("%i|", vetor[i]);
        
    };
    /*--------------------------------------*/
}

main(){
    int vetorMain[4];

    /*Bloco que recebe o vetor do usuário, e chama a função que vai trocar os valores*/
    for (int i = 0; i < 4; i++){
        printf("Insira um valor para o seu vetor: ");
        scanf("%i", &vetorMain[i]);
    }

    troca(vetorMain, 4);
    

}