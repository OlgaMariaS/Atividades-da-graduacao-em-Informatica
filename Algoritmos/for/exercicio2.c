#include<stdio.h>

/*
Sendo H = 1 + 1/2 + 1/3 + ...+1/N;faça um programa em C que tenha uma função que calcule o valor de H. O valor de N  ́e informado pelo usúario.
PLANEJAMENTO:
-Receber N do usuário;
-o For fará a soma das divisões por 1, sendo que os numeradores serão os próprios "i";
-Apresentar ao usuário a soma
*/
main(){

    float H, N, i;

    H = 0;

    printf("Digite um valor: ");
    scanf("%f", &N);

    for(i = 1; i <= N; i++){

        H = H + (1/i);

    }

    printf("A soma dos valores de H é: %.2f ", H);


}
