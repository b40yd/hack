#!/usr/local/bin/guile -s
!#
(display #t)
(newline)
;; check type yes or no exist.
;; if exist,return this type.
;; not exist,return error,inform error where.
(define checking
  (lambda (name)
    (let ((t string-downcase))
      (cond ((string=? (t name) "int") name)
	    ((string=? (t name) "string") name)
	    (else
	     (error checking "Invalid Type!" name))))))


(define make-type-table
  (lambda (field-name field-type field-length)
    (list field-name field-type field-length)))

(define table
  (lambda (table-field field-to-data)
    (list table-field field-to-data)))

(define status-table
  (lambda (table-name p-key power)
    (list table-name p-key power)))

(define type-list '(("name" "string" 20) ("age" "int" 10)))

(define make-all-table
  (lambda (table-name type-list p-key)    
    (let loop ((ll type-list)
	    (type-table '())
	    (main-table '())
	    (new-status-table '()))
      (cond ((null? ll)
	     first)
	    ((not (null? (car ll)))
	     (loop (cdr ll)
		   (cons (make-type-table (caar ll) (checking (cdar ll)) (cddar ll)) type-table)
		   (cons (table (caar ll) "") main-table)
		   (cons (status-table table-name p-key 0) new-status-table))))
    (list type-table main-table new-status-table))))



	       ;;(format #t "~a~%" (cddar ll))))))
	       

