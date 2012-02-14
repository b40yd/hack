(define greeting 
  "Please choice operating:
a) add data.  d) delete data.
s) search data. q) quit.
")

(define db-info 
  (lambda ()
    ;;(format #t "Please choice operating~%")
    (display greeting)
    ;;(newline)
    ))

(define db-search
  (lambda ()
    (format #t "db-search ok~%")))

(define fun
  (lambda ()
    (let ((ch (read)))
      (case ch
	((s) (db-search) (fun) )
	((q) 1)
	(else
	 (fun))
	)
)))




(define ask-todo
  (lambda (p)
    (do ((ch 0 (read)))

	((eqv? ch 'y) (p))
      
      (case ch
	((n) (main-loop))
	(else
	 (format #t "Are you sure?[y/n]~%")))
      )))


(define main-loop
  (lambda ()
    (do ((ch 0 (read))
	 )

	((eqv? ch 'q) (ask-todo primitive-exit))

      (case ch
	((s)
	 (db-search))
	(else
	 (db-info))))))

(define search 
  (lambda (e l)
    (let ((cc (lambda (ret)
		(for-each (lambda (x)
			    (if (eqv? x e)
				(ret "yes"))) l))))
      (call/cc cc))))