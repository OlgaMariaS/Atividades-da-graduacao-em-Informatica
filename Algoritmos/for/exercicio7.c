#include <stdio.h>
#include <string.h>
/*
Faca um programa em que troque todas as ocorrencias de uma letra (l1) seja trocada pela L2 em uma
string. A string e as letras palavra e L2 devem ser fornecidas pelo usuario.

PLANEJAMENTO
-Receber uma palavra do usuário;
-receber quais letras ele quer trocar;
-percorrer a string com for, se encontrar l1 substituirá por l2
-se encontrar l2 substituirá por l1
*/
void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}
int main()
{
      char palavra[10],l1[1],l2[1];
      int tamanhoPalavra;

      printf("Digite uma palavra: ");
      fgets(palavra, 10, stdin);

      printf("Informe uma letra a ser encontrada: ");
      fgets(l1, 1, stdin);

      flush_in();
      printf("Informe um letra substituta: ");
      fgets(l2, 1, stdin);

     /* tamanhoPalavra = strlen(palavra);

      for (int i = 0; i < tamanhoPalavra; i++)
      {
        if (palavra[i] == l1[0]){
          palavra[i] = l2[0];
        }
      }
      printf("%s", palavra); */
}
