CREATE DATABASE clinica_medica;

/*TIME - formato: 00h00min00seg*/
/*DATETIME - formato: YYYY-MM-DD HH:MI:SS*/

CREATE TABLE clinica_medica.medico(
	crm int NOT NULL unique PRIMARY KEY,
	nome varchar(50) NOT NULL,
	sala_atua int NOT NULL,
	horario_inicio_fixo time NOT NULL,
    horario_fim_fixo time NOT NULL
);

CREATE TABLE clinica_medica.responsavel(
	nome varchar(50) NOT NULL,
	cpf_responsavel bigint(11) NOT NULL unique PRIMARY KEY,
	idade int NOT NULL check(idade >=18), 
	grau_parentesco varchar(30) NOT NULL, 
	cpf_paciente bigint(11) NOT NULL unique
);

CREATE TABLE clinica_medica.paciente(
	cpf_paciente bigint(11) NOT NULL unique PRIMARY KEY,
	nome varchar(50) not null,
	cpf_responsavel bigint(11) unique,
	data_nasc date NOT NULL,
	convenio varchar(100),
	motivo_consulta varchar(255),
	foreign key (cpf_responsavel) references responsavel(cpf_responsavel)
);

CREATE TABLE clinica_medica.secretaria(
	id_secretaria int NOT NULL unique PRIMARY KEY, 
	nome varchar(50) NOT NULL, 
	telefone varchar(20) NOT NULL unique, 
	horario_inicio_atende time NOT NULL,
    horario_fim_atende time NOT NULL
);

CREATE TABLE clinica_medica.consulta(
	codigo int NOT NULL unique PRIMARY KEY, 
	data_horario_consulta datetime not null, 
	cpf_paciente bigint(11)  NOT NULL unique,
    crm int not null,
	foreign key (cpf_paciente) references paciente(cpf_paciente),
    foreign key (crm) references medico(crm)  
);

CREATE TABLE clinica_medica.indisponibilidade(
	crm int NOT NULL,
    indisponibilidade datetime,
	id_secretaria int NOT NULL, 
    foreign key (crm) references medico(crm),
    foreign key (id_secretaria) references secretaria(id_secretaria),
    primary key(crm, id_secretaria)
);
