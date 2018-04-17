	machine	68060
	public	_VFastClear32
_VFastClear32:	; Multiple of 32
; a0 = dst
; d0 = size
; d1 = data
	movem.l	d3-d6,-(a7)
	add.l	d0,a0
	lsr.l	#5,d0
	subq.l	#1,d0
	move.l	d1,d2
	move.l	d1,d3
	move.l	d1,d4
	move.l	d1,d5
	move.l	d1,d6
	move.l	d1,a1
	move.l	d1,a2
.copy:	movem.l	d1-d6/a1-a2,-(a0)
	dbra	d0,.copy
	movem.l	(a7)+,d3-d6
	rts
