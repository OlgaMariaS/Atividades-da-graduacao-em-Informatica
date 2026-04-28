/*

Desafios para Entregar:

1) Primeira Implementacao: Altere o exemplo para que as threads calculem e retornem a fatorial de um numero. Crie identificacao propria para cada thread. Vetorize as variaveis e estruturas das threads para indexa-las pela propria identificacao de cada uma. Cada thread deve calcular uma fatorial diferente, conforme informado pelo usuario. Ajuste a estrutura e os nomes das variaveis. Compile, execute e analise. Entregue o código fonte.

2) Segunda Implementacao: Modifique o exemplo para que as threads calculem e retornem o n-esimo elemento da sequencia de fibonacci, conforme n fornecido pelo
usuario. Crie identificação propria para cada thread. Vetorize as variáveis e estruturas das threads para indexa-las pela própria identificação de cada uma. As threads devem trabalhar em conjunto para calcular esse valor. Crie uma solucao da melhor forma que voce puder. Ajuste a estrutura e os nomes das variaveis. Compile, execute e analise. Entregue o código fonte.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TAM 2

void *funcaofatorSequencial(void *ptr);

struct tipoPack
{
    char mensagem[16];
    int num, fator;
};

typedef struct tipoPack tipoPack;

void main(void){   
    pthread_t thread[TAM];
    int iret[TAM];
    tipoPack pack[TAM];

    for (int i = 0; i < TAM; i++){
        sprintf(pack[i].mensagem, "\nSou a thread %d", i+1);

        pack[i].fator = 0;

        printf("\nDigite o número para a fatoração %d > ", i+1);
        scanf("%d", &(pack[i].num));
    }
    for (int i = 0; i < TAM; i++){
        iret[i] = pthread_create(&thread[i], NULL, funcaofatorSequencial, (void *)&pack[i]);

        pthread_join(thread[i], NULL);

        printf("\n Thread %d: Fator do número %d! = %d\n", i+1, pack[i].num, pack[i].fator);
    }
    
    exit(0);
}

void *funcaofatorSequencial(void *ptr)
{
    int i;

    tipoPack *pack;

    pack = (tipoPack *)ptr;

    printf("%s: vou realizar uma fatoracao", pack->mensagem);

    pack->fator = 1;
    for (i = pack->num; i >= 1; i--)
        (pack->fator) = (pack->fator) * i;
}
