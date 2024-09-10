#lang racket
(require examples)
;Declare uma struct que armazene o nome, peso, idade de uma pessoa. Em seguida faça funções para:
;a. Verificar se os dados da pessoa são validos (idade e peso positivos).
;b. Receber duas pessoas e retornar a mais velha (em caso de mesma idade, retorne a pessoa que foi passada como primeiro argumento).
;c. Receber duas pessoas e retornar a mais pesada (em caso de mesmo peso,retorne a que foi passada como primeiro argumento)
;d. Receber uma pessoa e retornar ela com um ano a mais.
;e. Receber uma pessoa, um valor real que represente quantos quilos a pessoa ganhou (ou perdeu) e retornar a pessoa com um novo peso.
;f. Calcular o índice de massa corporal (IMC) da pessoa.;O IMC de uma pessoa é dado pela fórmula a seguir: IMC = Peso(kg)/Altura(m)^2
;g. Classificar a pessoa de acordo com seu IMC considerando a tabela a seguir
;IMC              Classificação
;Menor que 18,5   Magreza
;18,5 a 24,9      Normal
;25 a 29,9        Sobrepeso
;30 a 34,9        Obesidade grau I
;35 a 39,9        Obesidade grau II
;Maior que 40     Obesidade grau III

(struct pessoa (nome peso idade) #:transparent)

(define (a dados_pessoa)
  (if (and (> (pessoa-peso dados_pessoa) 0) (> (pessoa-idade dados_pessoa) 0))
      "Dados validos"
      "Dados invalidos"))

(define (b pessoa1 pessoa2)
  (cond
    [( > (pessoa-idade pessoa2) (pessoa-idade pessoa1))
      (string-append (pessoa-nome pessoa2) " é mais velha")]
    [else
       (string-append (pessoa-nome pessoa1) " é mais velha")]))

(define (c pessoa1 pessoa2)
  (cond
    [( > (pessoa-peso pessoa2) (pessoa-peso pessoa1))
    (string-append (pessoa-nome pessoa2) " é mais pesada")]
    [else
       (string-append (pessoa-nome pessoa1) " é mais pesada")]))

(define (d pessoas)
  (pessoa
    (pessoa-nome pessoas)
    (pessoa-peso pessoas)
    (+ (pessoa-idade pessoas) 1)))

(define (e pessoas kg)
  (pessoa
    (pessoa-nome pessoas)
    (+ (pessoa-peso pessoas) kg)
    (pessoa-idade pessoas)))

(define (imc pessoa altura)
  (/ (pessoa-peso pessoa) (expt altura 2)))

(define (classifica_imc pessoa altura)
  (cond
    [(<= (imc pessoa altura) 18.5) "Magreza"]
    [(and (> (imc pessoa altura) 18.5) (<= (imc pessoa altura) 24.9)) "Normal"]
    [(and (>= (imc pessoa altura) 25.0) (<= (imc pessoa altura) 29.9)) "Sobrepeso"]
    [(and (>= (imc pessoa altura) 30.0) (<= (imc pessoa altura) 34.9)) "Obesidade grau I"]
    [(and (>= (imc pessoa altura) 35.0) (<= (imc pessoa altura) 39.9)) "Obesidade grau II"]
    [else "Obesidade grau III"]))

(examples
(check-equal? (a (pessoa "Olga" 54 21)) "Dados validos")
(check-equal? (a (pessoa "José" -10 26)) "Dados invalidos")

(check-equal? (b (pessoa "Carlos" 54 27) (pessoa "Bruna" 50 19)) "Carlos é mais velha")
(check-equal? (b (pessoa "Carlos" 54 15) (pessoa "Bruna" 50 19)) "Bruna é mais velha")

(check-equal? (c (pessoa "Carlos" 54 27) (pessoa "Bruna" 60 19)) "Bruna é mais pesada")
(check-equal? (c (pessoa "Carlos" 54 15) (pessoa "Bruna" 42 19)) "Carlos é mais pesada")

(check-equal? (d (pessoa "Olga" 54 21)) (pessoa "Olga" 54 22))

(check-equal? (e (pessoa "Olga" 54 21) 2) (pessoa "Olga" 56 21))
(check-equal? (e (pessoa "Olga" 54 21) -4) (pessoa "Olga" 50 21))

(check-equal? (imc (pessoa "Olga" 54 21) 1.50) 24.0)

(check-equal? (classifica_imc (pessoa "Olga" 40 21) 1.50) "Magreza")
(check-equal? (classifica_imc (pessoa "Olga" 54 21) 1.50) "Normal")
(check-equal? (classifica_imc (pessoa "Olga" 65 21) 1.50) "Sobrepeso")
(check-equal? (classifica_imc (pessoa "Olga" 75 21) 1.50) "Obesidade grau I")
(check-equal? (classifica_imc (pessoa "Olga" 89 21) 1.50) "Obesidade grau II")
(check-equal? (classifica_imc (pessoa "Olga" 150 21) 1.50) "Obesidade grau III")
)