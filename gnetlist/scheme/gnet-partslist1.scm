; Copyright (C) 2001-2010 MIYAMOTO Takanori
; gnet-partslist1.scm
; 
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

; The /'s may not work on win32
(load (string-append gedadata "/scheme/gnet-partslist-common.scm"))

(define partslist1:write-top-header
  (lambda (port)
    (display ".START\n" port)
    (display "..refdes\tdevice\tvalue\tfootprint\tquantity\n" port)))

(define (partslist1:write-partslist ls port)
  (if (null? ls)
      '()
      (begin (write-one-row (append (car ls) (list 1)) "\t" "\n" port)
	     (partslist1:write-partslist (cdr ls) port))))

(define partslist1:write-bottom-footer
  (lambda (port)
    (display ".END" port)
    (newline port)))

(define partslist1
  (lambda (output-filename)
    (let ((port (open-output-file output-filename))
	  (parts-table (marge-sort-with-multikey (get-parts-table packages) '(0 1 2 3))))
      (partslist1:write-top-header port)
      (partslist1:write-partslist parts-table port)
      (partslist1:write-bottom-footer port)
      (close-output-port port))))
