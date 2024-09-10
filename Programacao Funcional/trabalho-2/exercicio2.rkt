#lang racket
(require examples)

;Uma empresa está desenvolvendo um sistema para automatizar o processo de correção
;de provas objetivas. Você trabalha nesta empresa e ficou responsável por elaborar a
;parte que irá ser utilizada na correção das provas. Considerando que cada questão
;possui somente uma alternativa correta e possui um valor, faça:
;---------------------------------------------------------------------------------------------------------------------
;a)Uma estrutura que permita armazenar um item do gabarito da prova, contendo aresposta correta e o valor daquela questão.
(struct gabarito (questao valor))

;b)Implemente uma função que verifique se gabarito G é um gabarito valido, ou seja,
;para todos seus itens, a resposta correta está entre 1 e 5 e sua pontução é um número.

;Recebe um gabarito, verifica se todos as questões estão entre 1 e 5, e se o valor é um numero, caso seja falso,
;retorna gabarito invalido, se chegar ao fim do gabarito, retorno que estão todos validos
;Lista de struct gabarito -> string "válido ou não válido"
(define (gabarito-valido? G)
  (cond
    [(empty? G) "Gabarito invalido"]
    [(and (>= (gabarito-questao (first G)) 1) (<= (gabarito-questao (first G)) 5))
          (cond
            [(empty? (rest G)) "Gabarito valido"]
            [(number? (gabarito-valor (first G)))
                      (gabarito-valido? (rest G))]
            [else "Gabarito invalido"])]
    [else "Gabarito invalido"]))
     
(define prova1 (list (gabarito 1 5) (gabarito 1 5) (gabarito 3 10) (gabarito 2 10) (gabarito 4 10) (gabarito 5 10)))
(define prova2 (list (gabarito 1 5) (gabarito 2 1) (gabarito 8 10)))
(define prova3 (list (gabarito 1 5) (gabarito 2 "5") (gabarito 2 10)))
(define prova4 (list ))

;c. Implemente uma função que retorne se a lista de respostas é uma lista válida
(define (resposta-valida? R)
  (cond
    [(empty? R) "resposta invalida"]
    [(number? (first R))
     (cond
       [(empty? (rest R)) "resposta valida"]
       [(and (>= (first R) 1) (<= (first R) 5))
             (resposta-valida? (rest R))]
       [else "resposta invalida"])]
    [else "resposta invalida"]))

(define resposta1 (list 2 1 3 5 4 5))
(define resposta2 (list 2 1 3 5 4 5 3))
(define resposta3 (list 2 2 1 4 2 3))
(define resposta4 (list "1" "5"))
(define resposta5 (list 3 4 8 9))
(define resposta6 (list ))

;d)Faça uma função que receba uma sequência de respostas para uma prova (ou seja,
;uma sequência de números inteiros de 1 a 5) e uma sequência de itens de gabarito.
;Sua função deverá retornar a pontuação obtida pela sequência de respostas.
;Caso a resposta e o gabarito tenham tamanhos diferentes, seu programa deverá gerar um erro.

;Função compara o tamanho do gabarito e resposta, caso não seja igual, já apresenta erro
;depois compara a questão da resposta com a questão do gabarito se for igual, soma o valor da questão, mais
;a chamada recursiva pro resto das resposta e gabarito, caso seja diferente, só continua verificando o resto do gabarito
;até chegar ao fim, e assim apresenta a soma dos valores das resposta corretas
(define (pontuacao resposta lista-gabarito)
  (cond
    [(and (empty? resposta) (empty? lista-gabarito)) 0]
    [(equal? (length resposta) (length lista-gabarito))
     (cond
       [(equal? (first resposta) (gabarito-questao (first lista-gabarito)))
                (+ (gabarito-valor (first lista-gabarito))
                   (pontuacao (rest resposta) (rest lista-gabarito)))]
       [else (pontuacao (rest resposta) (rest lista-gabarito))])]            
    [else "Tamanhos invalidos"]))

;--------------------------------------------------------------------------------------
(examples
  (check-equal? (gabarito-valido? prova1) "Gabarito valido")
  (check-equal? (gabarito-valido? prova2) "Gabarito invalido")
  (check-equal? (gabarito-valido? prova3) "Gabarito invalido")
  (check-equal? (gabarito-valido? prova4) "Gabarito invalido")

  (check-equal? (resposta-valida? resposta1) "resposta valida")
  (check-equal? (resposta-valida? resposta2) "resposta valida")
  (check-equal? (resposta-valida? resposta3) "resposta valida")
  (check-equal? (resposta-valida? resposta4) "resposta invalida")
  (check-equal? (resposta-valida? resposta5) "resposta invalida")
  (check-equal? (resposta-valida? resposta6) "resposta invalida")
  
  (check-equal? (pontuacao resposta1 prova1) 35)
  (check-equal? (pontuacao resposta2 prova1) "Tamanhos invalidos")
  (check-equal? (pontuacao resposta3 prova1) 0)
)