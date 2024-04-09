/*      SISTEMA DE GERENCIAMENTO DE ESTOQUE 2.0

-Com interface gráfica e integração ao banco de dados "produto" em MySQL
Produção: 17/03/2024
Autores: 
Lucas Akira   RA: 129291
Olga Maria    RA: 130002*/

package sistemadeestoque;

public class SistemaDeEstoque {

    public static void main(String[] args) {
        
        //chama a interface gráfica
        Interface telaPrincipal = new Interface();
        telaPrincipal.setVisible(true);
    }
    
}
