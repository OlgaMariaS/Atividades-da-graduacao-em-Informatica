#include <stdio.h>

/*
    "PROGRAMA "É TRIÂNGULO, E QUAL?"

-Receber 3 valores do usuário;
-Calcular se é possivel ser um triangulo -> cada uma das variaveis DEVE ser MENOR que a soma do outros dois;
-Se é triangulo, descobrir qual (Equilátero, Isósceles e Escaleno);
-Apresentar ao usuário;
-Casos de valores x, y e z:
10,10,10 -> "é triangulo e é EQUILÁTERO";
20,10,10 -> "é triangulo e é ISÓSCELES";
10,20,30 -> "é triangulo e é ESCALENO";
-1, -1, -1 -> NÃO PODE SER FORMADO UM TRIANGULO;
*/

int main(){

    float x, y, z;
    //declarado as variaveis

    printf("Digite o valor de X: ");
    scanf("%f", &x);
    printf("Digite o valor de Y: ");
    scanf("%f", &y);
    printf("Digite o valor de Z: ");
    scanf("%f", &z);
    //pedido os valores os usuário e armazenados

    if( ((x+y) >= z) || ((z+y) >= x) || ((x+z) >= y) ){
    //comparado a soma dos valores e visto se é maior, se sim é triangulo

        if((x == y) && (x == z) && (z == y)){
            printf("É triangulo EQUILATERO");
            //se todos os lados iguais é equilatero

        }
        else if((x == y) || (x == z) || (z == y)){
            printf("É triangulo ISOSCELES");
            //caso não seja equilatero e dois lados sejam iguais, então é isosceles

        }
        else {
            printf("É triangulo ESCALENO");
            //e caso não seja, nem isosceles, nem equilatero é escaleno

        }
    } else{
    //caso um lado seja maior que a soma de 2, não é possivel ser um triangulo
        printf("Não é possivel formar um triângulo");

    }
}







