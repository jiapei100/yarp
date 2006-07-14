(declare (uses cyarp))

(Network-init)

(define p (new-BufferedPortBottle))

(BufferedPortBottle-open p "/chicken")

(define top 100)
(do ((i 1 (+ i 1)))
    ((> i top) #f) ; return #f at the end
  (let ((bottle (BufferedPortBottle-prepare p)))
    (Bottle-clear bottle)
    (Bottle-addString bottle "count")
    (Bottle-addInt bottle i)
    (Bottle-addString bottle "of")
    (Bottle-addInt bottle top)
    (display "Sending ")
    (display (Bottle-toString bottle))
    (newline)
    (BufferedPortBottle-write p)
    (Time-delay 0.5)))

(Network-fini)

