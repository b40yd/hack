#! /usr/local/bin/guile-gnome-2 \
-e main -s
!#


(use-modules (oop goops)
             (gnome gtk)
             (gnome glade))


(define help-str "移动鼠标到按钮上可看到简单帮助")

(define xml 
  (glade-xml-new "guitest.glade" #f #f))
(define window 
  (get-widget xml "window1"))
(define label-help
  (get-widget xml "label_help_button"))
(define label-show
  (get-widget xml "label_show"))
(define button-cat
  (get-widget xml "button_cat"))
(define button-dog
  (get-widget xml "button_dog"))

(define on_button_cat_clicked 
  (lambda (button)
    (slot-set! label-show 'label "I'm cat!!!")))
(define on_button_dog_clicked 
  (lambda (button)
    (slot-set! label-show 'label "I'm dog!!!")))
(define on_button_cat_enter 
  (lambda (button)
    (slot-set! label-help 'label "Click for cat")))
(define on_button_dog_enter 
  (lambda (button)
    (slot-set! label-help 'label "Click for dog")))
(define on_button_dog_leave
  (lambda (button)
    (slot-set! label-help 'label help-str)))
(define on_button_cat_leave
  (lambda (button)
    (slot-set! label-help 'label help-str)))
(define on_window1_remove
  (lambda (container window)
    (gtk-main-quit)
  )
)

(define main
  (lambda (args)
    (signal-autoconnect xml (current-module))
    (show window)
    (gtk-main)
  )
)

