#lang racket
(require examples)
;; InteiroPositivo -> Booleano
;; Produz #t se uma pessoa com a idade n é supercentenária(se tem 110 anos ou mais) #f caso contrário.
(examples
  (check-equal? (supercentenario 101) #f)
  (check-equal? (supercentenario 110) #f)
  (check-equal? (supercentenario 112) #t))

(define (supercentenario idade)
  (if (> idade 110) #t #f)
)
