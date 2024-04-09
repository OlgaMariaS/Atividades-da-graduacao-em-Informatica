package model.dao;

import connection.ConnectionFactory;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import model.bean.Produto;

//ProdutoDAO é responsável pela manipulação no banco de dados, fazendo um CRUD (criando, lendo, atualizado e deletando).

public class ProdutoDAO {
    
    //Insere um cadastro de produto no banco de dados
    public void create(Produto p) {
        
        Connection con = ConnectionFactory.getConnection();
        
        PreparedStatement stmt = null;

        try {
            stmt = con.prepareStatement("INSERT INTO produto (nome, descricao, quantidade, preco) VALUES(?,?,?,?)");
            
            stmt.setString(1, p.getNome());
            stmt.setString(2, p.getDescricao());
            stmt.setInt(3, p.getQuantidade());
            stmt.setDouble(4, p.getPreco());

            stmt.executeUpdate();
            JOptionPane.showMessageDialog(null, "Salvo com sucesso!");
            
        } catch (SQLException ex) {
            System.out.println(ex);
        } finally {
            ConnectionFactory.closeConnection(con, stmt);
        }

    }

    //Faz a consulta de todos os produtos do banco de dados e retorna eles armazenados em um lista
    public List<Produto> read() {

        Connection con = ConnectionFactory.getConnection();
        
        PreparedStatement stmt = null;
        ResultSet rs = null;

        List<Produto> produtos = new ArrayList<>();

        try {
            stmt = con.prepareStatement("SELECT * FROM produto");
            rs = stmt.executeQuery();

            while (rs.next()) {

                Produto produto = new Produto();

                produto.setId(rs.getInt("id"));
                produto.setNome(rs.getString("nome"));
                produto.setDescricao(rs.getString("descricao"));
                produto.setQuantidade(rs.getInt("quantidade"));
                produto.setPreco(rs.getDouble("preco"));
                produtos.add(produto);
            }

        } catch (SQLException ex) {
            Logger.getLogger(ProdutoDAO.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            ConnectionFactory.closeConnection(con, stmt, rs);
        }
        return produtos;
    }
        
    //Atualiza os dados uma instancia no banco, a partir do ID escolhido, seguindo os novos dados do parametro Produto p
    public void update(Produto p) {

        Connection con = ConnectionFactory.getConnection();
        
        PreparedStatement stmt = null;

        try {
            stmt = con.prepareStatement("UPDATE produto SET nome = ?, descricao = ?, quantidade = ?, preco = ? WHERE id = ?");
            
            stmt.setString(1, p.getNome());
            stmt.setString(2, p.getDescricao());
            stmt.setInt(3, p.getQuantidade());
            stmt.setDouble(4, p.getPreco());
            stmt.setInt(5, p.getId());

            stmt.executeUpdate();

            JOptionPane.showMessageDialog(null, "Alterado com sucesso!");
        } catch (SQLException ex) {
            JOptionPane.showMessageDialog(null, "Erro ao alterar: " + ex);
        } finally {
            ConnectionFactory.closeConnection(con, stmt);
        }

    }
    
    //A partir do id (codigo do produto) remove a instancia do banco de dados
    public void delete(Produto p) {
        Connection con = ConnectionFactory.getConnection();
        
        PreparedStatement stmt = null;

        try {
            stmt = con.prepareStatement("DELETE FROM produto WHERE id = ?");
            stmt.setInt(1, p.getId());

            stmt.executeUpdate();

            JOptionPane.showMessageDialog(null, "Excluido com sucesso!");
        } catch (SQLException ex) {
            JOptionPane.showMessageDialog(null, "Erro ao excluir: " + ex);
        } finally {
            ConnectionFactory.closeConnection(con, stmt);
        }

    }
    
    //Recebe um nome de produto e faz a consulta no banco de dados, e retorna uma lista com todos os produtos encontrados pelo parametro nome
    public List<Produto> readPorNome(String nome) {

        Connection con = ConnectionFactory.getConnection();
        
        PreparedStatement stmt = null;
        ResultSet rs = null;

        List<Produto> produtos = new ArrayList<>();

        try {
            stmt = con.prepareStatement("SELECT * FROM produto WHERE nome LIKE ?");
            stmt.setString(1, "%" + nome + "%");
            
            rs = stmt.executeQuery();

            while (rs.next()) {

                Produto produto = new Produto();

                produto.setId(rs.getInt("id"));
                produto.setNome(rs.getString("nome"));
                produto.setDescricao(rs.getString("descricao"));
                produto.setQuantidade(rs.getInt("quantidade"));
                produto.setPreco(rs.getDouble("preco"));
                produtos.add(produto);
            }

        } catch (SQLException ex) {
            Logger.getLogger(ProdutoDAO.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            ConnectionFactory.closeConnection(con, stmt, rs);
        }
        return produtos;
    }
}