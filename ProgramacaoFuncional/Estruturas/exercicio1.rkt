#lang racket
(require examples)
;Declare uma struct que possa armazenar um horário do dia (hora, minuto e segundo).;Em seguida faça as as seguintes funções:
;a. Uma função que receba um horário e retorne se este horário é um horário valido do dia ou não (considerando o intervalo válido de horário de 0:00:00 até 23:59:59).
;b. Uma função que receba dois horários e retorne se o primeiro argumento é um horário posterior ao segundo.
;c. Uma função que receba dois horários e retorne se o primeiro horário é um horário anterior ao segundo.
;d. Uma função que receba dois horários e retorne se são iguais (faça como se a struct não fosse declarada como transparent).
;e. Uma função que receba um valor em segundos (assuma que esse valor estará entre 0 e 86399) e converta para um horário.
;f. Uma função que receba dois horários e retorne a diferença em segundos entre ambos.
;g. Uma função que receba dois horários e retorne a uma struct de horário que seja a diferença de ambos (ou seja, diferença em horas, minutos e segundos).

(struct horario (h m s) #:transparent)

(define (a tipo-horario)
  (cond
    [(and (> (horario-h tipo-horario) 00) (< (horario-h tipo-horario) 23)
          (> (horario-m tipo-horario) 00) (< (horario-m tipo-horario) 59)
          (> (horario-s tipo-horario) 00) (< (horario-s tipo-horario) 59))
     "Horario valido"]
    [else "Horario invalido"]
  ))

(define (bcd horario1 horario2)
  (cond
    [(> (horario-h horario1) (horario-h horario2)) "Horario posterior"]
    [(equal? (horario-h horario1) (horario-h horario2))
      (cond
        [(> (horario-m horario1) (horario-m horario2)) "Horario posterior"]
        [(equal? (horario-m horario1) (horario-m horario2))
          (cond
            [(> (horario-s horario1) (horario-s horario2)) "Horario posterior"]
            [(equal? (horario-s horario1) (horario-s horario2)) "Horarios iguais"]
            [else "Horario anterior"]
        )]
        [else "Horario anterior"]
     )]
    [else "Horario anterior"]))

(define (seg->hora seg) (quotient (quotient seg 60) 60))
(define (seg->min seg) (remainder (quotient seg 60) 60))
(define (seg->seg seg) (remainder seg 60))
  
(define (e seg)
  (if (and (> seg 0) (<= seg 86399))
      (string-append
        (string-append
           (string-append (number->string (seg->hora seg)) ":")
           (string-append (number->string (seg->min seg)) ":"))
        (number->string (seg->seg seg)))
      "Segundos inválidos"))

;definimos que horario1 sempre será maior que horario2
(define (diferenca-hrs h1 h2) (- (horario-h h1) (horario-h h2)))
(define (diferenca-min m1 m2) (- (horario-m m1) (horario-m m2)))
(define (diferenca-seg s1 s2) (- (horario-s s1) (horario-s s2)))

(define (hora->seg hrs) (* (* hrs 60) 60))
(define (min->seg min) (* min 60))

(define (fg horario1 horario2 opcao)
  (cond
    [(equal? opcao "f")
     (horario (diferenca-hrs horario1 horario2)
              (diferenca-min horario1 horario2)
              (diferenca-seg horario1 horario2))]
     [(equal? opcao "g")
      (+
       (+
        (hora->seg (diferenca-hrs horario1 horario2))
        (min->seg (diferenca-min horario1 horario2)))
       (diferenca-seg horario1 horario2))]))
    
(examples
(check-equal? (a (horario 13 47 01)) "Horario valido")
(check-equal? (a (horario 27 47 01)) "Horario invalido")

(check-equal? (bcd (horario 14 00 00) (horario 13 00 00)) "Horario posterior")
(check-equal? (bcd (horario 13 30 00) (horario 13 00 00)) "Horario posterior")
(check-equal? (bcd (horario 13 30 19) (horario 13 30 00)) "Horario posterior")
(check-equal? (bcd (horario 15 30 00) (horario 15 30 00)) "Horarios iguais")
(check-equal? (bcd (horario 13 30 00) (horario 14 00 00)) "Horario anterior")
(check-equal? (bcd (horario 15 30 00) (horario 15 31 00)) "Horario anterior")
(check-equal? (bcd (horario 15 30 00) (horario 15 30 10)) "Horario anterior")

(check-equal? (e 5000) "1:23:20")
(check-equal? (e 3661) "1:1:1")
(check-equal? (e 86400) "Segundos inválidos")

(check-equal? (fg (horario 22 37 02) (horario 13 30 00) "f") (horario 9 7 02))
(check-equal? (fg (horario 22 37 02) (horario 13 30 00) "g") 32822)

)