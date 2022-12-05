#include<stdio.h>
/*
Escreva uma fução recursiva, ImprimeSerie(int i,int j, int k), que imprime na tela a serie de valores do intervalo [i,j], com incremento k.
PLANEJAMENTO
-Pedir os dois valores ao usuário e o incremento;
-chamar a função, e passar os parametros, dentro dela:
    - se o valor1 for menor que o valor final, vai ser impresso
    - somaremos valor1+incremento, e este agora será o valor 1, e será passado ao função;
    - dentro da função fará a mesma lógica x < valor final == s imprime, e soma o incremento novamente;
    -até que o valor inicial seja igual ao final, ai imprime e para;

TESTE:
-[2,13] k = 3 --> 2,5,8,11; 
*/

void ImprimeSerie(int i,int j, int k) {

    if (i <= j){
       printf(" %i|", i);
       ImprimeSerie(i+k, j, k);
    }
}

main(){ 
    int i, j, k;

    printf("Informe dois numeros: ");
    scanf("%i %i", &i, &j);

    printf("Informe um incremento ao valor 1: ");
    scanf("%i", &k);

    printf("Serie de %i ate %i e: ", i, j);
    ImprimeSerie(i, j, k);

}


