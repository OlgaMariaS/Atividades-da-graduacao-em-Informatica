#lang racket
(require examples)
;a. Para empilhar um elemento, que receba uma pilha P e um valor x e retorne P’, que é P com x empilhado.
;b. Para desempilhar um elemento, que receba uma pilha P e retorne a pilha P’, que é P após remover o elemento do seu topo.
;c. Pare obter o topo da pilha. Caso a pilha esteja vazia, utilize a função error, com uma mensagem de erro. Exemplo: (error “pilha vazia”)

(struct pilha (dados)#:transparent)
;; pilha representa uma pilha de valores
;; dados: list - lista que armazena os itens da pilha
         
(define (empilhar pilha1 x)
  (cons x (pilha-dados pilha1)))

(define (desempilhar pilha1 x)
  (cond
    [(equal? (first pilha1) x) (rest pilha1)]
    [else pilha1]))

(define (topo pilha)
  (cond
    [(empty? pilha) "pilha vazia"]
    [else (first pilha)]))

(define pilha1 (pilha'(1 2 3 4 5)))

(examples
 (check-equal? (empilhar pilha1 4) '(4 1 2))
 (check-equal? (desempilhar '(1 4 5) 1) '(4 5))
 (check-equal? (desempilhar '(1 2) 4) '(1 2))
 (check-equal? (topo '(1 2)) 1)
)
