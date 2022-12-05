#include<stdio.h>

/*Durante dez dias de um determinado mˆes, foram colhidas as temperaturas m ́edias di ́arias de
uma determinada regi ̃ao em graus celsius. Fa ̧ca um programa em C que calcule e informe a
temperatura m ́edia destes dias, e a temperatura mais alta do per ́ıodo.

PLANEJAMENTO
-Pedi ao usuário por meio do FOR 10 vezes a temperatura;
-Armazenar a temperatura informada
-Enviar a temperatura informada a um if que compara se é maior que a outra
-Exibir ao usuário a maior temperatura;
*/

main(){

    int i;
    float temperaturaInformada, maiorTemperatura, soma, media;

    soma = 0;

    for(i = 0; i < 10; i++){
printf("Maior temperatura e: %f ", maiorTemperatura);

        printf("Escreva a Temperatura ");
        scanf("%f", &temperaturaInformada);

        if(temperaturaInformada > maiorTemperatura ){
           maiorTemperatura = temperaturaInformada;
        }

        soma  = soma + temperaturaInformada;

    }

    media = soma / 10;
    printf("Media dos 10 dias e: %.2f ", media);
    printf("\nMaior temperatura e: %.2f ", maiorTemperatura);

}
