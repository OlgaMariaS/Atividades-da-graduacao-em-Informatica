#include<stdio.h>
/*
Mostre atraves de um teste de mesa os resultados da seguinte função:
int func(int n){
if (n == 0)
return (1);
if (n == 1)
return (1);
else{ return func(n-1)+ 2*func(n-2); }
considere as entradas:
(a) func(0)
(b) func(1)
(c) func(5)
PLANEJAMENTO
-Criar a main, e pedir ao usuário informação;
-chamar a função func, e passar numero como parametro;
-fazer os teste com os valores 0,1, 5 e deixar escrito os resultados recebidos;
-printar o resultado ao usuário pela main;

RESULTADOS DOS TESTE:
-ao informar 0 e 1, o retorno da 1;
-informando 5 o retorno da 21;
*/
int func(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 1;
    else
        return func(n-1) + 2*func(n-2);
}

main(){
    int numero, retorno;

    printf("Informe um numero: ");
    scanf("%i", &numero);

    retorno = func(numero);

    printf("O resultado e: %i", retorno);
}