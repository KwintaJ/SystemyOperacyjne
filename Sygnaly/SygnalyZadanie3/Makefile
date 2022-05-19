###############################################################################
#                             Makefile do projektu                            #
#                                    Sygnaly                                  #
#                                                                             #
#  Jan Kwinta                                                     22.03.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run3A, run3B, run3C, clean, tar

#==============================================================================
# Kompilator i inne:

Cflags = -O2 -Wall -pedantic -std=c99 -D_POSIX_C_SOURCE
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
Prog3A = signalsA
Prog3B = signalsB
Prog3C = signalsC

# Headery
H1 = argErrors


#==============================================================================
# ZALEZNOSCI:

$(Prog3A).x: $(Prog3A).c $(H1).h
	$(CO) $(Cflags) -o $@ $^ 

$(Prog3B).x: $(Prog3B).c $(Prog3A).x $(H1).h
	$(CO) $(Cflags) -o $@ $(Prog3B).c $(H1).h

$(Prog3C).x: $(Prog3C).c $(Prog3A).x $(H1).h
	$(CO) $(Cflags) -o $@ $(Prog3C).c $(H1).h


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog3A).x $(Prog3B).x $(Prog3C).x


#==============================================================================
# KOMPILACJA kazdego programu z osobna bez uruchamiania

.PHONY: prog3A prog3B prog3C

prog3A: $(Prog3A).x

prog3B: $(Prog3B).x

prog3C: $(Prog3C).x


#==============================================================================
# Sprzataczka
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
