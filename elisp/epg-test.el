
(require 'epg)
(require 'auth-source)

(defvar epg-protocol 'OpenPGP "Support OpenGPG or CMC")
(defvar cipher nil "test")
(let ((coding-system-for-write 'no-conversion)
      (context (epg-make-context epg-protocol))
      (signers (epg-list-keys (epg-make-context epg-protocol))))
  ;; (setf (epg-context-armor context) t)
  ;; (setf (epg-context-textmode context) t)
  ;; (setf (epg-context-signers context) signers)
  
  (f-write-bytes 
   (epg-encrypt-string context
                       "machine test login admin port 22 password admin"
                       signers
                       t)
   "~/.password-store/test.gpg")
  )
(epg-decrypt-string (epg-make-context) cipher)

(defun remember-password--read-keys (keys)
  (let ((ids '())
        (primary-sub-key (car (epg-key-sub-key-list keys)))
        (primary-user-id (car (epg-key-user-id-list keys))))
    (setq ids (plist-put ids :key (epg-sub-key-id primary-sub-key)))
    (setq ids (plist-put ids :user-id (epg-user-id-string primary-user-id)))
    (list ids)))

(defun remember-password-list-keys ()
  "docstring"
  (interactive)
  (let ((keys '()))
    (dolist (let-key (epg-list-keys (epg-make-context)))
      (setq keys (append keys (remember-password--read-keys let-key))))
    keys))

(let ((key-list (remember-password-list-keys)))
  (princ key-list))

(funcall (plist-get (car (auth-source-search :host "gitlab")) :secret))

(let ((user (plist-get (car (auth-source-search :host "test")) :user)))
  (s-split "\\^" user))
