#include<stdio.h>
/*
Escreva uma funcao que, dado um vetor de n posicoes, calcule o numero de elementos pares nesse vetor. O cabecalho da sua funcao deve ser: int pares (int vetor[ ], int n);
PLANEJAMENTO:
-Criar o vetor na main;
-Criar a função que recebe vetor e o tamanho do vetor chamar ela na main;
-Dentro da função um for percorerá o vetor que fará a divisão do valores por 2, se o resto sempre for 0 é par;
-E a variavel par receber mais um, a função retornará a quantidade de numeros pares;
-Apresentar a quantidade ao usuário;
TESTE:
0,1,2,3,4,5,6,7,8,9 --> 5 números pares;
0,2,4,6,8,10,12,14,16,18 --> 10 numeroa pares;
1,3,5,7,9,11,13,15,17,19 --> 0 numeros pares;
*/
int pares (int vetor[], int n){
    int i, qtdePar = 0;

    for (i = 0; i < n; i++){
        if ((vetor[i]%2) == 0){
            qtdePar += 1;
        }
    }

    return printf("A quantidade de valores pares que informou foi de: %i", qtdePar);
    
}

main(){
    int vetorMain[10];

    for (int i = 0; i < 10; i++)
    {
        printf("Insira um valor para o seu vetor: ");
        scanf("%i", &vetorMain[i]);
    }
    
    pares(vetorMain, 10);

}