#lang racket

(define (primo? n)
  (cond
    ((<= n 1) #f)  
    ((= n 2) #t)  
    (else
     (define (divisivel-por? x y)
       (= (remainder x y) 0))
     (not (ormap (lambda (x)
                   (divisivel-por? n x))
                 (range 2 (add1 (floor (sqrt n)))))))))

(define (combinações-goldbach n)
  (cond
    ((and (even? n) (> n 4))
     (let loop ((pares '())
                (x 2))
       (if (> x (/ n 2))
           (reverse pares)
           (if (and (primo? x) (primo? (- n x)))
               (loop (cons (list x (- n x)) pares) (add1 x))
               (loop pares (add1 x))))))
    (else '())))

; Exemplo de uso:
(define numero 20)
(define resultado (combinações-goldbach numero))
(displayln resultado)
