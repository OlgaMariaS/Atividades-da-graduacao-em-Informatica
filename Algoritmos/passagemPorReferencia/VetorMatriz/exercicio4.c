#include<stdio.h>
/*
Faça uma funcao que receba dois vetores de inteiros como parametro e retorne: (1) se os vetores forem iguais; (2) se os vetores tiverem os mesmos elementos mas em ordem diferente; (3) se o primeiro vetor tiver pelo menos um valor que não esta na segunda lista.

PLANEJAMENTO:
-Receber os valores de dois vetores do usuário na main;
-chamar a função COMPARA, e seus parametros serão os vetores;
-dentro da função, um primeiro for vai verificar se os valores de vetor 1 e 2 são iguais, em todos os indices, se sim "1";
-dentro deste mesmo vetor, se não for igual já apresentará o "3";
-
*/
void compara( int vetor1[], int vetor2[], int tamanho){

    int auxiliar = 0;

    /*Bloco que verifica se os elementos são exatamentes iguais ou não*/
    for (int i = 0; i < tamanho; i++){
        if (vetor1[i] == vetor2[i]){
            auxiliar++;
        }else{
            auxiliar--;
        }
        
    }
    if (auxiliar == tamanho){
        printf("Valores iguais: (1)");
    }
    if (auxiliar != tamanho)
    {
        printf("Valores diferentes: (3)");
    }
    
}

main(){
    int vetor1[4], vetor2[4];

    /*Bloco que recebe o vetor do usuário*/
    for (int i = 0; i < 4; i++){
        printf("Insira um valor para o seu vetor 1: ");
        scanf("%i", &vetor1[i]);
    }
    for (int i = 0; i < 4; i++){
        printf("Insira um valor para o seu vetor 2: ");
        scanf("%i", &vetor2[i]);
    }

    compara(vetor1,vetor2, 4);
}