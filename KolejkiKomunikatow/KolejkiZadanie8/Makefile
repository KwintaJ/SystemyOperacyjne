###############################################################################
#                             Makefile do projektu                            #
#                        Kolejki komunikatow Zadanie 8                        #
#                                                                             #
#  Jan Kwinta                                                     DD.MM.YYYY  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run8, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=gnu99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=gnu99 -pedantic -pthread -D_POSIX_SOURCE
LIBflags = -lrt
CO = gcc
LD = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
Prog1 = client
Prog2 = server

# Biblioteki
Lib1 = mqueue_lib

#==============================================================================
# ZALEZNOSCI:

%.o: %.c
	$(LD) $(Lflags) -c $<

$(Prog1).x: $(Prog1).c $(Lib1).o
	$(CO) $(Cflags) -o $@ $< $(Lib1).o $(LIBflags)

$(Prog2).x: $(Prog2).c $(Lib1).o
	$(CO) $(Cflags) -o $@ $< $(Lib1).o $(LIBflags)


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog1).x $(Prog2).x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run8
run8: $(Prog1).x $(Prog2).x
	xterm -hold -title $(Prog2) -bg red -e ./$(Prog2).x &
	xterm -hold -title $(Prog1)1 -bg green -e ./$(Prog1).x &
	xterm -hold -title $(Prog1)2 -bg green -e ./$(Prog1).x &
	xterm -hold -title $(Prog1)3 -bg green -e ./$(Prog1).x &


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )