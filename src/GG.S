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
        MOVE.L   #$C6008D,$FFFF8282.W
        MOVE.L   #$15004F,$FFFF8286.W
        MOVE.L   #$97,$FFFF828A.W
        MOVE.L   #$41903FF,$FFFF82A2.W
        MOVE.L   #$3F003F,$FFFF82A6.W
        MOVE.L   #$15F0415,$FFFF82AA.W
        MOVE.W   #$200,$FFFF820A.W
        MOVE.W   #$186,$FFFF82C0.W
        CLR.W    $FFFF8266.W
        MOVE.W   #$100,$FFFF8266.W
        MOVE.W   #$8,$FFFF82C2.W
        MOVE.W   #$A0,$FFFF8210.W
	rts
