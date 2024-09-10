#lang racket
(require examples)

;entrada --> retorno
;; String -> String

;; Transforma a data de entrada do formato "dia/mes/ano" para o formato "ano/mes/dia".
;; Requer que o dia e o mes tenha dois dígitos e que o ano tenha quatro digitos.

(define (dia data) (substring data 0 2))
(define (mes data) (substring data 3 5))
(define (ano data) (substring data 6))

(define (data+barra x) (string-append x "/"))

(define (data-dma->data-amd data)
  (string-append (data+barra (ano data))
                 (string-append (data+barra (mes data))
                                (dia data))))


(examples
(check-equal? (data-dma->data-amd "19/07/2023") "2023/07/19")
(check-equal? (data-dma->data-amd "01/01/1980") "1980/01/01")
(check-equal? (data-dma->data-amd "02/02/2002") "2002/02/02"))
