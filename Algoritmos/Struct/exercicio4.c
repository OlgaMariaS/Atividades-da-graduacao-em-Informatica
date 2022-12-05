#include<stdio.h>
#include<string.h>

/*
Faca um programa que controla o consumo de energia dos eletrodomesticos de uma casa e:
• Crie e leia 5 eletrodom ́esticos que cont ́em nome (m ́aximo 15 letras), potencia (real, emkW) e tempo ativo por dia (real, em horas).
• Leia um tempo t (em dias), calcule e mostre o consumo total na casa e o consumo relativo de cada eletrodom ́estico (consumo/consumo total) nesse per ́ıodo de tempo. Apresente este ultimo dado em porcentagem.

PLANEJAMENTO:
-Criar uma struct com nome, consumo, quantidade de horas ligado;
-Fazer um for para receber os 5 eletrodomesticos;
-ler os dias de consumo;
-Fazer a multiplicação do consumo pela horas e descobrir o de cada eletro;
-Descobrir o consumo total;
-Descubro o percentual de cada eletro gasta em todo o consumo e apresentar;

*/

typedef struct consumo{
    char nome[15];
    float kw;
    float tempo;
};

void flush_in(){
    int ch;
    while((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}

void pulaLinha(){
    return printf("\n-----------------------\n");
}

main(){
    float consumoPorEletro, consumoTotal;
    int dias, qtde = 2, porcentagem;

    struct consumo eletro[qtde];

    printf("De enter para iniciar");
    /*bloco que pede ao usuário os dados dos eletros 5 vezes*/
    for (int i = 0; i < qtde; i++)
    {
        flush_in();
        printf("Nome: ");
        fgets(eletro[i].nome, 15, stdin);

        printf("Consumo: ");
        scanf("%f", &eletro[i].kw);

        printf("Tempo que fica ligado em MINUTOS: ");
        scanf("%f", &eletro[i].tempo);

        pulaLinha();
    }

    printf("Quantos dias quer calcular o consumo: ");
    scanf("%i", dias);
    pulaLinha();

    for(int i = 0; i < qtde; i++){
        consumoPorEletro = (eletro[i].kw * eletro[i].tempo) * dias;

        printf("Consumo do eletrodomestico: %s", eletro[i].nome);
        printf(" foi de: %.2f \n", consumoPorEletro);

        consumoTotal += consumoPorEletro;
    }

    printf("Consumo total de eletros é de: %.2f", consumoTotal);

    for (int i = 0; i < qtde; i++)
    {   
        consumoPorEletro = (eletro[i].kw * eletro[i].tempo) * dias;

        porcentagem = (consumoPorEletro * consumoTotal) / 100;

        printf("O percentual do %s no total do consumo de %f é de: %f",eletro[i].nome, consumoTotal, porcentagem);
    }
    
    

}