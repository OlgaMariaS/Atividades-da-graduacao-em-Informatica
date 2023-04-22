#include <stdio.h>
#include <stdlib.h>
//GabrielSaraiva_RA129145_OlgaMaria_RA130002

//Primeiro de tudo, criar as estruturas (agregrados heterogêneos) que serão necessários para a aplicação

typedef struct tipo_itens{
    char nome[50];
    int prioridade;
    int equipe;
}Dados;

// Para o estado de preparação utilizaremos uma lista dupla circular com sentinela


struct tipo_celula{
    Dados DadosJogador;
    struct tipo_celula *prox;
    struct tipo_celula *ant;
};

struct tipo_lista{
    struct tipo_celula *sentinela;

};

//Funções Auxiliares
void inicializa_lista (struct tipo_lista *list){
    list->sentinela=(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    list->sentinela->prox=list->sentinela;
    list->sentinela->ant=list->sentinela;
}

int vazia_lista(struct tipo_lista *list){
    return list->sentinela->prox == list->sentinela;
}

//Função que printa os jogadores inseridos (Opção 2 no menu)
void lista_jogadores(struct tipo_lista *list){
    struct tipo_celula *novo = list->sentinela->prox;
    if(vazia_lista(list)){
        printf("Não há jogadores para remover!");
    }else{
        printf("NOME \t\t PRIORIDADE \t\t EQUIPE\n");
        while(novo != list->sentinela){
            printf("%s\t\t\t %d \t\t\t %d\n", novo->DadosJogador.nome, novo->DadosJogador.prioridade,novo->DadosJogador.equipe);
            novo = novo->prox;
        }
        printf("\n");
    }
}

//Função que Remove Jogador (Opção 3 no menu)
int remove_jogador(struct tipo_lista *list, Dados *x){
    int ordem_jogadores = 1; //primeira posição
    struct tipo_celula *i;
    int remove_jogador = 0;
    struct tipo_celula *del;
    if(vazia_lista(list)){
        printf("Sem jogadores para remover!");
    }else{
        for(i = list->sentinela->prox; i!=list->sentinela; i=i->prox)
        {
            printf("%d\t %s\n",ordem_jogadores, i->DadosJogador.nome);
            ordem_jogadores++;
        }
        printf("\nQual jogador deseja remover? ");
        scanf("%d",&remove_jogador);

        ordem_jogadores = 1; //reinicializa a ordem para percorrer a lista novamente
        for(del = list->sentinela->prox; del!=list->sentinela; del=del->prox)
        {
            if(remove_jogador == ordem_jogadores)
            {
                del->ant->prox = del->prox;
                del->prox->ant = del->ant;
                //salvo os dados do jogador para caso seja preciso utilizá-los futuramente
                *x = del->DadosJogador;
                free(del);
                return 1; //indica que a remoção foi bem sucedida
            }
            ordem_jogadores++; //incrementa a ordem para continuar percorrendo a lista
        }
    }
    // se chegou aqui, não encontrou nenhum jogador com a ordem informada
    return 0; //indica que a remoção falhou
}


//Opção 5
void encerra_partida(struct tipo_lista *l){
    free(l);
    printf("Programa Encerrado!");
    exit(0);
}

//Opção 4
/* Para a opção 4 utilizaremos algumas estruturas auxiliares, uma lista de prioridade para representar uma fila de prioridade */

//Função que receberá os jogadores recentemente inseridos em uma lista, na OPCAO 1 do menu, e os ordenará em uma fila de prioridade
void ordena_em_fila_de_prioridade(struct tipo_lista *list, Dados dado){ ///FALTA AJUSTAR A ESSA FUNÇÃO!!!!
    struct tipo_celula *novo, *p, *antecessor;
    novo = (struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->DadosJogador = dado;
    inicializa_lista(list);

    if (list->sentinela->prox == list->sentinela && list->sentinela->ant == list->sentinela){ // caso a lista esteja vazia, o novo nó será o primeiro
        novo->prox = list->sentinela;
        novo->ant = list->sentinela;
        list->sentinela->prox = novo;
        list->sentinela->ant = novo;
    } else {
        antecessor =(struct tipo_celula *)malloc(sizeof(struct tipo_celula));
        antecessor->prox = NULL;
        antecessor->ant = NULL;
        p = list->sentinela->prox;

        while(p->prox!= list->sentinela && novo->DadosJogador.prioridade > p->DadosJogador.prioridade){
            novo->prox = p;
            novo->ant = p->ant;
            p->ant = novo;
            antecessor = p;
            p = p->prox;
            if(antecessor->DadosJogador.prioridade < p->DadosJogador.prioridade){
                p->ant = antecessor ->ant;
                antecessor->prox = p->prox;
                p->prox = antecessor;
                antecessor -> ant = p;
                p->ant->prox = p;
                antecessor->prox->ant = antecessor;
            }
        }
    }
}

void imprime_prioridade(struct tipo_lista *l){
    //struct tipo_celula *jogador_ativo; //retorna um ponteiro para o jogador que está na sua vez de jogar
    struct tipo_celula *atual = l->sentinela->prox;
    struct tipo_celula *proximoDoAtual= atual->prox;

    while(atual->prox != l->sentinela){
        if (atual->DadosJogador.prioridade > proximoDoAtual->DadosJogador.prioridade) {
            printf("%s - equipe %d\n\n", atual->DadosJogador.nome, atual->DadosJogador.equipe);
            atual = atual->prox;
            proximoDoAtual = proximoDoAtual->prox;
        }
    }
    if(vazia_lista(l)){
        printf("Nao ha jogadores na partida!");
    }else if(atual->prox == l->sentinela){
            printf("Vez do jogador: %s - equipe %d\n",atual->DadosJogador.nome, atual->DadosJogador.equipe);
    }else if(atual->prox == l->sentinela && atual->ant == l->sentinela){
        printf("\n\n===== %s venceu! =====", atual->DadosJogador.nome);
    }
}

//Função que irá inserir um novo jogador a partida (Opção 1 no menu)
int insere_jogador(struct tipo_lista *list, Dados dado){
    struct tipo_celula *novo;
    novo = (struct tipo_celula *)malloc(sizeof(struct tipo_celula));
    novo->DadosJogador = dado;
    novo->prox=list->sentinela;
    novo->ant=list->sentinela->ant;
    list->sentinela->ant->prox=novo;
    list->sentinela->ant=novo;
    return 1;
}

//Função que encerra vez do jogador ativo:
void remove_jogador_ativo(struct tipo_lista *l, Dados *x){
    if(vazia_lista(l)){
        printf("Nao ha mais jogadores para jogar! \n");
    }else
    {
        struct tipo_celula *del;
        del=l->sentinela->ant;
        del->ant->prox = del->prox;
        del->prox->ant = del->ant;
        *x = del->DadosJogador;
        free(del);
        printf("Vez do jogador ativo encerrada!\n");   
    }
}



 //Função auxiliar que executará o menu do estado de jogo

 void estado_de_jogo(struct tipo_lista *l){
    int opcao = 0;
    Dados jogador, *x;   
    x = (Dados *)malloc(sizeof(Dados));                 
    do{
        printf("\nEstado de Jogo: \n");
        printf("1 - Encerrar vez do jogador ativo\n");
        printf("2 - Remover jogador\n");
        printf("3 - Encerrar jogo\n");
        printf("4 - Inserir jogador\n");
        printf("Opcao: ");
        scanf("%d",&opcao);
        switch (opcao)
        {
            case 1:
                remove_jogador_ativo(l,x);
                printf("\nJogadores em ordem de prioridade: \n");
                imprime_prioridade(l);
                break;

            case 2:
                remove_jogador(l,x); //dando erro
                imprime_prioridade(l);
                break;
            
            case 3:
                free(l);
                printf("Jogo encerrado!");
                exit(1);
                break;
            
            case 4:
                    printf("Digite os dados do jogador\n");
                    printf("NOME: ");
                    scanf("%s",jogador.nome);
                    printf("PRIORIDADE: ");
                    scanf("%d",&jogador.prioridade);
                    printf("EQUIPE: ");
                    scanf("%d",&jogador.equipe);
                    imprime_prioridade(l);
                    break;

            default:
                break;
            }
    }while(opcao <= 4);
 }

int main(){
    struct tipo_lista *l;
    l =(struct tipo_lista *)malloc(sizeof(struct tipo_lista));
    inicializa_lista(l);
    Dados jogador;
    int opcao_preparacao = 0;
    while(opcao_preparacao <= 5){
        printf("\nPreparacao: \n");
        printf("1 - Inserir jogador\n");
        printf("2 - Listar jogadores\n");
        printf("3 - Remover jogador\n");
        printf("4 - Iniciar partida\n");
        printf("5 - Encerrar programa\n");
        printf("Opcao: ");
        scanf("%d", &opcao_preparacao);

        switch(opcao_preparacao){
            case 1:
                printf("Digite os dados do jogador\n");
                printf("NOME: ");
                scanf("%s",jogador.nome);
                printf("PRIORIDADE: ");
                scanf("%d",&jogador.prioridade);
                printf("EQUIPE: ");
                scanf("%d",&jogador.equipe);
                insere_jogador(l,jogador);
                break;

            case 2:
                lista_jogadores(l);
                break;

            case 3:
                remove_jogador(l, &jogador);
                break;

            case 4:
                imprime_prioridade(l);
                estado_de_jogo(l);
                break;

            case 5:
                encerra_partida(l);
                break;
            }
    }

}
