#lang racket
(require examples)

(struct qtde_palavra (qtde pal)#:transparent)

(define lista2 (list (qtde_palavra 2 "a") (qtde_palavra 3 "f") (qtde_palavra 3 "c") (qtde_palavra 2 "e") (qtde_palavra 2 "b") (qtde_palavra 3 "d")))

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

;Vai percorrer a lista, verificando se os elementos estão na posição correta,
;caso não estejam, chama função ordena, e verifica o retorno da ordena
;no momento que verificar e todos os elementos estiverem corretos retorna a lista ordenada
(define (verifica-lista-ordenada lista)
  (cond
    [(empty? lista) empty]
    [(< (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
        (verifica-lista-ordenada (ordena lista))]
    [(and (= (qtde_palavra-qtde (first lista)) (qtde_palavra-qtde (first (rest lista))))
          (string>? (qtde_palavra-pal (first lista)) (qtde_palavra-pal (first (rest lista)))))
          (verifica-lista-ordenada (ordena lista))]
    [else lista]))

;(verifica-lista-ordenada (rest (verifica-lista-ordenada (ordena lista))))
   
(verifica-lista-ordenada lista2)
