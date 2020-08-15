
(require 'hydra)

(defun nav/mc/mark-all-dwim ()
  (interactive)
  (nav/symbol-at-point/mark)
  (exchange-point-and-mark)
  (mc/mark-all-like-this))

(defun nav/open-next-line ()
  (interactive)
  (end-of-line)
  (open-line 1)
  (forward-char 1))

(defun nav/org/clock-in/select ()
  (interactive)
  (let ((current-prefix-arg '(4)))
    (call-interactively 'org-clock-in)))

(defun nav/dumb-jump-go ()
  (interactive)
  (push-mark)
  (dumb-jump-go))

(defun nav/symbol-at-point/mark ()
  (unless (use-region-p)
    (let ((pos (bounds-of-thing-at-point 'symbol)))
      (if pos
          (progn
            (goto-char (car pos))
            (set-mark-command nil)
            (goto-char (cdr pos)))
        (error "Not on a symbol!")))))
(defun nav/symbol-at-point/grep ()
  (interactive)
  (nav/symbol-at-point/mark)
  (call-interactively 'helm-ag))
(defun nav/symbol-at-point/sexp-eval ()
  (interactive)
  (save-excursion
    (forward-sexp 1)
    (eval-last-sexp nil)))

;; Mode-line color indication feature
;; Disabled by default because it seems to become extremely slow
;; to change colors after a while. Not sure why.
(defvar nav/colorize-modeline nil
  "Indicates whether `vi-mode' should change the color of the
modeline when enabled.
If non-nil, `vi-mode' will change the modeline colors to those set in
the following variables when enabled and disabled:
`nav/modeline-active-foreground-off'
`nav/modeline-active-background-off'
`nav/modeline-inactive-foreground-off'
`nav/modeline-inactive-background-off'
`nav/modeline-active-foreground-on'
`nav/modeline-active-background-on'
`nav/modeline-inactive-foreground-on'
`nav/modeline-inactive-background-on'
")

(defvar nav/modeline-active-foreground-off "Black"
  "The modeline foreground color to be used for active (selected) buffers
in which `vi-mode' is disabled.")
(defvar nav/modeline-active-background-off "Light gray"
  "The modeline background color to be used for active (selected) buffers
in which `vi-mode' is disabled.")
(defvar nav/modeline-inactive-foreground-off "Black"
  "The modeline foreground color to be used for inactive (unselected)
buffers in which `vi-mode' is disabled.")
(defvar nav/modeline-inactive-background-off "Gainsboro"
  "The modeline background color to be used for inactive (unselected)
buffers in which `vi-mode' is disabled.")

(defvar nav/modeline-active-foreground-on "Blue"
  "The modeline foreground color to be used for active (selected)
buffers in which `vi-mode' is enabled.")
(defvar nav/modeline-active-background-on "White"
  "The modeline background color to be used for active (selected)
buffers in which `vi-mode' is enabled.")
(defvar nav/modeline-inactive-foreground-on "Light blue"
  "The modeline foreground color to be used for inactive (unselected)
buffers in which `vi-mode' is enabled.")
(defvar nav/modeline-inactive-background-on "White"
  "The modeline background color to be used for inactive (unselected)
buffers in which `vi-mode' is enabled.")

(defun nav/change-modeline-color (colorize)
  "Change the modeline color to indicate that vi-mode is active or inactive.
This function does nothing if `nav/colorize-modeline' is nil.
Argument COLORIZE dictates whether to turn colorization on or off.
Possible values are:
- nil            : Turn colorization off, returning the modeline to
                   white text on a black background.
- anything else  : Turn colorization on, setting the modeline to white
                   text on a blue background.
"
  (interactive)
  (when nav/colorize-modeline
    (if colorize
        (progn
          ;; Entering, turn colorization on
          (face-remap-add-relative
           'mode-line
           `((:foreground
              ,nav/modeline-active-foreground-on
              :background
              ,nav/modeline-active-background-on) mode-line))
          (face-remap-add-relative
           'mode-line-inactive
           `((:foreground
              ,nav/modeline-inactive-foreground-on
              :background
              ,nav/modeline-inactive-background-on) mode-line)))
      ;; else
      ;; Exiting, turn colorization off
      (face-remap-add-relative
       'mode-line
       `((:foreground
          ,nav/modeline-active-foreground-off
          :background
          ,nav/modeline-active-background-off) mode-line))
      (face-remap-add-relative
       'mode-line-inactive
       `((:foreground
          ,nav/modeline-inactive-foreground-off
          :background
          ,nav/modeline-inactive-background-off) mode-line)))))

(defvar nav/alter-cursor nil
  "Alter the cursor style when `vi-mode' is active?")
(defvar nav/cursor-type-active 'hollow
  "The cursor style to be used when vi-mode is active (if
`nav/alter-cursor' is non-nil).")
(defvar nav/cursor-type-inactive cursor-type
  "The cursor style to be used when vi-mode is not active (if
`nav/alter-cursor' is non-nil).")

(defun nav/change-cursor-type (enable)
  "If `nav/alter-cursor' and ENABLE are both non-nil, change the cursor
style to `nav/cursor-type-active'."
  (interactive)
  (when nav/alter-cursor
    (setq cursor-type (if (and nav/alter-cursor enable)
                          nav/cursor-type-active
                        ;; else
                        nav/cursor-type-inactive)) ))

(defun nav/set-visual-indicators (enable)
  "DOCSTRING"
  (interactive)
  (nav/change-modeline-color enable)
  (nav/change-cursor-type enable))

;; Exiting and toggling nav and nav/m modes
(defun exit-nav-modes ()
  "Exit `vi-mode'."
  (interactive)
  (nav/set-visual-indicators nil)
  (vi-mode -1)
  (autopair-mode 1))

(defun exit-nav-modes/insert ()
  "Same as `exit-nav-modes' but set the mark first."
  (interactive)
  (unless (use-region-p)
    (push-mark))
  (exit-nav-modes))

(defun toggle-nav-mode (&optional nav/set-state)
  "Turn vi-mode on or off.
It is preferable that this function is used to enable and disable
`vi-mode' because it handles a number of things that toggling
`vi-mode' directly does not. For example, entering and exiting
`vi-mode' with this function will properly manage modeline
colorization if `nav/colorize-modeline' is t.
Optional argument NAV/SET-STATE may be used to ensure that vi-mode is
in a given state. Possible values are:
- nil or no argume_nt : Toggle `vi-mode' on if it is off, or off if it
                       is on, in the current buffer.
- -1                 : Turn `vi-mode' off if it is on; otherwise do nothing.
- anything else      : Turn `vi-mode' on if it is off; otherwise do nothing.
"
  (interactive)
  (if nav/set-state
      ;; explicit argument
      (if (= nav/set-state -1)
          ;; turn off
          (exit-nav-modes)
        ;; else - turn on
        (enter-nav-mode))

    ;; else - toggle
    (if vi-mode
        (exit-nav-modes)
      ;; else
      (enter-nav-mode))))

(defun enter-nav-mode ()
  "Enter `vi-mode'."
  (vi-mode 1)
  (nav/set-visual-indicators t)
  (autopair-mode -1))

;; nav macros
(fset 'nav/macro-5
      [?\C-x ?\C-k ?5])
(fset 'nav/macro-6
      [?\C-x ?\C-k ?6])
(fset 'nav/macro-7
      [?\C-x ?\C-k ?7])
(fset 'nav/macro-8
      [?\C-x ?\C-k ?8])

(defun nav/end-of-line (&optional arg)
  (interactive)
  (if (equal major-mode 'org-mode)
      (org-end-of-line arg)
    (move-end-of-line arg)))

(defun nav/beginning-of-line (&optional arg)
  (interactive)
  (when (equal major-mode 'org-mode)
    (org-beginning-of-line arg))
  (previous-line (1- (or arg 1)))
  ;; (ll-match-regexps-to-str (buffer-substring-no-properties (point) (point-at-bol)) '("^[ \t]+$"))
  (back-to-indentation))

(defun nav/beginning-of-line-and-exit (&optional arg)
  (interactive)
  (nav/beginning-of-line arg)
  (exit-nav-modes/insert))

(defun nav/end-of-line-and-exit (&optional arg)
  (interactive)
  (nav/end-of-line arg)
  (exit-nav-modes/insert))

(defun nav/beginning-of-buffer-and-exit ()
  (interactive)
  (beginning-of-buffer)
  (exit-nav-modes))

(defun nav/end-of-buffer-and-exit ()
  (interactive)
  (end-of-buffer)
  (exit-nav-modes))


(defun nav/open-insert-next-line ()
  (interactive)
  (end-of-line)
  (newline-and-indent)
  (exit-nav-modes/insert))

(defun nav/open-insert-previous-line ()
  (interactive)
  (beginning-of-line)
  (open-line 1)
  (indent-according-to-mode)
  (exit-nav-modes/insert))

(defun nav/join-line (&optional arg)
  "Join ARG lines below the current line with the current line."
  (interactive)
  (next-logical-line arg)
  (dotimes (_ (or arg 1)) (join-line)))

(defun nav/join-up-line (&optional arg)
  "Join ARG lines below the current line with the current line."
  (interactive)
  (dotimes (_ (or arg 1)) (join-line)))

(defun nav/jump-to-char (&optional arg)
  "Prompt for a char and jump to the first (or with argument Nth) occurence
of it to the right of the point."
  (interactive "P")
  (let ((case-fold-search nil)) ;; make search case sensitive
    (search-forward (char-to-string (read-char "char: ")) nil t arg)))

(defun nav/backward-jump-to-char (&optional arg)
  "Prompt for a char and jump to the first (or with argument Nth) occurence
of it to the left of the point."
  (interactive "P")
  (let ((case-fold-search nil)) ;; make search case sensitive
   (search-backward (char-to-string (read-char "char: ")) nil t arg)))

(defun nav/mark-pop-and-jump ()
  (interactive)
  (set-mark-command 1))

(defun nav/delete-trailing-whitespace ()
  (interactive)
  (delete-trailing-whitespace (point-min) (point-max)))

(defun nav/untabify ()
  (interactive)
  (untabify (point-min) (point-max)))

(defun nav/cleanup-buffer ()
  (interactive)
  (nav/delete-trailing-whitespace)
  (nav/untabify))

(defun nav/sexp-at-point/goto-start ()
  (unless (member (char-before (point))
                  '(?  ?' ?\( ?\C-j ?\C-i ?\" ?\[))
    (forward-sexp)
    (backward-sexp)))

(defun nav/change-command (&optional arg)
  (interactive "P")
  (nav/delete-command arg)
  (exit-nav-modes/insert))

(defun number-string-p (str)
  (or (string-equal str "0")
      (not (zerop (string-to-number str)))))

(defvar nav/paste-line nil
  "Are the contents of the kill buffer a line?")
(defvar nav/delstart-persistent nil
  "Persistent delete region marker.")
(defun nav/delete-command (&optional arg)
  (interactive "P")
  (setq nav/paste-line nil)
  (if (use-region-p)
      (kill-region (region-beginning) (region-end))

    (let ((delstart (point))
          (pref-arg-string (if arg (concat (number-to-string arg) " ") ""))
          (movement-cmd (single-key-description
                         (read-char (format "[%s] move: " (or arg ""))))))
      (pcase movement-cmd
        ((pred number-string-p)
         (nav/delete-command
          (+ (string-to-number movement-cmd) (* (or arg 0) 10))))
        ("c"
         (back-to-indentation)
         (setq delstart (point))
         (end-of-line arg))
        ("d"
         (beginning-of-line)
         (setq delstart (point))
         (next-logical-line arg)
         (beginning-of-line)
         (setq nav/paste-line t))
        ("f"
         (nav/jump-to-char arg))
        ("F"
         (nav/backward-jump-to-char arg))
        ("g"
         (call-interactively (avy-goto-char-timer arg)))
        ("SPC"
         (nav/sexp-at-point/goto-start)
         (setq delstart (point))
         (forward-sexp))
        ("C-@"
         (sp-backward-up-sexp)
         (setq delstart (point))
         (forward-sexp))
        ("m"
         (setq nav/delstart-persistent (point))
         (message "Nav: Delete mark set"))
        ("r"
         (if nav/delstart-persistent
             (setq delstart nav/delstart-persistent)
           (message "Nav: Delete mark not set!")))

        (other-cmd
         (execute-kbd-macro (kbd (concat pref-arg-string other-cmd)))))

      (kill-region delstart (point)))))

(defvar nav/copystart-persistent nil
  "Persistent copy region marker.")
(defun nav/copy-command (&optional arg)
  (interactive "P")
  (setq nav/paste-line nil)
  (save-excursion
    (if (use-region-p)
        (copy-region-as-kill (region-beginning) (region-end))

      (let ((copystart (point))
            (copyend nil)
            (pref-arg-string (if arg (concat (number-to-string arg) " ") ""))
            (movement-cmd (single-key-description
                           (read-char (format "[%s] move: " (or arg ""))))))
        (pcase movement-cmd
          ((pred number-string-p)
           (nav/copy-command
            (+ (string-to-number movement-cmd) (* (or arg 0) 10))))
          ("y"
           (beginning-of-line)
           (setq copystart (point))
           (next-logical-line arg)
           (beginning-of-line)
           (setq nav/paste-line t))
          ("f"
           (nav/jump-to-char arg))
          ("F"
           (nav/backward-jump-to-char arg))
          ("g"
           (call-interactively (avy-goto-char-timer arg)))
          ("SPC"
           (nav/sexp-at-point/goto-start)
           (setq copystart (point))
           (forward-sexp))
          ("C-@"
           (sp-backward-up-sexp)
           (setq copystart (point))
           (forward-sexp))
          ("m"
           (setq nav/copystart-persistent (point))
           (message "Nav: Copy mark set"))
          ("r"
           (if nav/copystart-persistent
               (setq copystart nav/copystart-persistent)
             (message "Nav: Copy mark not set!")))

          (other-cmd
           (execute-kbd-macro (kbd (concat pref-arg-string other-cmd)))))

        (copy-region-as-kill copystart (point))))))

(defun nav/paste-after (&optional arg)
  (interactive "P")
  (dotimes (_ (or arg 1)) (nav/do-paste)))

(defun nav/paste-before (&optional arg)
  (interactive "P")
  (dotimes (_ (or arg 1)) (nav/do-paste t)))

(defun nav/do-paste (&optional before-p)
  (cond ((and nav/paste-line before-p)
         (beginning-of-line))

        (nav/paste-line ;; !before-p
         (next-logical-line)
         (beginning-of-line))

        (before-p ;; !nav/paste-line
         (backward-char 1)))

  (when (use-region-p)
      (delete-region (region-beginning) (region-end)))
  (yank)
  (when nav/paste-line
    (previous-logical-line)))

(defun nav/swap-yank-command (&optional arg)
    "Same as `nav/delete-command', but yank the (current) front of
the kill ring after deleting. This can be done repeatedly to
repeatedly swap the same string."
    (interactive "P")
    (nav/delete-command arg)
    (yank 2)
    (with-temp-buffer
      (yank 1)
      (kill-new (buffer-string))))


(defun nav/narrow-to-subtree ()
    (interactive)
    (org-mark-subtree)
    (call-interactively 'ni-narrow-to-region-indirect-other-window))

;;;;;;;;;; Hydras ;;;;;;;;;;
(defhydra nav/hydra/master (:color blue :hint nil)
  "
Master menu
_r_: Registers (=)              _f_: Frames
_m_: Macros (m)                 _c_: Multiple cursors
_b_: Buffer actions             _s_: Symbol at point
_o_: Org actions
"
  ("r" nav/hydra/registers/body)
  ("m" nav/hydra/macros/body)
  ("f" nav/hydra/frames/body)
  ("c" nav/hydra/mc/body)
  ("b" nav/hydra/buffer-edit/body)
  ("s" nav/hydra/symbol-at-point/body)
  ("o" nav/hydra/org/body)
  ("q" nil))
(defhydra nav/hydra/registers (:color blue :hint nil)
  "
Register commands
_s_: Save point                 _n_: Number to register
_j_: Jump to register         _i_/_+_: Increment number in register
_y_: Copy to register           _h_: Show registers
_p_: Insert from register       _w_: Window config to register
"
  ("s" point-to-register)
  ("j" jump-to-register)
  ("y" copy-to-register)
  ("p" insert-register)
  ("h" helm-register)
  ("n" number-to-register)
  ("i" increment-register)
  ("+" increment-register)
  ("w" window-configuration-to-register)
  ("q" nil))
(defhydra nav/hydra/macros (:color blue :hint nil)
  "
Macro commands
_n_: (New) Start defining macro       _b_: Bind macro to key (then exec with m5-8)
_d_: (Done) Finish defining macro     _l_: Edit recorded macro
_e_: Execute macro                    _r_: Repeat last command
"
  ("n" kmacro-start-macro)
  ("d" kmacro-end-macro)
  ("e" kmacro-end-and-call-macro)
  ("b" kmacro-bind-to-key)
  ("l" kmacro-edit-lossage)
  ("r" repeat)
  ("q" nil))
(defhydra nav/hydra/frames (:hint nil)
  "
Frame manipulation
_l_: Grow window horizontally      _x_: Toggle maximize buffer
_h_: Shrink window vertically      _e_: Toggle window split style
_k_: Grow window vertically        _w_: Save window configuration to register
_j_: Shrink window vertically      _r_: Restore window configuration from register
                                 _s_: Swap windows
"
  ("l" enlarge-window-horizontally)
  ("h" shrink-window-horizontally)
  ("k" enlarge-window)
  ("j" shrink-window)
  ("x" toggle-maximize-buffer :color blue)
  ("e" toggle-window-split :color blue)
  ("w" window-configuration-to-register :color blue)
  ("r" jump-to-register :color blue)
  ("s" swap-window-split :color blue)
  ("q" nil))
(defhydra nav/hydra/mc (:hint nil)
  "
     ^Up^            ^Down^        ^Miscellaneous^
----------------------------------------------
[_p_]   Next    [_n_]   Next    [_l_] Edit lines
[_P_]   Skip    [_N_]   Skip    [_a_] Mark all
[_u_]   Unmark  [_m_]   Unmark  [_q_] Quit
"
  ("l" mc/edit-lines :exit t)
  ("a" nav/mc/mark-all-dwim :exit t)
  ("n" mc/mark-next-like-this)
  ("N" mc/skip-to-next-like-this)
  ("m" mc/unmark-next-like-this)
  ("p" mc/mark-previous-like-this)
  ("P" mc/skip-to-previous-like-this)
  ("u" mc/unmark-previous-like-this)
  ("q" nil))
    (defhydra nav/hydra/buffer-edit (:color blue :hint nil)
  "
Buffer edit menu
_t_: Delete trailing whitespace                 _=_: Increase text size
_u_: Untabify                                   _-_: Decrease text size
_c_: Cleanup buffer (_t_ + _u_)                 _w_: Toggle word wrap
_t_: Toggle line truncation                     _h_: Toggle whitespace mode
"
  ("t" nav/delete-trailing-whitespace)
  ("u" nav/untabify)
  ("c" nav/cleanup-buffer)
  ("=" text-scale-increase :color red)
  ("-" text-scale-decrease :color red)
  ("w" toggle-word-wrap)
  ("t" toggle-truncate-lines)
  ("h" whitespace-mode)
  ("q" nil))

(defhydra nav/hydra/symbol-at-point (:hint nil :color blue)
  "
Symbol/sexp at point menu
_s_: Search                    _g_: Grep/ag        _G_: Interactive ag
_r_: Replace/rename            _d_: Definition
_;_/_o_: Occur                 _e_: Eval
"
  ("s" isearch-forward-symbol-at-point)
  ("g" nav/symbol-at-point/grep)
  ("G" helm-do-grep-ag)
  ("d" nav/dumb-jump-go)
  ("r" highlight-symbol-query-replace)
  (";" helm-occur)
  ("o" helm-occur)
  ("e" nav/symbol-at-point/sexp-eval)
  ("q" nil :color blue))
(defhydra nav/hydra/sexp-nav (:hint nil :color red)
  "
Sexp navigation menu
_a_: Beginning                    _e_: End                              _n_: New sexp                     _d_: Delete sexp
_l_: Forward                      _h_: Backward                         _y_: Copy sexp                    _M-e_: Eval sexp
_k_: Up left                      _K_: Up right                         _RET_: Exit sexp and newline
_j_: Down                         _J_: Backward down                    _w_: Wrap sexp                    _W_: Unwrap sexp
_s_: Slurp forward                _S_: Slurp backward
_b_: Barf forward                 _B_: Barf backward
"
  ("a" sp-beginning-of-sexp)
  ("e" sp-end-of-sexp)
  ("l" sp-forward-sexp)
  ("h" backward-sexp)
  ("k" sp-backward-up-sexp)
  ("K" sp-up-sexp)
  ("j" sp-down-sexp)
  ("J" sp-backward-down-sexp)

  ("w" (lambda () (interactive) (sp-wrap-with-pair "(")))
  ("W" sp-unwrap-sexp)

  ("n" (lambda () (interactive) (insert "()") (backward-char 1)))
  ("d" sp-kill-sexp)
  ("y" sp-copy-sexp)
  ("M-e" (lambda () (interactive) (save-excursion
                                    (forward-sexp)
                                    (eval-last-sexp nil))))
  ("RET" (lambda () (interactive) (sp-up-sexp) (autopair-newline)))

  ("s" sp-forward-slurp-sexp)
  ("S" sp-backward-slurp-sexp)
  ("b" sp-forward-barf-sexp)
  ("B" sp-backward-barf-sexp)
  ("q" nil :color blue))
(defhydra nav/hydra/org (:hint nil :color blue)
  "
Org menu
== Structure ==       == Clock & Time ==
_s_: Sort                           _TAB_ Cycle global visibility           _i_: Clock in recent task
_e_: Sparse tree                    _c_: Enter column view                  _r_: Show remaining timer
_y_: Copy subtree structure         _p_: Set property                       _t_: Set timer
_w_: Refile                         _x_: Export                             _._: Active timestamp
_m_: Promote subtree                _M_: Promote heading                    _<_: Inactive timestamp
_d_: Demote subtree                 _D_: Demote heading
_z_: Save all org buffers           _n_: Narrow to subtree
"
  ("i" nav/org/clock-in/select)
  ("r" org-timer-show-remaining-time)
  ("t" org-timer-set-timer)
  ("s" org-sort)
  ("e" org-sparse-tree)
  ("y" org-copy-subtree)
  ("w" org-refile)
  ("p" org-set-property)
  ("x" org-export)
  ("m" org-promote-subtree :color red)
  ("M" org-do-promote :color red)
  ("d" org-demote-subtree :color red)
  ("D" org-do-demote :color red)
  ("." org-time-stamp)
  ("<" org-time-stamp-inactive)
  ("TAB" org-shifttab :color red)
  ("c" org-columns)
  ("z" org-save-all-org-buffers)
  ("n" nav/narrow-to-subtree)
  ("q" nil))

(require 'misc)

;; for some reason these bindins using Alt must be defined outside the
;; map to work?
(defvar vi-mode-map
  (let ((vi-keymap (make-sparse-keymap)))
    (define-key vi-keymap (kbd "M-O") 'nav/open-next-line)
    (define-key vi-keymap (kbd "M-RET") 'nav/open-next-line)
    (define-key vi-keymap (kbd "M-j") 'scroll-up-line)
    (define-key vi-keymap (kbd "M-k") 'scroll-down-line)
    (define-key vi-keymap (kbd "n M-i") 'org-clock-in-last)
    (define-key vi-keymap (kbd "M-q") 'nav/hydra/sexp-nav/body)
    (define-key vi-keymap (kbd "M-J") 'nav/join-line)
    (define-key vi-keymap (kbd "M-K") 'nav/join-up-line)
    (define-key vi-keymap (kbd "nM-P") 'org-delete-property)
    (define-key vi-keymap (kbd "M-r") 'll/replace-selection)
    (define-key vi-keymap (kbd "M-d") 'nav/dumb-jump-go)
    (define-key vi-keymap (kbd "M-H") 'sp-backward-up-sexp)
    (define-key vi-keymap (kbd "M-L") 'sp-up-sexp)
    ;; View control

    (define-key vi-keymap (kbd "i") 'exit-nav-modes/insert)

    ;; point movement
    (define-key vi-keymap (kbd "l") 'forward-char)
    (define-key vi-keymap (kbd "h") 'backward-char)
    (define-key vi-keymap (kbd "j") 'next-line)
    (define-key vi-keymap (kbd "k") 'previous-line)
    (define-key vi-keymap (kbd "e") 'nav/end-of-line)
    (define-key vi-keymap (kbd "a") 'nav/beginning-of-line)

    (define-key vi-keymap (kbd "w") 'forward-to-word)
    (define-key vi-keymap (kbd "b") 'backward-word)
    (define-key vi-keymap (kbd "q") 'forward-sexp)
    (define-key vi-keymap (kbd "Q") 'backward-sexp)

    (define-key vi-keymap (kbd ",") 'beginning-of-buffer)
    (define-key vi-keymap (kbd ".") 'end-of-buffer)
    (define-key vi-keymap (kbd "/") 'end-of-buffer);; I often mis-press instead of .
    (define-key vi-keymap (kbd "<") 'nav/beginning-of-buffer-and-exit)
    (define-key vi-keymap (kbd ">") 'nav/end-of-buffer-and-exit)
    (define-key vi-keymap (kbd "E") 'nav/end-of-line-and-exit)
    (define-key vi-keymap (kbd "A") 'nav/end-of-line-and-exit)
    (define-key vi-keymap (kbd "I") 'nav/beginning-of-line-and-exit)
    (define-key vi-keymap (kbd "g") 'avy-goto-char-timer)
    (define-key vi-keymap (kbd "G") 'avy-goto-line)
    (define-key vi-keymap (kbd "[") 'backward-sexp)
    (define-key vi-keymap (kbd "]") 'forward-sexp)

    ;;  mark and point control
    (define-key vi-keymap (kbd " ") 'set-mark-command)
    (define-key vi-keymap (kbd "xx") 'exchange-point-and-mark)
    (define-key vi-keymap (kbd "t") 'exchange-point-and-mark)
    (define-key vi-keymap (kbd "v") 'nav/mark-pop-and-jump)

    ;;  hydra menus
    (define-key vi-keymap (kbd "`") 'nav/hydra/master/body)
    (define-key vi-keymap (kbd "=") 'nav/hydra/registers/body)

    ;;  text manipulation
    (define-key vi-keymap (kbd "c") 'nav/change-command)
    (define-key vi-keymap (kbd "d") 'nav/delete-command)
    (define-key vi-keymap (kbd "y") 'nav/copy-command)
    (define-key vi-keymap (kbd "X") 'nav/swap-yank-command)

    (define-key vi-keymap (kbd "p") 'nav/paste-after)
    (define-key vi-keymap (kbd "P") 'nav/paste-before)

    (define-key vi-keymap (kbd "f") 'nav/jump-to-char)
    (define-key vi-keymap (kbd "F") 'nav/backward-jump-to-char)

    (define-key vi-keymap (kbd "o") 'nav/open-insert-next-line)
    (define-key vi-keymap (kbd "O") 'nav/open-insert-previous-line)
    (define-key vi-keymap (kbd "C") '[?c ?e])
    (define-key vi-keymap (kbd "D") '[?d ?e])
    (define-key vi-keymap (kbd "'") 'quoted-insert)

    ;;  search & replace
    (define-key vi-keymap (kbd "s") 'isearch-forward)
    (define-key vi-keymap (kbd "r") 'isearch-backward)
    (define-key vi-keymap (kbd "S") 'query-replace)
    (define-key vi-keymap (kbd "R") 'replace-regexp)

    ;;  other
    (define-key vi-keymap (kbd "u") 'undo)
    (define-key vi-keymap (kbd "xs") 'save-buffer)
    (define-key vi-keymap (kbd "z") 'save-buffer)
    (define-key vi-keymap (kbd "xff") 'counsel-find-files)
    (define-key vi-keymap (kbd "xfr") 'counsel-recentf);; not using kbd syntax because doesn't work
    (define-key vi-keymap (kbd "xB") 'ibuffer)
    (define-key vi-keymap (kbd "xh") 'mark-whole-buffer)
    (define-key vi-keymap (kbd "xag") 'inverse-add-global-abbrev);; add global abbrev
    (define-key vi-keymap (kbd "xal") 'inverse-add-mode-abbrev);; add mode abbrev
    (define-key vi-keymap (kbd "xd") 'dired)

    ;;  macros
    (define-key vi-keymap (kbd "mn") 'kmacro-start-macro)
    (define-key vi-keymap (kbd "md") 'kmacro-end-macro)
    (define-key vi-keymap (kbd "me") 'kmacro-end-and-call-macro)
    (define-key vi-keymap (kbd "mb") 'kmacro-bind-to-key)
    (define-key vi-keymap (kbd "ml") 'kmacro-edit-lossage);; view last keystrokes, turn into macro
    (define-key vi-keymap (kbd "mr") 'repeat);; to repeat last command
    (define-key vi-keymap (kbd "m5") 'nav/macro-5)
    (define-key vi-keymap (kbd "m6") 'nav/macro-6)
    (define-key vi-keymap (kbd "m7") 'nav/macro-7)
    (define-key vi-keymap (kbd "m8") 'nav/macro-8)
    (define-key vi-keymap (kbd "mm") 'nav/hydra/macros/body)

    ;;  org mode
    (define-key vi-keymap (kbd "nb") 'org-agenda)
    (define-key vi-keymap (kbd "ni") 'org-clock-in)
    (define-key vi-keymap (kbd "no") 'org-clock-out)
    (define-key vi-keymap (kbd "nc") 'org-columns)
    (define-key vi-keymap (kbd "nt") 'org-todo)
    (define-key vi-keymap (kbd "nk") 'org-cut-subtree)
    (define-key vi-keymap (kbd "nw") 'org-copy-subtree)
    (define-key vi-keymap (kbd "nn") 'nav/hydra/org/body)
    (define-key vi-keymap (kbd "nj") 'org-capture)
    (define-key vi-keymap (kbd "n.") 'org-time-stamp)
    (define-key vi-keymap (kbd "np") 'org-priority)
    (define-key vi-keymap (kbd "nP") 'org-set-property)
    (define-key vi-keymap (kbd "nL") 'org-insert-link)
    (define-key vi-keymap (kbd "nl") 'org-open-at-point);; "n l" to open org links
    (define-key vi-keymap (kbd "ns") 'org-schedule)
    (define-key vi-keymap (kbd "nd") 'org-deadline)
    (define-key vi-keymap (kbd "nI") 'org-toggle-inline-images)
    ;;  arguments
    (define-key vi-keymap (kbd "-") '[?\M--])
    (define-key vi-keymap (kbd "1") '[?\C-1])
    (define-key vi-keymap (kbd "2") '[?\C-2])
    (define-key vi-keymap (kbd "3") '[?\C-3])
    (define-key vi-keymap (kbd "4") '[?\C-4])
    (define-key vi-keymap (kbd "5") '[?\C-5])
    (define-key vi-keymap (kbd "6") '[?\C-6])
    (define-key vi-keymap (kbd "7") '[?\C-7])
    (define-key vi-keymap (kbd "8") '[?\C-8])
    (define-key vi-keymap (kbd "9") '[?\C-9])
    (define-key vi-keymap (kbd "0") '[?\C-0])
    vi-keymap))

(define-minor-mode vi-mode
  "Toggle vi-mode.
vi-mode is a modal editing minor mode. It allows use of emacs
functions via single keystrokes while the minor mode is active.
**Note**: Do not enable and disable vi-mode directly. Use
`toggle-vi-mode' instead.
vi-mode defines the following bindings:
\\{vi-mode-map}
"
  ;; initial value
  :lighter
  ;; indicator for mode line
  " vi"
  ;; minor mode bindings
  :keymap vi-mode-map
  :group 'vi)

(provide 'init-vi-mode)
