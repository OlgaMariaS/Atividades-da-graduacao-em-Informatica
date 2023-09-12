#lang racket
(require examples)
;Faça uma função que receba um valor natural e devolva a soma de seus algarismos.

(define (soma-recursiva n soma)
    (if (= n 0)
          soma
        (soma-recursiva (quotient n 10) (+ soma (remainder n 10)))))

(examples
 (check-equal? (soma-recursiva 1234 0) 10)
 (check-equal? (soma-recursiva 111 0) 3)
 (check-equal? (soma-recursiva 92 0) 11)
)
