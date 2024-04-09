CREATE DATABASE produto;
create table produto(
    id integer primary key auto_increment,
    nome varchar(50) not null,
    descricao varchar(100) not null,
    quantidade integer not null, 
    preco double not null
)