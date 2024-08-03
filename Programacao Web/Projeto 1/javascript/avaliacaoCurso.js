/* Pega as informações no localStorage e insere no formulario pra avaliacao  */
document.addEventListener("DOMContentLoaded", function() {
    // Pega as informações do usuário logado do sessionStorage
    let usuarioLogado = JSON.parse(sessionStorage.getItem("usuarioLogado"));
    if (usuarioLogado) {
        // Preenche os campos do formulário com os dados do usuário logado
        document.getElementById("nome").value = usuarioLogado.usuario;
        document.getElementById("email").value = usuarioLogado.email;
    } 
});

//Recebe a avaliação e retorna aviso
function enviarComentario() {
    const comentario = document.getElementById("comentario-area").value;
    const nome = document.getElementById("nome").value;

    if(comentario === null){ // if não funciona
        alert("Para avaliar o curso, você deve digitar um comentário");
    }else{
        alert(nome + " obrigado pela sua avaliação");
    }
}

// REFERENCIA : https://www.w3schools.com/jsref/met_element_addeventlistener.asp

/* Exibe nome do usuário no cabeçalho */
document.addEventListener("DOMContentLoaded", function() {
    // Pega as informações do usuário logado do sessionStorage
    let usuarioLogado = JSON.parse(sessionStorage.getItem("usuarioLogado"));
    const userLoginInfo = document.getElementById("user-login-info");

    //Exibe o nome do usuário
    if (usuarioLogado) {
        const nomeUsuario = usuarioLogado.usuario; 
        userLoginInfo.textContent = `Bem-vindo, ${nomeUsuario}`;
    } else {
        userLoginInfo.textContent = "Usuário não autenticado";
    }
});

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
