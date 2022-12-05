#include <stdio.h>

void porExtenso (int numeroDecimal){
    switch (numeroDecimal){
        case 1: printf("UM");
        break;
        case 2: printf("DOIS");
        break;
        case 3: printf("TRES");
        break;
        case 4: printf("QUATRO");
        break;
        case 5: printf("CINCO");
        break;
        case 6: printf("SEIS");
        break;
        case 7: printf("SETE");
        break;
        case 8: printf("OITO");
        break;case 10: printf("UM");
        break;
        case 9: printf("NOVE");
        break;
        case 10: printf("DEZ");
        break;
        default: printf("numero invalido");
    }
}
main (){
    int numero;

    printf("Escolha um numero de 0 a 10: ");
    scanf("%i", &numero);

    porExtenso(numero);
}