#include<stdio.h>
/*
Fa̧ca um programa em C que receba a idade,a altura e o peso de 4 pessoas. Calcule e mostre:
• A quantidade de pessoas com mais de 50 anos;
• A m ́edia de altura das pessoas com idade entre 10 e 20 anos;
• A porcentagem de pessoas com peso inferior a 40 quilos.

PLANEJAMENTO
-Criar um FOR
-Dentro dele pedir 4x a idade, peso, altura;
-Se maior que 50 anos 50MAIS++;
-Se idade > 10 e idade < 20 --> mediaAltura = mediaAltura + altura;
-Se peso < 40kg --> peso40 = peso40 + peso;
-Apresentar ao usuário:
-qtde de pessoa acima 50 anos
-mediaAltura / 4;
-(peso40 / 100) * somas do peso das 4 pessoas
*/

main(){
    float peso, somaAltura = 0, mediaAltura, altura, somaPesos = 0, peso40 = 0, porcentagemPeso;
    int idade, maior50 = 0;

    for(int i = 0; i < 4; i++){

        printf("Qual a idade? ");
        scanf("%i", &idade);
        printf("Qual o peso em KG? ");
        scanf("%f", &peso);
        printf("Qual a altura? ");
        scanf("%f", &altura);

        printf("-------------------- \n"); //pula linha

        if( idade > 50){
            maior50 += 1;
        }
        if(idade >= 10 && idade <= 20){
            somaAltura = somaAltura + altura;
        }
        if(peso <= 40){
            peso40 = peso40 + peso;

        }

        somaPesos = somaPesos + peso;

    }

    mediaAltura = somaAltura / 4;
    porcentagemPeso = somaPesos * (peso40/100);

    printf(" Quantidade de pessoas acima de 50 anos: %i ", maior50);
    printf("\n Média das altura entre 10 e 20 anos: %2.f ", mediaAltura);
    printf("\n Percentual de pessoas com menos de 40kg: %2.f ", porcentagemPeso);

}
