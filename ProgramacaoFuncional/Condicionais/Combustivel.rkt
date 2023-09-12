#lang racket
;;Programa que gera retorno se é viavel usar alcool ou gasolina, caso alcool seja até 70% do valor da gasolina

;;Teste para verificação se está correto o codigo


(define (combustivel precoAlcool precoGasol)
  (cond
    [(<= precoAlcool (* 0.7 precoGasol)("Alcool"))]
    [else ("Gasolina")]
  )