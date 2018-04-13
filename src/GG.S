* ###########################################################################
* #                                                                         #
* #  'Screens Pain' coded 1993 by Chris of AURA & Scandion of the Mugwumps  #
* #                                                                         #
* #                 --- It's an INDEPENDENT-Product ---                     #
* #                                                                         #
* ###########################################################################
* Monitor: VGA
* 160*144, True Color, 60.0 Hz, 31470 Hz
	machine	68030
	public	_VGAGG

_VGAGG:	; _FS_Vmode must be set !
        MOVE.L   #$FE00CB,$FFFF8282.W
        MOVE.L   #$2802CF,$FFFF8286.W
        MOVE.L   #$FFA000DA,$FFFF828A.W
        MOVE.L   #$20D0201,$FFFF82A2.W
        MOVE.L   #$170011,$FFFF82A6.W
        MOVE.L   #$2510207,$FFFF82AA.W
        MOVE.W   #$200,$FFFF820A.W
        MOVE.W   #$81,$FFFF82C0.W
        CLR.W    $FFFF8266.W
        MOVE.W   #$100,$FFFF8266.W
        MOVE.W   #$1,$FFFF82C2.W
        MOVE.W   #$A0,$FFFF8210.W
	rts
