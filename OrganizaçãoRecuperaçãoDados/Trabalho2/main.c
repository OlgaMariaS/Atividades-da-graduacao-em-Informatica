#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Comandos 
int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-c") == 0) {

    //chama da funcao que cria o arquivo de indices, caso retorne 1, significa que foi criado com sucesso
       if( arv() == 1){
            printf("Criacao do arquivo de índices 'btree.dat' criada com sucesso!");
       }else{
            printf("Falha na criacao do arquivo de indices");
       }

    } else if (argc == 2 && strcmp(argv[1], "-e") == 0) {
        
        //deve verificar se dados existe e btree existe, se não apresenta erro
        //se sim, chama a funções que executa o arquivo do operações 
        executa_operacoes(argv[2]);

    } else if (argc == 1 && strcmp(argv[1], "-p") == 0) {
        //chama a função que imprime a arvore
        imprime_arvore();
        
    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s -e nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}
