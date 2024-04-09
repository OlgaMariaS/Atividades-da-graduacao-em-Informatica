/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.estoque;

/**
 *
 * @author Olga
 */
public class Produto {
    private String nome;
    private String descricao;
    private Double preco;
    private Integer quantidadeEstoque;


    public Produto() {
    }
    public Produto(String nome, String descricao, Double preco, Integer quantidadeEstoque) {
        this.nome = nome;
        this.descricao = descricao;
        this.preco = preco;
        this.quantidadeEstoque = quantidadeEstoque;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public Double getPreco() {
        return preco;
    }

    public void setPreco(Double preco) {
        this.preco = preco;
    }

    public Integer getQuantidadeEstoque() {
        return quantidadeEstoque;
    }

    public void setQuantidadeEstoque(Integer quantidadeEstoque) {
        this.quantidadeEstoque = quantidadeEstoque;
    }

    @Override
    public String toString() {
        return    "Nome: " + nome + "\n" 
                + "Descricao: " + descricao + "\n" 
                + "Preco: " + String.format("%.2f", preco) 
                + "\n" + "Estoque atual: " + quantidadeEstoque;
    }
}
