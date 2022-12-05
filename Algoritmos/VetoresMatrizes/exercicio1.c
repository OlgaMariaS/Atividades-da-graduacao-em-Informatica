#include<stdio.h>

/*
Faca um programa que leia um vetor de 7 posicoes de numeros e divida todos os seus elementos
pelo maior valor do vetor. Mostre o vetor ap os os calculos.

PLANEJAMENTO:
-Declarar as variveis em float pois será dividido o valor das menores pelo maior;
-pedir ao usuário 7x os valores;
-em outro for, depois que todos os valores tiverem declarados, compararemos os valores para achar o maior;
-dividir os valores menores pelo maior e colocar isso novamente dentro do vetor no indice correspondente;_
-apresentar ao usuário;
*/

main(){
    float vetor[7], divisao, maior, tamanho;
    int i, tamanhoVetor;

    maior = 0;

    //descobrirmos o tamanho do vetor
    tamanhoVetor = sizeof(vetor)/sizeof(vetor[0]);

    /*  Bloco que informar os dados no vetor*/
    for(i = 0; i < tamanhoVetor; i++){

        printf("Digite um valor: \n");
        scanf("%f", &vetor[i]);
    }

    /*  Bloco que descobre o maior  */
    for(i=0;  i < tamanhoVetor; i++){
        if(vetor[i] > maior){
            maior = vetor[i];
        }
    }
    printf("Maior numero %.2f \n", maior );
    
    /*Bloco que faz a divisão dos elementos pelo maior*/
    for (i = 0; i < tamanhoVetor; i++){
        //cria a variavel divisão para ser apresentada na tela 
        
        divisao = vetor[i] / maior;

        printf("Divisao de %.2f : ", vetor[i]);
        printf("%.2f", maior);
        printf(" = %.2f \n", divisao );

        //divide o valor x pelo maior, e já atribui ao mesmo indice no vetor
        vetor[i] = vetor[i] / maior;
        
    }
    //Apresente todos os elementos do vetor
    printf("Vetor final: ");
    for(i = 0; i < tamanhoVetor; i++){
        printf(" '%.2f' ", vetor[i]);
    }

}
