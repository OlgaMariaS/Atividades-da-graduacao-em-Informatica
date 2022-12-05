#include <stdio.h>
#include <string.h>

/*
Faca um programa que receba uma palavra e a imprima de tras para frente.
PLANEJAMENTO
-receber a palavra
-percorrer os caracteres da palavra com for;
-que vai ler somente a ultima letra e apresentar, depois diminuiremos o i e apresentará a penultima, basicamente vai apresentar a mesma palavra em ordem decrescente
-apresentar ao usuário;
*/

int main()
{
      int i, tamanhoPalavra;
      char palavra[15];

      printf("Digite uma palavra: ");
      fgets(palavra, 15, stdin);

      tamanhoPalavra = strlen(palavra);
      
      for (i = tamanhoPalavra; i >= 0; i--)
      {
        /*o i = tamanho da palavra, e ele deve chegar até 0, por isso i--, logo se tamanho = 5, a palavra mostrará o que tem no indice 5, e depois no 4...*/

        printf("%c", palavra[i]);
        //deve ser %c (ele vai entender como Caracter e não como uma string toda se usarmos o S);
      }     

      return 0;
}
