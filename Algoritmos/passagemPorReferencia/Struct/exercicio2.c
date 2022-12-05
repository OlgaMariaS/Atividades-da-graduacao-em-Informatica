#include<stdio.h>
#include<string.h>
/*
Considere a mesma situação do exercicio anterior. No entanto, ao inves de imprimir os dados do aluno no programa principal, chame uma segunda funcao que fara a exibição dos dados.
PLANEJAMENTO:
-Criar struct e preencher ela dentro da main;
-chamar a função exibe, passar o parametros sendo struct para ser exibia ao usuário dentro da função;
*/

void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}
/*Cria a struct de cadastro*/
typedef struct aluno {
    int ra;
    char nome[20];
};
/*Função quer exibe o cadastro do aluno na tela*/
void exibe(struct aluno *mostraAluno){

    printf("\nDados do aluno: \nRA:%i \nNome: %s", mostraAluno->ra, mostraAluno->nome);

}

main(){
    /*struct de alunos de informática, preenchidas pelo usuário e chamando a função que exibe os dados ao usuário*/
    struct aluno informatica;
    
    printf("Informe o RA: ");
    scanf("%i", &informatica.ra);
    flush_in();
    printf("Qual o nome do aluno: ");
    fgets(informatica.nome, 20, stdin);

    exibe(&informatica);

    
    
}