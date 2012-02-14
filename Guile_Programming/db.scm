;;加载OOP模块
(use-modules (oop goops))
;;定义一个类 类名后面是继承父类参数
;;slot-ref 获取,类似get
;;slot-set! 设置,类似set
(define-class <HFG> ()
  (name #:init-value "" #:accessor hfg:name #:init-keyword #:name)
  (mail #:init-value "" #:accessor hfg:mail #:init-keyword #:mail)
  (age #:init-value "" #:accessor hfg:age #:init-keyword #:age)
  (gen-info #:allocation #:virtual 
	    #:accessor hfg:gen-info
	    #:slot-ref (lambda (o)
			 (let* ((name (slot-ref o 'name))
				(mail (slot-ref o 'mail))
				(age  (slot-ref o 'age))
				)
			   (format #f "name=~a&mail=~a&age=~a"
				   name mail age)))
	    #:slot-set! (lambda (o v)
			  #f)
	    )
  )


(define make-type-check
  (lambda (type)
    (let ((t string-downcase))
      (cond 
       ((string=? t "int") integer?)
       ((string=? t "uint") positive?)
       ((string=? t "string") string?)
       (else
	(error make-type-check "Invalid type!" type))))))
       
(define make-type-record
  (lambda (name type size)
    (list name (make-type-check type) size))) 


(define insert-type-to-table 
  (lambda (type-table keyname keytype keysize)
    (cons 
     (make-type-record keyname keytype keysize)
     type-table)))

(define create-table
  (lambda (name p-key)
    (cond 
     ((not (string? name))
      (error create-table "Invalid name!" name))
     ((not (string? p-key)) 
      (error create-table "Invalid p-key!" p-key))
     (else      
      (list (list name length p-key)
	    (list '())
	    (list '()))))))

(define table-type-handle '(("id" integer? 11) ("name" string? 20) ("age" integer? 2)))



(define db '((("id" 1) ("name" "bao") ("mail" "bao@gmail.com") ("age" "18"))
	     (("id" 2) ("name" "pw") ("mail" "pw@gmail.com") ("age" "18"))
	     (("id" 3) ("name" "gang") ("mail" "gang@gmail.com") ("age" "19"))))

(define search
  (lambda (db f p v)
    (let ((results '()))
      (for-each
       (lambda (x)
	 (let ((item (assoc-ref x f)))
	   (if (p (car item) v) (set! results (cons x results))
	       )))
       db)
      results)))

(define search_values
  (lambda (o f)
    (let ((results '()))
      (for-each
       (lambda (x)
	 (let ((var (assoc-ref x f)))
	   (set! results (cons var results)))
	 )
       o)
      results)))

;(map 
; (lambda (x)
;   (format #t "name:~a~%" (car x))) 
; (search_values (search db "id" <= 2) "name"))

;(for-each 
; (lambda (x) 
;   (set! array (cons (car x) array))) 
; (search_values (search db "id" <= 2) "name"))


;(define FIELD 1)
;(define TABLE 2)
;(define ITEM 3)
;(define PRE 4)
;(define VALUE 5)

;(define lang (string-split 
;	      (regexp-substitute #f 
;				 (string-match sql "select name from HFG where age = 18")
;				 'pre 1 "#" 2 "#" 3 "#" 4 "#" 5 'post) #\&))
;(define sql "select ([a-zA-Z0-9]*) from ([a-zA-Z0-9]*) where ([a-zA-Z0-9]*) ([=<>]*) ([a-z0-9A-Z]*)")


(define-syntax mselect 
  (syntax-rules (from where in) 
    ((mselect FIELD from TABLE where ID in (VALUE))
     (search_values (search TABLE ID string=? VALUE) FIELD))
    )
  )


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
