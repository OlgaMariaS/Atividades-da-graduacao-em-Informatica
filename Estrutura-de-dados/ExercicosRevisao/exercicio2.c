#include<stdio.h>

/*
Autor: Olga
data: dezembro/2022 
Obejtivo: Em uma eleição presidencial existem quatro candidatos. Os votos são informados através de códigos. Os dados utilizados para a contagem dos votos obedecem à seguinte codificação:  

- 1,2,3,4 = voto para os respectivos candidatos;
- 5 = voto nulo;
- 6 = voto em branco;

Elabore um algoritmo que leia o código do candidato em um voto. Calcule e escreva:

- total de votos para cada candidato;
- total de votos nulos;
- total de votos em branco;

PLANEJAMENTO:
Receber o valor do usuário, fazer comparações em 6 ifs, o numero que o usuário digitar será comparado aos valores dos candidatos, nulo e branco, qual numero que for igual, será incrementado a uma variavel e quando o usuário quiser finalizar a votação, será mostrado na tela a contagem dos votos.

*/
void pulaLinha(){
    return printf("-----------------------\n");
}

void main(){

    //Declarado as variaveis 
    int voto, voto1=0,voto2=0,voto3=0, voto4=0, voto5=0, voto6=0;
    char resposta[1];

    do{
        //Pede ao usuário qual o voto dele
        printf("Qual seu voto? ");
        scanf("%i", &voto);
    
        pulaLinha();

        //Compara o voto aos valores, qual for igual a variavel responsavel será incrementada, fazendo assimma contagem
        if (voto == 1)
            voto1++;
        if (voto == 2)
            voto2++;
        if (voto == 3)
            voto3++;
        if (voto == 4)
            voto4++;
        if (voto == 5)
            voto5++;
        if (voto == 6)
            voto6++;
        
        //Pergunta se o usuário quer continuar a votação
        printf("Quer continuar a votacao? s ou n: ");
        scanf("%s", &resposta);
        
    }
    while ( strcmp(resposta,"s") == 0 );     
    //No momento que o usuário digitar qualquer coisa que não seja 'S' o programa para de perguntar

    pulaLinha();

    //Mostra ao usuário a contagem final dos votos 
    printf("Quantidade de votos para: \n 1: %i\n 2: %i \n 3: %i \n 4: %i \n Nulos: %i \n Brancos: %i", voto1, voto2, voto3, voto4, voto5, voto6);

    return 0;

}