#include <stdio.h>

/*
Dado dois vetores, A (5 elementos) e B (7 elementos), fa̧ca um programa que imprima todos
os elementos comuns aos dois vetores.

Planejamento:
-Criar dois vetores, um de 5 elemento e outro de 7;
-Pedir ao usuário os elementos do vetor A e os elementos do vetor B;
-criar um for dentro de outro for, no qual vai percorrer o vator de 7 elementos, e no indice X, vai igualar ele aos elementos do outros vetor;
-se for igual será armazenado em um terceiro vetor chamado intersecaoAB;
-apresenta ao usuário;

Teste:
- A [1,2,3,4,5]; B [9,5,1,7,2,14,10,11], intersecaoAB = 1,2,5;
*/
int pulaLinha(){
   return printf("\n--------------------------\n");
}
int main(){
    int vetorA[5], vetorB[8], i, j, tamanhoVetorA, tamanhoVetorB, intersecaoAB = 0;

    /*Calcula o tamanho dos vetores A e B */
    tamanhoVetorA = sizeof(vetorA)/sizeof(vetorA[0]);
    tamanhoVetorB = sizeof(vetorB)/sizeof(vetorB[0]);

    /*Pede os valores de A, e apresenta ao usuário*/
    for(i = 0; i < tamanhoVetorA; i++){

        printf("\nDigite um valor para o vetor A: ");
        scanf("%i", &vetorA[i]);
    }    
    printf("\nVetor A: ");
    for(i = 0; i < tamanhoVetorA; i++){
        printf(" '%i' ", vetorA[i]);
    }
    pulaLinha();

    /*Pede os valores de B, e apresenta ao usuário*/
    for(j = 0; j < tamanhoVetorB; j++){

        printf("\nDigite um valor para o vetor B:  ");
        scanf("%i", &vetorB[j]);
    }
    printf("\nVetor B: ");
    for(j = 0; j < tamanhoVetorB; j++){
        printf(" '%i' ", vetorB[j]);
    }
    pulaLinha();

    /*Descobre os elementos em comum */
    printf("Intersecao de A e B: ");

    for(i = 0; i < tamanhoVetorA; i++){
        for(j = 0; j < tamanhoVetorB; j++){

            if (vetorA[i] == vetorB[j]){

                if (intersecaoAB == vetorA[i]){}
                else{
                    intersecaoAB = vetorA[i];
                    printf(" '%d' ",vetorA[i]);
                }
            }
        }
    }
}