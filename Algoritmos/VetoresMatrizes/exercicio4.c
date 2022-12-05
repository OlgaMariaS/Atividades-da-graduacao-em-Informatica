#include<stdio.h>

/*
Fa ca um programa que receba uma matriz M[3][3] e calcule o maior elemento da sua diagonal principal. A seguir, deve-se dividir todos os elementos de M pelo maior encontrado. Como resultado o programa deve exibir a matriz alterada.

PLANEJAMENTO:
-Criar uma matrix, e pedir os valores ao usuário;
-Pelo for, vou encontrar as linhas e colunas (0,0), (1,1), (2,2) que compõe a diagonal principal
-Será pego o elemento da diagonal e comparado ao maior, que de inicio será 0;descobrindo o maior;
-Outro for, percorrerá a matriz, e dividirá todos os elementos pelo maior e no mesmo for, será colocado dentro da matrix o valor dividido;
-Apresentará a matrix por meio de outro for;

teste:
             colunas
          | 1 | 2 | 3 |
 linhas   | 4 | 5 | 6 |
          | 7 | 8 | 10|
    
diagonal principal -> 1,5,10 ---> maior valor 10;
Matriz após divisão:
                colunas
          | 0.1 | 0.2 | 0.3 |
 linhas   | 0.4 | 0.5 | 0.6 |
          | 0.7 | 0.8 |  1  |
*/

main(){
   float matriz[3][3], maior = 0;
   int linha, coluna;

    //Bloco recebe os elementos da matriz pelo usuário
   for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna ++){
            printf("Digite um valor para a matrix: ");
            scanf("%f", &matriz[linha][coluna]);
        }
    }

    //Bloco que encontra o maior valor da diagonal principal
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna ++){

            if((linha == 0 && coluna == 0) || (linha == 1 && coluna == 1) || (linha == 2 && coluna == 2)){

                if (matriz[linha][coluna] > maior)
                {
                    maior = matriz[linha][coluna];
                }
            }
        }
    }

    printf("Maior valor da diagonal principal: %.2f \n", maior);

    //Bloco que faz a divisão dos elementos pelo maior
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna ++){
            matriz[linha][coluna] /= maior;
        }
    }

    //Bloco que apresenta ao usuário os valores final e divididos
    printf("Matriz final: \n");
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna ++){

            printf(" %.2f |", matriz[linha][coluna]);
            
        }
    }
}