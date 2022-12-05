#include<stdio.h>
/*
Escreva um procedimento que intercala os valores de dois vetores inteiros de mesmo tamanho em um terceiro vetor. Tome cuidado ao definir o tamanho do terceiro vetor. Seu cabecalho deve ser: void intercala (int v1[ ], int v2[ ], int v3[ ], int dimensao);
PLANEJAMENTO:
-Receber do usuário os valores de dois vetores, que terão tamanho 5;
-chamar a função INTERCALA, passando os vetores preenchidos, o vetor a intercalar e o tamanho;
-Dentro da função existirá um for que se o i for divisivel por 2, o indice do v3 receberá o indice v1, e se não receberá o indice do v2;
- 
-Apresentar ao usuário o vetor 3 que tem os vetores intercalados;
*/

void pulaLinha(){
    return printf("\n--------------------------\n");
}
void intercala (int v1[ ], int v2[ ], int v3[ ], int dimensao){
    int j = 0, tam = dimensao/2;

    for (int i = 0; i < dimensao && j < tam; i+=2){

        v3[i] = v1[j];
        v3[i+1] = v2[j];

        j++;
    }
    
    pulaLinha();
    printf("Intercalado entre v1 e v2: ");
    for (int i = 0; i < dimensao; i++){
        printf(" %i|", v3[i]);
    } 
}

main(){
    int vetor1[5], vetor2[5], conjuncao[10];

    for (int i = 0; i < 5; i++)
    {
        printf("Digite 5 valores para o seu vetor 1: ");
        scanf("%i", &vetor1[i]);
    }

    pulaLinha();

    for (int i = 0; i < 5; i++)
    {
        printf("Digite 5 valores para o seu vetor 2: ");
        scanf("%i", &vetor2[i]);
    }
  
    intercala(vetor1,vetor2, conjuncao, 10);

}