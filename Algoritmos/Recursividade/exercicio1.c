#include<stdio.h>
/*
Escreva uma função recursiva que fa ̧ca o seguinte: leia um n ́umero; se o n ́umero for negativo, a fução para; caso contrario, a funçãoo imprime o numero e faz uma chamada recursiva a si mesma.
PLANEJAMENTO
-criar a main
-chamar a funcao negativos 
-dentro da função peça um valor, se for menor que 0 apresente;
- se não chame a função novamente para que ela faça uma nova pedido até que recebe um valor que valide a condição
*/
void negativos(){
    int valor;

    printf("Informe um valor: ");
    scanf("%i", &valor);

    if (valor < 0)
    {
       printf("Valor negativo recebido");
    }else{
        return negativos();
    }
    
}
main(){

    negativos();

}