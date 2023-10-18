#lang racket
(require examples)

(struct qtde_palavra (qtde pal)#:transparent)

(define lista2 (list (qtde_palavra 2 "a") (qtde_palavra 3 "f") (qtde_palavra 3 "c") (qtde_palavra 2 "e") (qtde_palavra 2 "b") (qtde_palavra 3 "d")))
(define lista3 (list (qtde_palavra 8 "a") (qtde_palavra 1 "f") (qtde_palavra 4 "c") (qtde_palavra 5 "e") (qtde_palavra 9 "b") (qtde_palavra 2 "d")))
(define lista4 (list (qtde_palavra 4 "a") (qtde_palavra 1 "f") (qtde_palavra 6 "c") (qtde_palavra 12 "e") (qtde_palavra 6 "b") (qtde_palavra 17 "d")))

;Recebe uma lista e retorna ela ordenada
(define (ordena lista)
  (cond
    [(empty? (rest lista)) lista]
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

(define (bubble lista passadas)
  (cond
    [(equal? (length lista) passadas) lista]
    [else (bubble (ordena lista) (add1 passadas))]))

(bubble lista2 0)
(bubble lista3 0)
(bubble lista4 0)

