function autenticar() {
    //Armazena em variáveis os dados preenchidos nos formulario removendo espaços em branco do inicio e fim
    const valorUsuario = document.getElementById("login").value.trim();
    const valorSenha = document.getElementById("senha").value.trim();

    if (valorUsuario && valorSenha) {
        let usuarios = JSON.parse(localStorage.getItem("usuarios"));

        if(usuarios === null) {
            alert("Usuário não cadastrado");
            return;
        } else {
            // Percorre o array de usuários, verificando usuario e senhas correspondem a um cadastrado
            for (let i = 0; i < usuarios.length; i++) {
                if (usuarios[i].usuario === valorUsuario && usuarios[i].senha === valorSenha) {
                    alert("Bem vindo(a), " + usuarios[i].usuario);
                    // Armazena as informações do usuário logado no sessionStorage
                    sessionStorage.setItem("usuarioLogado", JSON.stringify(usuarios[i]));
                    //redireciona para a página principal após login
                    window.location.href = "/usuarioLogado/usuarioLogado.html";
                    break;
                } 
            }
        }       
    }    
}

/* Altera tema da pagina */
function MudarCorPagina() {
    const Seletor = document.getElementById("page-mode");
    const body = document.body;
    const main = document.querySelector("main");
    const headerPrincipal = document.querySelector(".headerPrincipal");

    if (Seletor.value === "customizado") {
        aplicarModoNoturno(body, headerPrincipal, main);
    } else if (Seletor.value === "normal") {
        aplicarModoNormal(body, headerPrincipal, main);
    }
}

function aplicarModoNoturno(body, header, main) {
    header.classList.add('modo-noturno');
    header.classList.remove('modo-normal');
    body.classList.add('modo-noturno');
    body.classList.remove('modo-normal');
    main.classList.add('modo-noturno');
    main.classList.remove('modo-normal');
}

function aplicarModoNormal(body, header, main) {
    header.classList.add('modo-normal');
    header.classList.remove('modo-noturno');
    body.classList.add('modo-normal');
    body.classList.remove('modo-noturno');
    main.classList.add('modo-normal');
    main.classList.remove('modo-noturno');
}


