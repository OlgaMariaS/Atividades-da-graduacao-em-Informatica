/*
Exemplo 01: testar a criacao de threads, bem como a espera pelo termino delas.

===========
Explicacoes
===========

O prototipo da funcao de criacao de uma thread eh especificado da seguinte forma.

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *atributos,
                   void *funcao_da_thread(void *),
                   void *arg_da_funcao);

Ela usa 4 parametros:

1) O primeiro, "*thread", usado para conter o identificador da thread retornado pelo sistema/biblioteca, do tipo "pthread_t" (identifica a thread por meio de um número). Essa variável deve ser declarada no programa principal, no qual as threads são criadas. Ela retorna valores diferentes no Windows e no Linux.

2) O segundo, "*atributos", variável do tipo "pthread_attr_t", usada para conter atributos iniciais para a thread, fornecidos pelo programador, os quais podem definir o estado, a política de escalonamento, o escopo de ação e o tamanho da pilha, entre outros. Ela deve ser declarada no programa principal ou NULL pode ser usado para indicar atributos padrão.

3) O terceiro, "*funcao_da_thread", eh o nome da funcao que sera executada pela thread criada. Essa funcao deve ser definida do tipo void e deve ter um único parâmetro também do tipo void.

4) O quarto e ultimo parametro, "*arg_da_funcao", é o argumento a ser passado para a funcao da thread. Esse parametro pode representar o dado de um tipo simples, string, vetorial, estrutura ou area de memoria, declarado no programa principal; deve ser convertido como um ponteiro para void na chamada da função e "desconvertido" internamente na execução da função.

Se bem sucedida, a funcao pthread_create() retorna 0, caso contrario, retorna o numero do erro. Nesse caso, o valor retornado no argumento "thread" eh indefinido.

O programa principal costuma ser referenciado como a thread principal.

A espera pelo termino das threads pode ser feito pela funcao pthread_join que possui o seguinte prototipo:

int pthread_join(pthread_t thread, void **retval);

Ela usa 2 parametros:

1) O primeiro, "thread", identifica uma thread que tenha sido criada de forma bem sucedida com pthread_create.

2) O segundo, "retval", retorna o status de termino da thread, exceto se NULL for utilizado.

Se bem sucedida, a funcao pthread_join() retorna 0, caso contrario, retorna o numero do erro. Nesse caso, o valor retornado no argumento "retval" eh indefinido.

Observação:

O identificador de uma thread pode ser obtido por ela própria por meio da função pthread_self(), sem argumento. No windows, esse identificador é um número inteiro, iniciado a partir de 1 (um), para a primeira thread criada, 2 (dois) para a segunda thread criada e assim suscessivamente. Assim, no Windows, esse identificador pode ser usado para indexar as estruturas de dados usadas pelas threads. Mas no Linux, esse identificador é um número grande, gerado de forma não subsequente a cada vez e não pode ser usado como indexador. Assim, no Linux, o proprio programador deve criar e controlar as identificações das threads para poder usa-las como indexadores de estruturas.

===========
Experimento
===========

Digite o codigo em C a seguir em um editor de texto e salve o arquivo com o seguinte nome:

exemplo01.c

Depois, compile o programa em linha de comando da seguinte forma:

cc -lpthread exemplo01.c -o exemplo01

ATENCAO: dependendo da distribuicao Linux, eh possivel que a biblioteca de threads tenha outra forma de chamada, como por exemplo, pthread, sem o 'l' de library. Nesse caso, use apenas -pthread ao inves de  -lpthread.

Corrija os erros de compilacao. Quando a compilacao for bem sucedida, o arquivo executavel "exemplo01" serah criado.

Entao, execute o executavel com a seguinte linha de comando:

./exemplo01

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcaoImprimeMensagem( void *ptr );

void main(void)
{
    pthread_t thread1, thread2;
    char mensagem1[16] = "\nSou a thread 1";
    char mensagem2[16] = "\nSou a thread 2";
    int  iret1, iret2;

    /* Cria 2 threads independentes e ambas executarao a mesma funcao
       com argumentos diferentes */

    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) mensagem1);

    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) mensagem2);

    printf("\nCriacao da thread 1 retornou: %d\n",iret1);
    printf("\nCriacao da thread 2 retornou: %d\n",iret2);

    /* Espera as threads completarem para entao continuar, para nao
       correr o risco de terminar o programa principal antes das
       threads terminarem. O termino do processo causa forcadamente
       o termino de suas tarefas */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nAmbas as threads 1 e 2 ja finalizaram e agora eu (o main) finalizarei...\n");
    exit(0);
}

void *funcaoImprimeMensagem(void *ptr )
{
     char *mensagem;
     mensagem = (char *) ptr;
     printf("%s \n", mensagem);
}