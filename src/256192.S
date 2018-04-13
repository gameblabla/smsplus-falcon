* ###########################################################################
* #                                                                         #
* #  'Screens Pain' coded 1993 by Chris of AURA & Scandion of the Mugwumps  #
* #                                                                         #
* #                 --- It's an INDEPENDENT-Product ---                     #
* #                                                                         #
* ###########################################################################
* Monitor: VGA
* 256*192, True Color, 60.0 Hz, 31470 Hz
	machine	68030
	public	_VGA256192

_VGA256192:	; _FS_Vmode must be set !
        MOVE.L   #$C6008D,$FFFF8282.W
        MOVE.L   #$15029F,$FFFF8286.W
        MOVE.L   #$FFB80097,$FFFF828A.W
        MOVE.L   #$41903FF,$FFFF82A2.W
        MOVE.L   #$3F00A1,$FFFF82A6.W
        MOVE.L   #$3A10415,$FFFF82AA.W
        MOVE.W   #$200,$FFFF820A.W
        MOVE.W   #$186,$FFFF82C0.W
        CLR.W    $FFFF8266.W
        MOVE.W   #$100,$FFFF8266.W
        MOVE.W   #$9,$FFFF82C2.W
        MOVE.W   #$100,$FFFF8210.W
	rts
