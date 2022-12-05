#include<stdio.h>
#include<string.h>

/*
Crie uma estrutura representando os alunos do curso de Fundamentos de Algoritmos. A estrutura deve conter a matr ́ıcula do aluno, nome, nota da primeira prova,nota da segunda prova e nota da terceira prova.
• Permita ao usu ́ario entrar com os dados de 5 alunos.
• Encontre o aluno com maior nota da primeira prova.
• Encontre o aluno com maior m ́edia geral.
• Encontre o aluno com menor m ́edia geral
• Para cada aluno diga se ele foi aprovado ou reprovado, considerando o valor 6 para aprovacao.

PLANEJAMENTO:
-Criar um struct que receba o nome, matricula, notas;
-Criar um for que vá receber os dados de 5 alunos;
-Criar outro for que calcule as médias de cada alunos, e armazena a media final e se >6 aprovado, e adicionar a mediafinal de cada um em mediaTotal, e encontrar quem tem a maior e menos média por meio de if.
*/

typedef struct calculoNota{
    int matricula;
    char nome[20];
    float nota1;
    float nota2;
    float nota3;
};

void flush_in(){
    /*função que limpa a memória, para o fgets não entenda o enter como caracter*/
    int ch;
    while((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}

void pulaLinha(){
    return printf("\n-----------------------\n");
}

main(){
    float mediaFinal, mediaTotal, maiorMedia = 0, menorMedia = 10, maiorNota1 = 0;
    struct calculoNota algoritmo[5];

    /*bloco que pede ao usuário os dados de cada aluno 5 vezes*/
    for (int i = 0; i < 5; i++)
    {
        printf("Matricula: ");
        scanf("%f", &algoritmo[i].matricula);

        flush_in();
        printf("Nome: ");
        fgets(algoritmo[i].nome, 20, stdin);

        printf("Nota 1: ");
        scanf("%f", &algoritmo[i].nota1);

        printf("Nota 2: ");
        scanf("%f", &algoritmo[i].nota2);

        printf("Nota 3: ");
        scanf("%f", &algoritmo[i].nota3);

        pulaLinha();
    }

    for (int i = 0; i < 5; i++){

        /*Calculo da media de cada aluno*/
        mediaFinal = (algoritmo[i].nota1 + algoritmo[i].nota2 +algoritmo[i].nota3) / 3;

        /*Bloco que verifica se o aluno passou ou não*/
        printf("\nAluno: %s", algoritmo[i].nome);
        
        if (mediaFinal > 6.0)
        {
            printf("Aprovado com media final: %.2f", mediaFinal);
        }else{
        
        printf("Reprovado com media final: %.2f", mediaFinal);
        }

        pulaLinha();

        /*Bloco que verifica a maior media*/
        if (mediaFinal > maiorMedia)
        {
            maiorMedia = mediaFinal;

        }
        
        /*Bloco que verifica a menor media*/
        if (mediaFinal < menorMedia)
        {
            menorMedia = mediaFinal;
        }

        /*Descobre a maior nota da primeira prova*/
        if(algoritmo[i].nota1 > maiorNota1){
            maiorNota1 = algoritmo[i].nota1;
        }
    }

    /*Apresenta a maior, menor e nota da 1° prova*/
    printf("Maior media foi %.2f", maiorMedia);
    pulaLinha();
    printf("Menor media foi %.2f", menorMedia);
    pulaLinha();
    printf("Maior Nota da primeira prova foi %.2f", maiorNota1);


    

}