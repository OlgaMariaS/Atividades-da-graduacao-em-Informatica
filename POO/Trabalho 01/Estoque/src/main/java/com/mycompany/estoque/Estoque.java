/*
SISTEMA DE GERENCIAMENTO DE ESTOQUE
Produção: 18/02/2024
Autores: 
Lucas Akira   RA: 
Olga Maria    RA: 130002
*/

package com.mycompany.estoque;

import java.util.ArrayList;
import java.util.Scanner;

public class Estoque {
    //Menu do estoque 
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int opcaoMenu;

        ArrayList<Produto> listaProdutos = new ArrayList<>();
        
        System.out.println("=======================Inicio do gerenciamento do estoque========================");
        do {
            System.out.println("Menu:");
            System.out.println("1 - Cadastrar");
            System.out.println("2 - Editar");
            System.out.println("3 - Excluir");
            System.out.println("4 - Pesquisar");
            System.out.println("5 - Catálogo");
            System.out.println("6 - Sair");
            System.out.print("\nOpção: ");
            opcaoMenu = scanner.nextInt();
            
            executarOpcao(opcaoMenu, listaProdutos);
        } while (opcaoMenu != 6);
    }
    
    //Função que executa a operação escolhida no menu (main)
    public static void executarOpcao(int opcaoMenu, ArrayList<Produto> listaProdutos) {
        Scanner scanner = new Scanner(System.in);
        switch (opcaoMenu) {
            case 1: cadastrar(listaProdutos);
                    break;
            case 2: editar(listaProdutos);
                    break;
            case 3: excluir(listaProdutos);
                    break;
            case 4: pesquisar(listaProdutos);
                    break;
            case 5: catalogo(listaProdutos);
                    break;
            case 6: System.out.println("=====================Fim do gerenciamento do estoque========================");
                    break;
            default: System.out.println("Opção inválida! \n");
        }
    }
    
    //Função que cadastrar o produto e insere na lista de produtos
    public static void cadastrar(ArrayList<Produto> listaProduto) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("-----------------Cadastro de Produto------------------");
        System.out.print("Nome: ");
        String nome = scanner.nextLine();
        System.out.print("Descrição: ");
        String descricao = scanner.nextLine();
        System.out.print("Preço: ");
        double preco = scanner.nextDouble();
        System.out.print("Estoque Atual: ");
        int quantidade = scanner.nextInt();

        Produto produto = new Produto(nome, descricao, preco, quantidade);

        listaProduto.add(produto);
        System.out.println("----------------------------------------");
    }
    
    //Função que permite a edição de um produto, já cadastrado
    public static void editar(ArrayList<Produto> listaProdutos) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("----------------Edição do Produto----------------");
        System.out.print("Código do produto a ser editado: ");
        int idProduto = scanner.nextInt();
        
        if( (idProduto <= 0) || (idProduto > listaProdutos.size()) ){
            System.out.println("Código não encontrado");
        }else{
            imprimirProdutoPeloCodigo(listaProdutos, idProduto);
            int opcaoMenu;
            
            do {
                System.out.println("Escolhe a informação pra editar:");
                System.out.println("1 - Nome");
                System.out.println("2 - Descrição");
                System.out.println("3 - Preço");
                System.out.println("4 - Quantidade");
                System.out.println("5 - Sair da edição");
                System.out.print("\nOpção: ");
                opcaoMenu = scanner.nextInt();
                
                auxiliarEdicao(listaProdutos, opcaoMenu, idProduto);
            } while (opcaoMenu != 5);
        }
        System.out.println("---------------------------------------------");
    }
    //Função que auxilia a função "editar", a partir da escolha do usuário, escreve a nova informação no objeto Produto
    public static void auxiliarEdicao(ArrayList<Produto> listaProdutos, int opcaoMenu, int idProduto){
        Scanner scanner = new Scanner(System.in);
        
        switch (opcaoMenu) {
            case 1: System.out.print("Novo nome: ");
                    String nome = scanner.nextLine();
                    listaProdutos.get(idProduto-1).setNome(nome);
                    break;
            case 2: System.out.print("Nova descrição: ");
                    String descricao = scanner.nextLine();
                    listaProdutos.get(idProduto-1).setDescricao(descricao);
                    break;
            case 3: System.out.print("Novo preço: ");
                    double preco = scanner.nextDouble();
                    listaProdutos.get(idProduto-1).setPreco(preco);
                    break;
            case 4: System.out.print("Nova quantidade: ");
                    int quantidade = scanner.nextInt();
                    listaProdutos.get(idProduto-1).setQuantidadeEstoque(quantidade);
                    break;
            case 5: System.out.println("Finalizado a edição");
                    imprimirProdutoPeloCodigo(listaProdutos, idProduto);
                    break;
            default: System.out.println("Opção inválida! \n");
        }            
    }
    //Função que auxilia a função "editar", mostrando os dados do produto escolhido
    public static void imprimirProdutoPeloCodigo(ArrayList<Produto> listaProdutos, int idProduto){
        System.out.println("-----Dados do produto-------");
        System.out.println(listaProdutos.get(idProduto-1).toString());
        System.out.println("----------------------------");
    }
    
    //Função que excluí produto da lista, a partir da escolha do código
    public static void excluir(ArrayList<Produto> listaProdutos){
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("-------------Exclusão de produto-------------");
        System.out.print("Código do produto a ser excluido: ");
        int idProduto = scanner.nextInt();
        
        if( (idProduto <= 0) || (idProduto > listaProdutos.size()) ){
            System.out.println("Código não encontrado");
        }else{
            listaProdutos.remove(listaProdutos.get(idProduto-1));
            System.out.println("Produto excluído!!");
        }
        System.out.println("---------------------------------------------");
    }
    
    //Função que mostra os dados de um produto na tela, a partir do nome.
    public static void pesquisar(ArrayList<Produto> listaProdutos){
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("-------------Pesquisa de produto-------------");
        System.out.print("Nome do produto a ser pesquisado: ");
        String NomeProduto = scanner.nextLine();
        
        for (Produto produto : listaProdutos) {
            if(produto.getNome().equals(NomeProduto)){
                System.out.println("-----Dados do produto-------");
                System.out.println(produto.toString());
                System.out.println("----------------------------");
            }else{
                System.out.println("Produto não encontrado");
            }
        }
        System.out.println("---------------------------------------------");
    }
    
    //Função que mostra na tela todos os produtos e suas informações
    public static void catalogo(ArrayList<Produto> listaProdutos) {
        int indice = 1;
        System.out.println("---------Catálogo de produtos--------------");
        for (Produto produto : listaProdutos) {
            System.out.println("Código: " + indice);
            System.out.println(produto.toString());
            System.out.println("------------");
            indice++;
        }
        System.out.println("--------------------------------------------");
    }

}
