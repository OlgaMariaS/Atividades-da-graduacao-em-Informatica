#include<stdio.h>

/*Escreva um programa que receba um numero inteiro que representa um intervalo de tempo medido em minutos e devolva o numero equivalente de horas e minutos (por exemplo, 131 minutos equivalem a 2 horas e 11 minutos). Use uma struct que tenha um campo horas(inteiro) e minutos (inteiro).

PLANEJAMENTO:
-Criar um struct com os horas e minutos;
-Receber do usuário os minutos;
-Fazer uma divisão por 60 e o resto são os minutos;
-Mostrar ao usuário;

*/
typedef struct tempo{
    int horas;
    int minutos;
};
void pulaLinha(){
    return printf("-------------------------------\n");
}
main(){
    struct tempo horasMinutos;   
    int minutosRecebidos, divisao; 
   
        printf("Escreva o tempo em minutos ");
        scanf("%i", &minutosRecebidos);
        
        pulaLinha();

        horasMinutos.horas = minutosRecebidos/60;
        horasMinutos.minutos = minutosRecebidos % 60;

        printf("%i minutos sao equivalentes a: ", minutosRecebidos);
        printf("%i horas e ", horasMinutos.horas);
        printf("%i minutos", horasMinutos.minutos);
    
}