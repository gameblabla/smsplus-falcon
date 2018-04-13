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
	public	_RGBSMS_256192

_RGBSMS_256192:	; _FS_Vmode must be set !
        MOVE.L   #$620046,$FFFF8282.W
        MOVE.L   #$A024D,$FFFF8286.W
        MOVE.L   #$A6004B,$FFFF828A.W
        MOVE.L   #$41903FF,$FFFF82A2.W
        MOVE.L   #$3F003F,$FFFF82A6.W
        MOVE.L   #$1BF0415,$FFFF82AA.W
        MOVE.W   #$200,$FFFF820A.W
        MOVE.W   #$185,$FFFF82C0.W
        CLR.W    $FFFF8266.W
        MOVE.W   #$100,$FFFF8266.W
        MOVE.W   #$0,$FFFF82C2.W
        MOVE.W   #$100,$FFFF8210.W
	rts
