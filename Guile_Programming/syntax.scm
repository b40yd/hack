#!/usr/local/guile/bin/guile -s
main
!#

;;;test guile parser...
(display "hello,world!")

;; test guile define-syntax 
(define-syntax when
  (syntax-rules ()
    ((when cond exp ...)
     (if (eq? cond #\s)
       (begin exp ...)))))

(when #t (let ((s "---")) (display s)))
(newline)

;; test guile define-syntax-rule
(define-syntax-rule (foo1 n t ...)
   (+ n t ...))
(display (foo1 1 2 3 4 5))
(newline)
