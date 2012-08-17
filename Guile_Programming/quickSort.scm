
(define lst '(6 7 2 3 1))

(define llst '())
(define rlst '())

(define filters
  (lambda (x y)
    (if (procedure? x)
	(x y))
    'Not is procedure'))

(filters 
 (lambda (x) 
   (cond ((null? x) 
	  '())
	 ((> (car x) (car lst))
	  (set! llst (append llst (list (car x)))))
	 ((<= (car x) (car lst))
	  (set! rlst (append rlst (list (car x)))))))
 (cdr lst))

(define lsts '(8 7 3 4 2 5 1))

(define quick-sort 
  (lambda (lst)
    (cond
     ((null? lst) '())
     (else
      (let ((small-part
	     (filters
	      (lambda (x) 
		(cond ((null? x) 
		       '())
		      ((<= (car x) (car lsts))
		       (list (car x)))))
	      (cdr lst)))
	    (big-part 
	     (filters 
	      (lambda (x) 
		(cond ((null? x) 
		       '())
		      ((> (car x) (car lsts))
		       (list (car x)))))
	      (cdr lst))))
	(append (quick-sort small-part)
		(list (car lst))
		(quick-sort big-part)))))))

(define lst '(8 7 3 4 2 5 1))

(filters
 (lambda (x)
   (cond ((null? x)
	  '())
	 ((<= (car x) car lsts)
	  (list car x)))
   (cdr lst))) 
