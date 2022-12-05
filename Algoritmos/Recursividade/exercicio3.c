#include<stdio.h>
/*
Escreva uma função recursiva, potencia(x,y), que devolva x elevado a potencia y.
PLANEJAMENTO
-Criar a main, e pedir o numero e a potencia ao usuário;
-chamar a função e passar os parametros;
-dentro da função:
    -a potencia será reduzida até 1;
    -chegando em 1, ela multiplicará pelo N que foi informado;
    -ou seja, será multiplicado N*1 == X1 --> N*x1 == x2 --> N*x2 == x3...
    -até que finalize o numero de retornos, que será o mesmo numero de decremento da potencia, por fim retornará o valor final da potencia.
-retornar o valor ao usuário e printar a potencia;
TESTE:
n = 2, p = 4 --> resultado é 16;
*/
int calculoPotencia (int n, int p){

    if (p == 0)
       return 1;
    else
        return n * calculoPotencia(n, p -1);
    
}
main(){
    int numero, potencia, resultado;

    printf("Informe um numero: ");
    scanf("%i", &numero);
    printf("Informe a potencia: ");
    scanf("%i",&potencia);

    resultado = calculoPotencia(numero, potencia);

   printf("Resultado: %i ", resultado);
}