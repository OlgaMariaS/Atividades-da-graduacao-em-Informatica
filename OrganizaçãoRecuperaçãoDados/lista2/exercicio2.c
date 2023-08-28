#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Foi visto em aula um programa C chamado list (slide 22 do arquivo “Operações em Arquivos.pdf”).
Modifique o programa list para que ele leia os dados a partir da entrada padrão (stdin), em vez de um
arquivo, e escreva os dados lidos em um arquivo, em vez da saída padrão (stdout).*/
int input(char str[], int size) {
    int i = 0;
    char c = getchar();

    while (c != '\n') {
        if (i < size-1) {
        str[i] = c;
        i++;
    }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

int main( ){
    char l;
    FILE *fd;
    char filename[20];

    printf("De nome do arquivo: ");
    input(filename, 20);

    fd = fopen(filename, "r+");

    printf("Informe os dados do seu arquivo: \n");
    input(l,50);
    fputs(l,filename);

    fclose(fd);
}