#include<stdio.h>
#include<string.h>
/*
Faca um programa que defina uma struct com o nome e o RA de um aluno. Dentro do programa
principal declare uma variavel que seja do tipo da struct criada. Passe essa variavel para uma
função que fara o cadastro de um aluno. Quando retornar da funçao, imprima os dados do
aluno cadastrado.
PLANEJAMENTO:
-Criar o struct com dados do aluno;
-vou chamar a função e passar o struct pra ela como parametro;
-dentro da função terá os printf que preencheram o cadastro;
-o retorno da função será mostrado dentro da main;
*/

void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

typedef struct aluno {
    int ra;
    char nome[20];
};

void cadastrar(struct aluno *cadastroAluno){

    printf("Informe o RA: ");
    scanf("%i", &cadastroAluno->ra);
    flush_in();
    printf("Qual o nome do aluno: ");
    fgets(cadastroAluno->nome, 20, stdin);

    return cadastroAluno->ra;
    return cadastroAluno->nome;
}
main(){
    struct aluno informatica;
    
    cadastrar(&informatica);

    
    printf("\nDados do aluno: \nRA:%i \nNome: %s", informatica.ra, informatica.nome);
}
