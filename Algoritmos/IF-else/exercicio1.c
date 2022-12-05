#include <stdio.h>

/*CÓDIGO DE COMPARAÇÃO DE SENHAS

-Definir variaveis;
-Ler a senha;
-Comparar com a senha registrada, neste caso 1234;
-Se senha igual a 1234, então "ACESSO LIBERADO";
-Se não: "Acesso negado";
*/

int main()
{

    int senhaRecebida, senhaVerdadeira;
    //variaveis de valor inteiro, que recebem a senha atual e a senha informado pelo usuário

    senhaVerdadeira = 1234;
    //atribuindo o valor fixo a variavel

    printf("Digite sua senha: ");
    scanf("%i", &senhaRecebida);
    //Pedindo o valor ao usuário e atribuindo a variavel

    if (senhaRecebida == senhaVerdadeira){
        printf("Acesso Liberado");
        //caso a senha recebida pelo usuário seja igual a seja fixa na variavel, terá acesso

    }else{
        printf("Acesso Negado");
        //caso os valores não sejam iguais, será acesso negado

    }


}
