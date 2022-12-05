#include <stdio.h>

float valorVenda (int quantidade){
    float total;

    if(quantidade >= 12){
       return total = quantidade * 0.30;
    }else{
        return total = quantidade * 0.35;
    }
}
main (){
    int qtde;
    float valorTotal;

    printf("Quantidade de laranjas  ");
    scanf("%i", &qtde);

    valorTotal = valorVenda(qtde);

    printf("Valor total: %.2f", valorTotal);
}