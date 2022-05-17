###############################################################################
#							  Makefile do projektu							  #
#							   Semafory Zadanie 6							  #
#																			  #
#  Jan Kwinta													  04.05.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run6, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=c99 -pedantic -c -g
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))

#==============================================================================
# ZMIENNE:

R = realisator.x
PROCNUM = 
SECTNUM = 


#==============================================================================
# ZALEZNOSCI:

semaph_lib.o: semaph_lib.h semaph_lib.c
	$(CO) $(Lflags) semaph_lib.c

realisator.x: realisator.c semaph_lib.o
	$(CO) $(Cflags) -o $@ $^
	
duplicator.x: duplicator.c semaph_lib.o realisator.x
	$(CO) $(Cflags) -o $@ duplicator.c semaph_lib.o


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: duplicator.x realisator.x semaph_lib.o


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run6
run6: duplicator.x
	./duplicator.x $(R) $(PROCNUM) $(SECTNUM)
	rm numer.txt


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
