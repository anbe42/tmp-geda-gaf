;;; gEDA - GPL Electronic Design Automation
;;; gnetlist - gEDA Netlist
;;; Copyright (C) 1998-2010 Ales Hvezda
;;; Copyright (C) 1998-2010 gEDA Contributors (see ChangeLog for details)
;;;
;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 2 of the License, or
;;; (at your option) any later version.
;;;
;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with this program; if not, write to the Free Software
;;; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

;;----------------------------------------------------------------------
;; The below functions added by SDB in Sept 2003 to support command-line flag
;; processing.
;;----------------------------------------------------------------------

;;---------------------------------------------------------------
;;  debug-spew
;;  Wrapper which spews debug messages if -v flag is set, otherwise
;;  does nothing.
;;  Calling form:  (debug-spew "verbose debug text")
;;--------------------------------------------------------------
(define debug-spew
  (lambda (debug-string)
    (if (calling-flag? "verbose_mode" (gnetlist:get-calling-flags))
        (display debug-string) 
)))


;;---------------------------------------------------------------
;; calling-flag?
;;   Returns #t or #f depending upon the corresponding flag
;;   was set in the calling flags given to gnetlist.  
;;   9.7.2003 -- SDB.
;;---------------------------------------------------------------
(define calling-flag?
  (lambda (searched-4-flag calling-flag-list)

    (if (null? calling-flag-list)
          '#f                                             ;; return #f if null list -- sort_mode not found.
          (let* ((calling-pair (car calling-flag-list))   ;; otherwise look for sort_mode in remainder of list.
                 (calling-flag (car calling-pair))
                 (flag-value (cadr calling-pair))  )

            ;; (display (string-append "examining calling-flag = " calling-flag "\n" ))
            ;; (display (string-append "flag-value = " (if flag-value "true" "false") "\n" ))

            (if (string=? calling-flag searched-4-flag)
                flag-value                                                 ;; return flag-value if sort_mode found
                (calling-flag? searched-4-flag (cdr calling-flag-list))    ;; otherwise recurse until sort_mode is found
            )  ;; end if  
          )  ;; end of let*
     )  ;; end of if (null?
))

;;-------------  End of SDB's command line flag functions ----------------

;; Support functions

;;  This fcn should behave exactly the same as C's strncmp fcn.
;;  It compares two strings from the start up to a user-defined end
;;  char count.  It also checks that the string compare was successful through
;;  the end char count (i.e. that both strings are >= "end").  This
;;  guards against returning #t when comparing "unconnected_pin-23" to "unc"
;;  (over 15 chars).
;;  I needed to write this because substring chokes when the string arg is
;;  shorter than the end arg.
;;  1.4.2006 -- SDB.
(define strncmp?
  (lambda (string1 string2 end)
    (and 
     (string-ci=? (substring string1 0 (min end (string-length string1)))
		  (substring string2 0 (min end (string-length string2))))
     (>= (min (string-length string1) (string-length string2)) end)
    )
  )
)


;;  This fcn returns the first len characters of the string str.  If
;;  str has less than len characters, it returns the whole string
;;  (but doesn't choke)
(define safe-string-head
  (lambda (str len)
    (substring str 0 (min len (string-length str)))
  )
)

;;
;; Given a uref, returns the device attribute value (unknown if not defined)
;;
(define get-device
   (lambda (package)
      (gnetlist:get-package-attribute package "device")))

;; Shorthand for get component values
(define get-value
   (lambda (package)
      (gnetlist:get-package-attribute package "value")))

(define get-component-text
   (lambda (package)
      (let ((value (gnetlist:get-package-attribute package "value"))
            (label (gnetlist:get-package-attribute package "label"))
            (device (gnetlist:get-package-attribute package "device")))
         (if (not (string=? "unknown" value))
            value
            (if (not (string=? "unknown" label))
               label
               device)))))


;; return all pins for a particular package 
(define pins
   (lambda (package)
      (gnetlist:get-pins package)))

;; this is really crude, but I'm tired... :)
(define display-nl
   (lambda (list)
      (display list) 
      (newline)))


;; ah.. wonder what use this is...
(define display-pin
   (lambda (pin-list)
      (for-each display-nl pin-list)))


;; ha. I'm playing with scheme here.. don't mind me
(define display-all-pins
   (lambda ()
      (for-each display-pin all-pins)))


;; another misc function
(define print-packages
   (lambda (plist)
      (for-each display-nl plist)))

;; ETTUS
;; find-device
;; Usage:  (find-device packages devicename)
;; Returns the first package which matches the devicename
(define find-device
   (lambda (components devicename)
      (if (not (null? components))       
         (if (string=? devicename (get-device (car components)))
            (car components)
            (find-device (cdr components) devicename))))) 


;; ETTUS
;; find-devices
;; Usage:  (find-devices packages devicename '())
;; Returns a list of packages which match the device name
(define find-devices
   (lambda (components devicename list)
      (if (not (null? components))
         (if (string=? devicename (get-device (car components)))
            (find-devices (cdr components)
                                devicename
                                (cons (car components) list))
            (find-devices (cdr components)
                                devicename
                                list))
         list)))

;; ETTUS
;; contains?
;; Usage (contains? list item)
;; True if the list contains the item, according to string=?
(define contains?
   (lambda (ls item)
      (cond
         ((null? ls) #f)
         ((string=? item (car ls)) #t)
         (#t (contains? (cdr ls) item)))))

;; ETTUS
;; Usage: (number-nets all-unique-nets 1)
;; Returns a list of pairs of form (netname . number)
(define number-nets
   (lambda (nets number)
      (if (null? nets)
         '()
         (if (string=? "GND" (car nets))
            (cons (cons "GND" 0) (number-nets (cdr nets) number))
            (cons
               (cons (car nets) number)
               (number-nets (cdr nets)(+ number 1)))))))

;; ETTUS
;; Usage: (get-net-number netname numberlist)
;; numberlist should be from (number-nets) above
;; Returns the number corresponding to the net
(define get-net-number
   (lambda (netname numberlist)
      (if (not (null? numberlist))
         (if (string=? netname (car (car numberlist)))
            (cdr (car numberlist))
            (get-net-number netname (cdr numberlist))))))

;; 
;; Useful output functions contributed by Andrew Bardsley
;;
(define (print-to-port port . l)
    (for-each (lambda (elem) (display elem port)) l))

(define (print . l)
    (apply print-to-port (cons (current-output-port) l)))

;;
;; Wrap a string into lines no longer than wrap-length
;; wrap-char is put on the end-of-the-wrapped-line, before the return
;; (from Stefan Petersen)
(define (gnetlist:wrap string-to-wrap wrap-length wrap-char)
  (if (> wrap-length (string-length string-to-wrap))
      string-to-wrap ; Last snippet of string
      (let ((pos (string-rindex string-to-wrap #\space 0 wrap-length)))
	(cond ((not pos)
	       (display "Couldn't wrap string  at requested position\n")
	       " Wrap error!")
	      (else
	       (string-append 
		(substring string-to-wrap 0 pos) 
		wrap-char
		"\n "
		(gnetlist:wrap (substring string-to-wrap (+ pos 1)) wrap-length wrap-char)))))))

;; example use
; (define (run-test test-string wrap-len)
;   (display (string-append "Wrapping \"" test-string "\" into "))
;   (display wrap-len)
;   (newline)
;   (display (gnetlist:wrap test-string wrap-len " \\"))
;   (newline)
;   (newline))

; (run-test "one two three four five six seven eight nine ten" 5)
; (run-test "one two three four five six seven eight nine ten" 10)
; (run-test "one two three four five six seven eight nine ten" 20)

;; determine the uref to use for a particular OBJECT
(define (gnetlist:get-uref object)
  ; Returns first value of first attrib found with given name, or #f.
  (define (attrib-first-value object name)
    (let ((attrib-lst (get-attrib-value-by-attrib-name object name)))
      (if (null? attrib-lst) #f (car attrib-lst))))
  ; Handler if we find uref=
  (define (handle-uref value)
    (simple-format (current-output-port)
                   "WARNING: Found uref=~A" value)
    (newline)
    (simple-format (current-output-port)
                   "uref= is deprecated, please use refdes=~A" value)
    (newline)
    value)

  ; Actually find attribute: check refdes, then uref, then return #f.
  (cond
   ((attrib-first-value object "refdes") => (lambda (x) x))
   ((attrib-first-value object "uref") => handle-uref)
   (else #f)))

;; define the default handler for get-uref
(define get-uref gnetlist:get-uref)
