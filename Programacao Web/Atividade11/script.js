/*Considere um código Javascript para validar os campos. No caso do campo login,
considere que o mesmo não pode estar nulo. No caso do campo senha, verifique se a
senha digitada é igual a PSW2024;
3) Caso os campos não estejam de acordo com as restrições estabelecidas, apresente uma
mensagem de alerta, informando a ocorrência de um problema;
4) Caso os campos estejam de acordo com as restrições estabelecidas, apresente uma
mensagem de alerta de login realizado com sucesso;
5) Crie uma outra versão da página, considerando Constraint Validation. */

function validarCampos() {
  const login = document.getElementById("login").value;
  const senha = document.getElementById("password").value;
   
  if (login == "" || senha == "") {
      alert("Digite usuário e senha");
  }else{
    if(senha == "PSW2024"){
      alert("Login realizado com sucesso");
    }else{
      alert("Senha inválidos");
    }
  }

}