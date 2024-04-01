/*Secretaria */
INSERT INTO clinica_medica.secretaria VALUES (01, 'Lilian Passos Scatalon', 44998427651, 070000, 170000);

/*Médicos*/
INSERT INTO clinica_medica.medico VALUES (111999, "Dr. Henrique", 12, 090000, 150000);
INSERT INTO clinica_medica.medico VALUES (669811, "Dra. Ana Flavia S.", 17, 123000, 173000);
INSERT INTO clinica_medica.medico VALUES (889144, "Dr. Sergio Colombo", 21, 130000, 170000);

/*Responsáveis*/
INSERT INTO clinica_medica.responsavel VALUES ("Paulo Sergio", 05384714494, 59, "Pai", 13262269984);
INSERT INTO clinica_medica.responsavel VALUES ("Simone", 05324895946, 45, "Mãe", 15411177798);

/*Pacientes*/
INSERT INTO clinica_medica.paciente VALUES (11964619963, "Eduardo Rufino", null, 20030425, "Bom Samaritano", "Hemorroida");
INSERT INTO clinica_medica.paciente VALUES (13262269984, "Gabriel Saraiva", 05384714494, 20071014, "Sem convenio", "Tosse seca, peito carregado");
INSERT INTO clinica_medica.paciente VALUES (11222333444, "Matheus Ito", null, 19940502, "Sem convenio", "Miopia");
INSERT INTO clinica_medica.paciente VALUES (07342864900, "Olga Maria", null, 20020914, "Unimed", "Tendinite");
INSERT INTO clinica_medica.paciente VALUES (05687222995, "José Augusto", null, 19940129, "Unimed", "Gripe e febre");
INSERT INTO clinica_medica.paciente VALUES (15411177798, "Brenda", 05324895946, 20160129, "Sem convenio", "pulso quebrado");
INSERT INTO clinica_medica.paciente VALUES (87454296311, "Yasser", null, 19940129, "Unimed", "Verme tenia");
INSERT INTO clinica_medica.paciente VALUES (24157894566, "Lucas", null, 20160129, "Sem convenio", "covid-19");

/*Informando a INDISPONIBILIDADE dos médicos*/
INSERT INTO clinica_medica.indisponibilidade VALUES (889144, 20240328140000, 01);
INSERT INTO clinica_medica.indisponibilidade VALUES (669811, 20240330150000, 01);

/*-------------------------------------CONSULTAS PERTINENTES AO DOMINIO------------------------------------------*/
/*Marcando consultas*/
INSERT INTO clinica_medica.consulta VALUES (224, 20240325110000, 11964619963, 889144);
INSERT INTO clinica_medica.consulta VALUES (225, 20240325130000, 05687222995, 889144);
INSERT INTO clinica_medica.consulta VALUES (226, 20240327120000, 15411177798, 889144);
INSERT INTO clinica_medica.consulta VALUES (177, 20240919160000, 13262269984, 669811);
INSERT INTO clinica_medica.consulta VALUES (969, 20241203153500, 11222333444, 111999);

/*Remarcações de consultas*/
UPDATE clinica_medica.consulta SET data_horario_consulta = '2024-09-18 16:00:00' WHERE (codigo = '177');
UPDATE clinica_medica.consulta SET data_horario_consulta = '2024-03-25 15:00:00' WHERE (codigo = '225');

/*Desmarcando consultas*/
DELETE FROM clinica_medica.consulta WHERE (codigo = '177');

/*Agenda de consultas do médico*/
/*Dr Sergio*/
SELECT medico.nome AS Medico,
	   paciente.nome AS Paciente, 
       consulta.data_horario_consulta AS Horario
FROM clinica_medica.consulta
JOIN clinica_medica.medico ON consulta.crm = medico.crm
JOIN clinica_medica.paciente ON consulta.cpf_paciente = paciente.cpf_paciente
WHERE (medico.crm = 889144);

/*Disponibilidade de médico*/
SELECT medico.nome AS Nome, 
       medico.horario_inicio_fixo AS Horario_entrada,
       medico.horario_fim_fixo AS Horario_termino,
       indisponibilidade.indisponibilidade AS Indisponivel
FROM clinica_medica.medico
JOIN clinica_medica.indisponibilidade ON indisponibilidade.crm = medico.crm
WHERE (medico.crm = 889144);

/*Funções de agregação - Quantidade de consultas marcadas*/
SELECT 	medico.nome AS Nome,
		COUNT(codigo) AS Quantidade_de_consultas
FROM clinica_medica.consulta
JOIN clinica_medica.medico ON consulta.crm = medico.crm
WHERE (consulta.crm = 889144);