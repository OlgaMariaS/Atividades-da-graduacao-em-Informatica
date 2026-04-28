/* Desafio 07: este codigo esta gerando resultados incorretos, eventuais, visiveis nas impressoes na tela. As threads estao retornando resultados parciais corretos
mas a thread main() nao esta identificando corretamente o resultado geral correto.
Entao, ajuste o codigo para autoconferir se a implementacao esta correta. A ideia eh comparar exaustivamente os resultados obtidos pela logica sequencial com os
resultados obtidos pela logica paralela.

Faça o programa principal resolver o problema de busca sequencialmente, logo após a geração aleatória do vetor. Depois, compare esses resultados (ditos verdadeiros)
com os resultados da execução paralela. Pare a verificação na ocorrência de erro e mostre a situação da execução. O usuário deve informar quantas vezes ele quer
executar a verificação. O usuário também continua informando o tamanho do vetor.
*/

/*
Olga Maria - RA 130002

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define maxThreads 50
#define maxElem 100

void *buscaMaiorMenor(void *ptr);
void validaResultado(int tamVetor, int paralMaior, int paralMenor);
void geraVetor(int n);

int vet[maxElem];

struct tipoPack {
   int tid, ini, fim, posMaior, posMenor;
};

typedef struct tipoPack tipoPack;

void main(void)
{
    pthread_t thread[maxThreads];

    int qtdeExe, qtdeMaxExe, seq, i, iret[maxThreads], kThreads;
    int ini, fim, faixa, restante, nElem, posMaior, posMenor;

    tipoPack pack[maxThreads];

    srand(time(NULL));

    printf("Programa Multithread para Buscar Maior e Menor Elementos\n");

    /*Logica para repetição do programa*/
    qtdeExe=1;
    printf("\nDeseja quantas execuções do programa? => ");
    scanf("%d", &qtdeMaxExe);
    if(qtdeMaxExe < 1){
        printf("\nPrograma deve receber ao menos 1 execucao!");    
        exit(1);
    }

    while (qtdeExe <= qtdeMaxExe){
        nElem=0;
        while (nElem<1) {
        printf("\nEntre com numero de elementos do vetor (nao nulo) => ");
        scanf("%d", &nElem);
        }

        geraVetor(nElem);        

        kThreads=0;
        while ((kThreads<1)||(kThreads>nElem)) {
            printf("\nO numero de threads nao pode ser nulo e nem maior que o numero de elementos!");
            printf("\nEntre com o numero de threads => ");
            scanf("%d", &kThreads);
        }

        faixa = nElem/kThreads;
        restante = nElem % kThreads;

        ini = 0;
        fim = faixa-1;

        if (restante>0){
            fim++;
            restante--;
        }

        for (i=0; i<kThreads; i++){
            pack[i].tid=i+1;
            pack[i].ini = ini;
            pack[i].fim = fim;
            pack[i].posMaior=ini;
            pack[i].posMenor=ini;

            ini=fim+1;
            fim=ini+faixa-1;

            if (restante>0){
                fim++;
                restante--;
            }
        }

        for (i=0; i<kThreads; i++)
            iret[i] = pthread_create(&(thread[i]), NULL, buscaMaiorMenor, (void*) &pack[i]);

        for (i=0; i<kThreads; i++)
            pthread_join(thread[i], NULL);

        printf("\nThread %d: achou Maior = %d e Menor = %d\n", 1, vet[pack[0].posMaior], vet[pack[0].posMenor]);
        posMaior=pack[0].posMaior;
        posMenor=pack[0].posMenor;

        for (i=1; i<kThreads; i++){
            printf("\nThread %d: achou Maior = %d e Menor = %d\n", i+1, vet[pack[i].posMaior], vet[pack[i].posMenor]);
            if (vet[posMaior] < vet[pack[i].posMaior])
                posMaior=pack[i].posMaior;
            else if (vet[posMenor] > vet[pack[i].posMenor])
                posMenor=pack[i].posMenor;
        }

        printf("\nThread Main: Maior de Todos = %d e Menor de Todos = %d\n", vet[posMaior], vet[posMenor]);

        /* Resolve o problema sequencialmente e faz a validação validação */
        validaResultado(nElem, posMaior, posMenor);

        qtdeExe++;
    }
    printf("\nFinalizado as %d execuções do programa", &qtdeExe);    
    exit(0);
}

void validaResultado(int tamVetor, int paralMaior, int paralMenor){
    tipoPack pack[maxThreads];
    int i = 0;

    printf("\n=================================================");
    printf("\nOráculo Sequencial - Validação da solução paralela");
    pack[i].tid = i+1;
    pack[i].ini = i;
    pack[i].fim = tamVetor -1;
    pack[i].posMaior=i;
    pack[i].posMenor=i;

    buscaMaiorMenor((void*) &pack[i]);

    int posMaior=pack[i].posMaior;
    int posMenor=pack[i].posMenor;

    printf("\nSequencial => Maior: %d | Menor: %d", posMaior, posMenor);
    printf("\nParalelo   => Maior: %d | Menor: %d", paralMaior, paralMenor);

    if(posMenor == paralMenor && posMaior == paralMaior){
        printf("\nSucesso na validação dos resultados!");
        printf("\n=================================================");
    }else{
        printf("\nEncontrado erro na execução paralela");
        printf("\n==============Abortando programa!===============");
        exit(1);
    }
}

void *buscaMaiorMenor(void *ptr){    
    int i;

    tipoPack *pack;

    pack = (tipoPack *) ptr;

    printf("\nThread %d: vou procurar o Maior e o Menor de %d a %d\n", pack->tid, pack->ini, pack->fim);

    for (i=pack->ini+1; i<=(pack->fim); i++){
        if (vet[pack->posMaior]<vet[i])
            pack->posMaior=i;
        if (vet[pack->posMaior] < vet[i])
            pack->posMaior = i;
        if (vet[pack->posMenor] > vet[i])
            pack->posMenor = i;
    }
}

void geraVetor(int n){
    int i;
    printf("\nGeracao do Vetor:\n");

    for (i=0; i<n-1; i++){
        vet[i]=rand()%1000;
        printf("%d, ",vet[i]);
    }
    vet[i]=rand()%1000;
    printf("%d\n",vet[i]);
}

/*O else if faz com que a verificação do menor só aconteça quando o elemento atual NÃO for o maior. Se o elemento i for o maior do vetor, ele atualiza o maior — mas nunca checa se esse mesmo elemento poderia também redefinir o menor (o que não faria sentido), porém o problema real é o inverso: quando um elemento é menor que o atual menor, mas não é menor que o atual maior, o else if impede a atualização.*/