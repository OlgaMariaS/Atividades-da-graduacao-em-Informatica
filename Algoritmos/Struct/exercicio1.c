#include<stdio.h>
#include<string.h>

/*Crie um cadastro de alunos com RA, Nome, Curso e Serie. Cadastre 5 alunos. Em seguida liste o RA e o nome dos alunos do primeiro ano de Ciencia da Computacao

PLANEJAMENTO:
-Criar um struct com os dados para cadastro;
-Criar um for que leia 5 vezes os dados;
-Ler Se o curso é igual ao ciencia da computação;
-se for igual ver se a serie é 1°;
-se sim apresentar ao usuário;

*/
typedef struct uem{
    int ra;
    char nome [20];
    char curso [20];
    int serie;
};
void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}
void pulaLinha(){
    return printf("-----------------------\n");
}

main(){
    struct uem alunos[2];
    int i;
    
    for(i=0; i < 2; i++){
        printf("RA: ");
        scanf("%i", &alunos[i].ra);

        flush_in();
        printf("Nome: ");
        fgets(alunos[i].nome, 20, stdin);

        printf("Curso: ");
        fgets(alunos[i].curso, 20, stdin);
        
        printf("Serie: ");
        scanf("%i", &alunos[i].serie); 

        pulaLinha();

    }

    printf("Alunos do 1 anos de ciencia da computacao");

    for(i=0; i < 2;i++){
        if ( strcmp(alunos[i].curso, "ciencia") == 0 )
        {
           printf("%s \n", alunos[i].curso);
        }
        
    }
    
}