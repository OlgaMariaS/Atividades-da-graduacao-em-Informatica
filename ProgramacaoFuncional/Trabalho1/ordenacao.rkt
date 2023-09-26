#lang racket
(require examples)

(struct qtde_palavra (qtde pal)#:transparent)

(define lista2 (list (qtde_palavra 2 "a") (qtde_palavra 3 "f") (qtde_palavra 3 "c") (qtde_palavra 2 "e") (qtde_palavra 2 "b") (qtde_palavra 1 "d")))
(define lista-ordenada (list (qtde_palavra 3 "c") (qtde_palavra 3 "f") (qtde_palavra 2 "a") (qtde_palavra 2 "b") (qtde_palavra 2 "e") (qtde_palavra 1 "d")))

;Recebe uma lista e retorna ela ordenada
(define (ordena lista)
  (cond
    [(empty? (rest lista)) (first lista)]
    [(> (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
         (cons (first lista)
               (ordena (rest lista)))]
    [(= (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
         (cond
             [(string<? (qtde_palavra-pal (first lista)) (qtde_palavra-pal (first (rest lista))))
              (cons (first lista)
                    (ordena (rest lista)))]
             [else (cons (first (rest lista))
                         (ordena (cons (first lista)
                                       (cdr (rest lista))))) ])]                
    [else (cons (first (rest lista))
                (ordena (cons (first lista)
                              (cdr (rest lista)))))]))

(define (percorre-para-ordenar lista)
  (cond
    [(empty? lista) empty]
    [else (ordena (lista)) ]))
  
(ordena lista2)
;(examples
 ;(check-equal? (ordena lista2) (lista-ordenada)))
