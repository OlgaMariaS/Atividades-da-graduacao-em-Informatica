package sistemadeestoque;

import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;
import model.bean.Produto;
import model.dao.ProdutoDAO;

public class Interface extends javax.swing.JFrame {

    public Interface() {
        initComponents();    
        //Chama os produtos do banco para a interface gráfica
        catalogo();
    }
    
    //metodo auxiliar que reseta os campos do cadastro após serem utilizados
    public void resetaCadastro(){
        campoNome.setText("");
        campoDescricao.setText("");
        campoQuantidade.setText("");
        campoPreco.setText("");
    }
        
    //Recebe as instancias do banco de dados, pelo metodo read() do arquivo ProdutoDAO.java, 
    //e insere elas na JTable 'tabelaProdutos' para visualização do usuário
    public void catalogo(){
        DefaultTableModel modeloTabela = (DefaultTableModel) tabelaProdutos.getModel();
        modeloTabela.setNumRows(0);
        
        ProdutoDAO produtoDao = new ProdutoDAO();
        
        for(Produto p: produtoDao.read()){
            modeloTabela.addRow(new Object[]{
                p.getId(),
                p.getNome(),
                p.getDescricao(),
                p.getQuantidade(),
                p.getPreco()
            });
        }
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        Cadastro = new javax.swing.JPanel();
        nome = new javax.swing.JLabel();
        campoNome = new javax.swing.JTextField();
        descricao = new javax.swing.JLabel();
        campoDescricao = new javax.swing.JTextField();
        quantidade = new javax.swing.JLabel();
        campoQuantidade = new javax.swing.JTextField();
        campoPreco = new javax.swing.JTextField();
        preco = new javax.swing.JLabel();
        incluir = new javax.swing.JButton();
        alterar = new javax.swing.JButton();
        excluir = new javax.swing.JButton();
        pesquisar = new javax.swing.JButton();
        refresh = new javax.swing.JButton();
        titulo = new javax.swing.JLabel();
        panelTabela = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        tabelaProdutos = new javax.swing.JTable();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sistema de gerenciamento de estoque");

        Cadastro.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Cadastro", javax.swing.border.TitledBorder.DEFAULT_JUSTIFICATION, javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Segoe UI", 0, 12), new java.awt.Color(0, 0, 0))); // NOI18N
        Cadastro.setForeground(new java.awt.Color(204, 204, 204));

        nome.setText("Nome:");

        descricao.setText("Descrição:");
        descricao.setToolTipText("");

        quantidade.setText("Quantidade:");

        preco.setText("Preço:");

        incluir.setFont(new java.awt.Font("Segoe UI", 1, 12)); // NOI18N
        incluir.setForeground(new java.awt.Color(0, 153, 0));
        incluir.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/add.png"))); // NOI18N
        incluir.setText("Incluir");
        incluir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                incluirActionPerformed(evt);
            }
        });

        alterar.setFont(new java.awt.Font("Segoe UI", 1, 12)); // NOI18N
        alterar.setForeground(new java.awt.Color(0, 102, 255));
        alterar.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/book_edit.png"))); // NOI18N
        alterar.setText("Alterar");
        alterar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                alterarActionPerformed(evt);
            }
        });

        excluir.setFont(new java.awt.Font("Segoe UI", 1, 12)); // NOI18N
        excluir.setForeground(new java.awt.Color(204, 0, 0));
        excluir.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/cancel.png"))); // NOI18N
        excluir.setText("Excluir");
        excluir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                excluirActionPerformed(evt);
            }
        });

        pesquisar.setFont(new java.awt.Font("Segoe UI", 1, 12)); // NOI18N
        pesquisar.setForeground(new java.awt.Color(204, 153, 0));
        pesquisar.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/zoom.png"))); // NOI18N
        pesquisar.setText("Pesquisar");
        pesquisar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                pesquisarActionPerformed(evt);
            }
        });

        refresh.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/arrow_refresh.png"))); // NOI18N
        refresh.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                refreshActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout CadastroLayout = new javax.swing.GroupLayout(Cadastro);
        Cadastro.setLayout(CadastroLayout);
        CadastroLayout.setHorizontalGroup(
            CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(CadastroLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(descricao)
                    .addComponent(nome)
                    .addComponent(quantidade))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(CadastroLayout.createSequentialGroup()
                        .addComponent(campoQuantidade, javax.swing.GroupLayout.PREFERRED_SIZE, 112, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(23, 23, 23)
                        .addComponent(preco)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(campoPreco, javax.swing.GroupLayout.PREFERRED_SIZE, 112, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(31, 31, 31)
                        .addComponent(incluir)
                        .addGap(18, 18, 18)
                        .addComponent(alterar)
                        .addGap(18, 18, 18)
                        .addComponent(excluir))
                    .addComponent(campoDescricao)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, CadastroLayout.createSequentialGroup()
                        .addComponent(campoNome)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(pesquisar)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(refresh)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        CadastroLayout.setVerticalGroup(
            CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(CadastroLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(nome)
                        .addComponent(campoNome, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(pesquisar))
                    .addComponent(refresh))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(descricao)
                    .addComponent(campoDescricao, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(12, 12, 12)
                .addGroup(CadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(quantidade)
                    .addComponent(campoQuantidade, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(preco)
                    .addComponent(campoPreco, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(incluir)
                    .addComponent(alterar)
                    .addComponent(excluir))
                .addContainerGap(18, Short.MAX_VALUE))
        );

        titulo.setFont(new java.awt.Font("Nirmala UI", 1, 14)); // NOI18N
        titulo.setForeground(new java.awt.Color(0, 51, 51));
        titulo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagens/book_open.png"))); // NOI18N
        titulo.setText("SISTEMA DE GERENCIAMENTO DE ESTOQUE");

        panelTabela.setBorder(javax.swing.BorderFactory.createTitledBorder("Catálogo"));

        tabelaProdutos.setFont(new java.awt.Font("Arial", 1, 12)); // NOI18N
        tabelaProdutos.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "Código", "Nome", "Descrição", "Quantidade", "Preço"
            }
        ) {
            boolean[] canEdit = new boolean [] {
                false, false, false, false, false
            };

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        tabelaProdutos.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                tabelaProdutosMouseClicked(evt);
            }
        });
        tabelaProdutos.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                tabelaProdutosKeyReleased(evt);
            }
        });
        jScrollPane1.setViewportView(tabelaProdutos);

        javax.swing.GroupLayout panelTabelaLayout = new javax.swing.GroupLayout(panelTabela);
        panelTabela.setLayout(panelTabelaLayout);
        panelTabelaLayout.setHorizontalGroup(
            panelTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panelTabelaLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1)
                .addContainerGap())
        );
        panelTabelaLayout.setVerticalGroup(
            panelTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelTabelaLayout.createSequentialGroup()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 264, Short.MAX_VALUE)
                .addContainerGap())
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(226, 226, 226)
                .addComponent(titulo)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(Cadastro, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(panelTabela, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap(7, Short.MAX_VALUE)
                .addComponent(titulo)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(Cadastro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(panelTabela, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents
    
    //Armazena os dados preenchidos em cadastro em um objeto Produto, e o objeto é passado ao metodo create para que seja inserido no banco de dados
    private void incluirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_incluirActionPerformed
        
        if( (!"".equals(campoNome.getText())) && (!"".equals(campoDescricao.getText())) && (!"".equals(campoQuantidade.getText())) && (!"".equals(campoPreco.getText())) ){
            Produto produto = new Produto();
            ProdutoDAO dao = new ProdutoDAO();

            produto.setNome(campoNome.getText());
            produto.setDescricao(campoDescricao.getText());
            produto.setQuantidade(Integer.parseInt(campoQuantidade.getText()));
            produto.setPreco(Double.parseDouble(campoPreco.getText()));

            dao.create(produto);

            resetaCadastro();
            catalogo(); 
        }else{
            JOptionPane.showMessageDialog(null, "Preencha todos os campos do cadastro para incluir");
        }
    }//GEN-LAST:event_incluirActionPerformed
    
    //Clicando no botão de "editar", é verificado se um produto foi selecionado, se sim, será enviado os campos
    //de cadastro ao metodo update para que atualiza o produto no banco de dados, a partir do ID (codigo) da linha selecionada
    private void alterarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_alterarActionPerformed
       
       if(tabelaProdutos.getSelectedRow() != -1){
            Produto produto = new Produto();
            ProdutoDAO dao = new ProdutoDAO();

            produto.setNome(campoNome.getText());
            produto.setDescricao(campoDescricao.getText());
            produto.setQuantidade(Integer.parseInt(campoQuantidade.getText()));
            produto.setPreco(Double.parseDouble(campoPreco.getText()));
            produto.setId((int)tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 0));
            
            dao.update(produto);
            
            resetaCadastro();
            catalogo();
       }else {
            JOptionPane.showMessageDialog(null, "Selecione um produto para editar");
        }
    }//GEN-LAST:event_alterarActionPerformed

    //Clicando no botão de "excluir", é verificado se um produto foi selecionado, se sim, 
    //o codigo(ID) será enviado ao metodo delete, que removerá a instancia do banco de dados
    private void excluirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_excluirActionPerformed
        
        if(tabelaProdutos.getSelectedRow() != -1){
            Produto produto = new Produto();
            ProdutoDAO dao = new ProdutoDAO();

            produto.setId((int)tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 0));
            dao.delete(produto);
            
            resetaCadastro();
            catalogo();
        }else {
            JOptionPane.showMessageDialog(null, "Selecione um produto para excluir");
        }
    }//GEN-LAST:event_excluirActionPerformed
    
    //Pega os dados da linha da tabela selecionado pelo MOUSE e coloca na tela de cadastro para que haja edição
    private void tabelaProdutosMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_tabelaProdutosMouseClicked
                
        if(tabelaProdutos.getSelectedRow() != -1){
            campoNome.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 1).toString());
            campoDescricao.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 2).toString());
            campoQuantidade.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 3).toString());
            campoPreco.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 4).toString());
        }
    }//GEN-LAST:event_tabelaProdutosMouseClicked
    
    //Pega os dados da linha da tabela selecionado pelo TECLADO e coloca na tela de cadastro para que haja edição
    private void tabelaProdutosKeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_tabelaProdutosKeyReleased
        
        if(tabelaProdutos.getSelectedRow() != -1){
            campoNome.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 1).toString());
            campoDescricao.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 2).toString());
            campoQuantidade.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 3).toString());
            campoPreco.setText(tabelaProdutos.getValueAt(tabelaProdutos.getSelectedRow(), 4).toString());
        }
    }//GEN-LAST:event_tabelaProdutosKeyReleased
    
    //Verifica se o campoNome foi preenchido, se sim, chama o metodo readPorNome que faz consulta 
    //pelo nome no banco de dados, e com o retorno é mostrado os produtos com o devido nome na tabela.
    private void pesquisarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_pesquisarActionPerformed
        if(!"".equals(campoNome.getText())){
            DefaultTableModel modeloTabela = (DefaultTableModel) tabelaProdutos.getModel();
            modeloTabela.setNumRows(0);

            ProdutoDAO produtoDao = new ProdutoDAO();

            for(Produto p: produtoDao.readPorNome(campoNome.getText())){
                modeloTabela.addRow(new Object[]{
                    p.getId(),
                    p.getNome(),
                    p.getDescricao(),
                    p.getQuantidade(),
                    p.getPreco()
                });
            } 
        }else{
            catalogo();
            JOptionPane.showMessageDialog(null, "Informe o nome do produto para pesquisar");
        }
    }//GEN-LAST:event_pesquisarActionPerformed
    
    //ao clicar no botão de refresh ele limpa os campos de cadastro e volta a tabela de produtos a tela inicial dela
    private void refreshActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_refreshActionPerformed
        resetaCadastro();
        catalogo();
    }//GEN-LAST:event_refreshActionPerformed

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Windows".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable(){
            public void run() {
                new Interface().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel Cadastro;
    private javax.swing.JButton alterar;
    private javax.swing.JTextField campoDescricao;
    private javax.swing.JTextField campoNome;
    private javax.swing.JTextField campoPreco;
    private javax.swing.JTextField campoQuantidade;
    private javax.swing.JLabel descricao;
    private javax.swing.JButton excluir;
    private javax.swing.JButton incluir;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel nome;
    private javax.swing.JPanel panelTabela;
    private javax.swing.JButton pesquisar;
    private javax.swing.JLabel preco;
    private javax.swing.JLabel quantidade;
    private javax.swing.JButton refresh;
    private javax.swing.JTable tabelaProdutos;
    private javax.swing.JLabel titulo;
    // End of variables declaration//GEN-END:variables
}
