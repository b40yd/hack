
(define lst '(6 7 2 3 1))

(define llst '())
(define rlst '())

(define filters
  (lambda (x y)
    (if (procedure? x)
	(x y)
	"Not is procedure")))


;(define (ff lst)
;  (filters 
;   (lambda (x) 
;     (cond ((null? x) 
;	    '())
;	   ((> (car x) (car lst))
;	    (list (car x)))
;	   ((<= (car x) (car lst))
;	    (list (car x)))))
;   (if (null? lst)
;       '()
;       (cdr lst))))

(define (fmin lst factor)
  (filter (lambda (x) (<= x factor)) lst))


(define (fmax lst factor)
  (filter (lambda (x) (> x factor)) lst))


(define lsts '(8 7 3 4 2 5 1))

(define quick-sort 
  (lambda (lst)
    (cond
     ((null? lst) '())
     (else
      (let* ((first (car lst))
	     (small-part
	      (fmin (cdr lst) first))
	     (big-part 
	      (fmax (cdr lst) first)))
	(display small-part)
	(append (quick-sort small-part)
		(list first)
		(quick-sort big-part)))))))
  
;(define lst '(8 7 3 4 2 5 1))

;(filters
; (lambda (x)
;   (cond ((null? x)
;	  '())
;	 ((<= (car x) car lsts)
;	  (list car x)))
;   (cdr lst))) 
