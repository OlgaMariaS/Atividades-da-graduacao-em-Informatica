/* Pega as informações no localStorage e insere no formulario pra edição  */
document.addEventListener("DOMContentLoaded", function() {
    // Pega as informações do usuário logado do sessionStorage
    let usuarioLogado = JSON.parse(sessionStorage.getItem("usuarioLogado"));

    if (usuarioLogado) {
        // Preenche os campos do formulário com os dados do usuário logado
        document.getElementById("nome").value = usuarioLogado.usuario;
        document.getElementById("email").value = usuarioLogado.email;
        document.getElementById("senha").value = usuarioLogado.senha;
        document.getElementById("telefone").value = usuarioLogado.telefone;
        document.getElementById("cidade").value = usuarioLogado.cidade;
    } else {
        alert("Nenhum usuário logado.");
    }
});

//Atualiza os novos dados do usuário
function editar() {
    // Pega os novos valores do formulário removendo espaços em branco do inicio e fim
    let usuario = document.getElementById("nome").value.trim();
    let email = document.getElementById("email").value.trim();
    let senha = document.getElementById("senha").value.trim();
    let telefone = document.getElementById("telefone").value.trim();
    let cidade = document.getElementById("cidade").value.trim();

    //Valida se todos os campos do formulário foi preenchido
    if (usuario && email && senha && telefone && cidade) {
        if (senha.length >= 8 && /[a-z]/.test(senha) && /[0-9]/.test(senha)) {
            // Cria um objeto usuario com os novos dados
            let usuarioLogado = {
                usuario: usuario,
                email: email,
                senha: senha,
                telefone: telefone,
                cidade: cidade
            };
            // Atualiza no sessionStorage
            sessionStorage.setItem("usuarioLogado", JSON.stringify(usuarioLogado));

            // Atualiza no localStorage (no array de usuários)
            let usuarios = JSON.parse(localStorage.getItem("usuarios"));
            for (let i = 0; i < usuarios.length; i++) {
                if (usuarios[i].usuario === usuarioLogado.usuario) {
                    usuarios[i] = usuarioLogado;
                    break;
                }
            }
            localStorage.setItem("usuarios", JSON.stringify(usuarios));

            alert("Informações atualizadas com sucesso.");
        } else {
              alert("A senha deve conter pelo menos 8 caracteres com letras e números");
        }
    } else {
        alert("Preencha todos os campos para atualizar!");
    }
}
    
/* Exibe nome do usuário no cabeçalho */
document.addEventListener("DOMContentLoaded", function() {
    // Pega as informações do usuário logado do sessionStorage
    let usuarioLogado = JSON.parse(sessionStorage.getItem("usuarioLogado"));
    const userLoginInfo = document.getElementById("user-login-info");

    //Se existe usuario logado, exibe o nome do usuário
    if (usuarioLogado) {
        const nomeUsuario = usuarioLogado.usuario; // Pega o nome do usuário logado
        userLoginInfo.textContent = `Bem-vindo, ${nomeUsuario}`;
    } else {
        userLoginInfo.textContent = "Usuário não autenticado";
    }
});

/* Alteração de tema  */
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
