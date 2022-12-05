#include <stdio.h>

/*
    "MEDIA DO ALUNO"

-Receber a media do aluno;
-Comparar a media a valores de 0.0 a 10.0;
-Apresentar o conceito;
-Casos de valores:
0.0 a 4.9 -> D;
5.0 a 6.9 -> C;
7.0 a 8.9 -> B;
8.9 a 10.0-> A;
*/

int main(){

    float media;
    //declarado as variavel

    printf("Digite o valor da media do aluno: ");
    scanf("%f", &media);
    //pedido a média do aluno e armazenada;

    if(media > 0){
    //comparando se media é maior que 0

        if(media >= 0.0 && media <= 4.9){
            printf("D");
            //se maior que 0 e menor que 4.9, apresenta D
        }
        if(media >= 5.0 && media <= 6.9){
            printf("C");
            //se maior que 5 e menor que 6.9, apresenta C
        }
        if(media >= 7.0 && media <= 8.9){
            printf("B");
            //se maior que 7 e menor que 8.9, apresenta B
        }
        if(media >= 9.0 && media <= 10.0){
            printf("A");
            //se maior que 9 e menor que 10, apresenta A
        }
    } else{
    //caso media for menor que zero, será avisado ao usuário
        printf("Media inferior a 0");
    }

}








