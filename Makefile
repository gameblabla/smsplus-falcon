CC          = vc
CT60 	    = NO
# change compilation / linking flag options
PRGNAME  = smsplus_30.prg
CFLAGS		= -O4 -DMSB_FIRST -speed -sc -no-intz -unroll-all -notmpfile

ifeq ($(CT60), YES)
CFLAGS  += -D_CT60 -cpu=68040
PRGNAME  = smsplus_ct60.prg
endif
ifeq ($(CT60), NO)
CFLAGS  += -cpu=68030
endif

# Files to be compiled
SRC   = ./src/emu_main.c ./src/saves.c ./src/falcon.c ./src/render.c ./src/sms.c ./src/system.c ./src/vdp.c ./src/z80.c ./src/falcsys.c ./src/falcsysa.s ./src/vfastclear.s
# Rules to make executable
$(PRGNAME): $(SRC)  
	$(CC) +tos $(CFLAGS) -o $(PRGNAME) $^
clean:
	rm -f $(PRGNAME) *.o
