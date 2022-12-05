#include <stdio.h>

/*
        MEDIA DAS IDADES E A MAIOR

-Definir variaveis;
-Ler as idades;
-Somar as quatro idades e dividir por 4;
-Apresentar a média das idades;
-Comparar as idades e mostrar a maior idade ao usuário;
-Casos:
idades -> 10,9,8,7 = "maior idade é 10 anos, e a media é 8.5"
idades -> 10,10,10,10 = "todas as idades são iguais"
*/

int main()
{

    int idade1, idade2, idade3, idade4, maiorIdade;
    float mediaIdades;
    //Declarado as variaveis para receber as idades e a media;

    printf("idade da primeira pessoa: ");
    scanf("%i", &idade1);
    printf("idade da segunda pessoa: ");
    scanf("%i", &idade2);
    printf("idade da terceira pessoa: ");
    scanf("%i", &idade3);
    printf("idade da quarta pessoa: ");
    scanf("%i", &idade4);
    //Pedido a usuário as idades das quatro pessoas e armazenadas

    mediaIdades = (idade1 + idade2 + idade3 + idade4) / 4;
    //Media das idades

    printf("A media das idades é %0.1f ", mediaIdades);
    //Apresentado a média das idades ao usuário


    if (idade1 > idade2 && idade1 > idade3 && idade1 > idade4){
        printf("\nA maior idade é da primeira pessoa com %i anos", idade1);
        //comparado a 1° idade a todas as outras e se a maior será apresentada
    }
    if (idade2 > idade1 && idade2 > idade3 && idade2 > idade4){
        printf("\nA maior idade é da segunda pessoa com %i anos", idade2);
        //comparado a 2° idade a todas as outras e se a maior será apresentada
    }
     if (idade3 > idade2 && idade3 > idade1 && idade3 > idade4){
        printf("\nA maior idade é da terceira pessoa com %i anos", idade3);
        //comparado a 3° idade a todas as outras e se a maior será apresentada
    }
    if (idade4 > idade2 && idade4 > idade3 && idade4 > idade1){
        printf("\nA maior idade é da quarta pessoa com %i anos", idade4);
        //comparado a 4° idade a todas as outras e se a maior será apresentada
    }
    else {
        printf("\nTodas as idades são iguais");
        //caso nenhuma das suposições acima sejam verdadeiras, entende-se que todas as idades são iguais e é apresentado ao usuário
    }

}
