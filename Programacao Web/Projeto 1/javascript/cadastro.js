function cadastrar() {
  //Armazena em variáveis os dados preenchidos nos formulario
  let valorNome = document.getElementById("nome").value.trim();
  let valorEmail = document.getElementById("email").value.trim();
  let valorSenha = document.getElementById("senha").value.trim();
  let valorConfirmaSenha = document.getElementById("confirmar-senha").value.trim();
  let valorTelefone = document.getElementById("telefone").value.trim();
  let valorCidade = document.getElementById("cidade").value.trim();

  //Valida se todos os campos do formulário foi preenchido e armazena em um array na memória cache do navegador (localStorage)
  if (valorNome && valorEmail && valorSenha && valorConfirmaSenha && valorTelefone && valorCidade && valorSenha == valorConfirmaSenha) {
    if (valorSenha.length >= 8 && /[a-z]/.test(valorSenha) && /[0-9]/.test(valorSenha)) {
        let usuario = {
          usuario: valorNome,
          email: valorEmail,
          senha:  valorSenha,
          telefone: valorTelefone,
          cidade: valorCidade
    };
        
    //Salva os dados do novo usuário no localStorage no navegador
    let usuarios = JSON.parse(localStorage.getItem("usuarios")) || [];
    usuarios.push(usuario);
    localStorage.setItem("usuarios", JSON.stringify(usuarios));
    alert("Cadastro realizado com sucesso");
    window.location.href = "login.html"; //redireciona após o cadastro para o login
      
    } else {
        alert("A senha deve conter pelo menos 8 caracteres com letras e números");
    }
  } else if(valorConfirmaSenha != valorSenha){
      alert("As senhas preenchidas estão diferentes!")
  } else {
      alert("Preencha todos os campos para cadastrar!");

  }
}

/* Altera tema */
function MudaCorPagina() {
  let Seletor = document.getElementById("page-mode");
  let body = document.body;
  let headerCadastro = document.querySelector(".headerCadastro");
  let mainCadastro = document.querySelector(".mainCadastro");

  if (Seletor.value === "customizado") {
    aplicarModoNoturno(body, headerCadastro, mainCadastro);
  } else if (Seletor.value === "normal") {
    aplicarModoNormal(body, headerCadastro, mainCadastro);
  }
}

function aplicarModoNoturno(body, header, main) {
  body.classList.add('modo-noturno');
  body.classList.remove('modo-normal');
  header.classList.add('modo-noturno');
  header.classList.remove('modo-normal');
  main.classList.add('modo-noturno');
  main.classList.remove('modo-normal');
}

function aplicarModoNormal(body, header, main) {
  body.classList.add('modo-normal');
  body.classList.remove('modo-noturno');
  header.classList.add('modo-normal');
  header.classList.remove('modo-noturno');
  main.classList.add('modo-normal');
  main.classList.remove('modo-noturno');
}
