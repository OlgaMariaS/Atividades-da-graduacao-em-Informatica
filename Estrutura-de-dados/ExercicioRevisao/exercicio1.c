#include<stdio.h>
#include<string.h>

/*Autor: Olga 
Data: 30/11/22
Objetivo: 1) A prefeitura de uma cidade fez uma pesquisa entre seus habitantes, coletando dados sobre o salário e número de filhos.A prefeitura deseja saber:  
a) média do salário da população;
b) média do número de filhos;
c) maior salário;
d) percentual de pessoas com salário até R$100,00.
O final da leitura de dados se dará com a entrada de um salário negativo(Use o comando DO-WHILE).

PLANEJAMENTO:
Receber um primeiro salario e filhos, armazena-los em variaveis de filhos e salarios, depois eu pergunto se quer continuar, se sim, será perguntado novamente e os novos dados de salarios e filhos serão atribuidos a variaveis que recebem seu valor atual mais o novo valor, e ainda será incrementado uma varivel auxiliar para a media, e se o salario for menor que 100,00 será incrementado outra variavel.
*/
void pulaLinha(){
    return printf("-----------------------\n");
}

void main(){

    //Declarado as variaveis 
    int qtdeFilho, mediaFilhos, totalFilhos = 0, auxiliar = 0;
    float salarioAtual, salarioTotal, salarioMenor100, mediaSalario, percentual;
    char resposta[1];

    do{
        //Pede ao usuário o salario e quantidade de filhos
        printf("Qual seu salario? ");
        scanf("%f", &salarioAtual);
        printf("Quantos filhos tem? ");
        scanf("%i", &qtdeFilho);
        
        pulaLinha();
        
        //Pergunta se o usuário quer continuar a pesquisa
        printf("Quer continuar? s ou n \n");
        scanf("%s", &resposta);
        
        //Enquanto o usuário continuar, será somado as variaveis o total de filhos e salarios
        totalFilhos = totalFilhos + qtdeFilho;
        salarioTotal = salarioTotal + salarioAtual;
        auxiliar++;

        //Caso o salario seja menor que cem reais, será atribuido a uma variavel com o valor total dos salarios menores que cem reais
        if (salarioAtual <= 100.00)
        {
            salarioMenor100 = salarioMenor100 + salarioAtual;
        }
        
    } 
    while ( strcmp(resposta,"s") == 0 );     
    //No momento que o usuário digitar qualquer coisa que não seja 'S' o codigo para de pedir

    //Calculo das medias e percentual
    mediaFilhos = totalFilhos / auxiliar;
    mediaSalario = salarioTotal / auxiliar;
    percentual = (salarioMenor100*100) / salarioTotal;

    pulaLinha();

    //Mostra ao usuário as medias de salario e filhos e percentual 
    printf("Media de filhos: %i \n", mediaFilhos);
    printf("Media de salarios: %.2f \n", mediaSalario);
    printf("Total de salarios menores que 100,00: %.2f ", percentual);

    return 0;

}

