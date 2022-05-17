###############################################################################
#                            Makefile do projektu                             #
#                          Pamiec dzielona Zadanie 7                          #
#                                                                             #
# Jan Kwinta                                                       DD.MM.YYYY #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run7, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=c99 -pedantic -c -g
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
MAIN = shm7
P = producer
C = consumer

# Headery
H1 = semaph_lib
H2 = memory_lib

# Pliki
IN = towar.txt
OUT = 


#==============================================================================
# ZALEZNOSCI:

$(H1).o: $(H1).h $(H1).c
	$(CO) $(Lflags) $(H1).c

$(H2).o: $(H2).h $(H2).c
	$(CO) $(Lflags) $(H2).c

$(P).x: $(P).c $(H1).o $(H2).o
	$(CO) $(Cflags) -o $@ $^

$(C).x: $(C).c $(H1).o $(H2).o
	$(CO) $(Cflags) -o $@ $^

$(MAIN).x: $(MAIN).c $(P).x $(C).x $(H1).o $(H2).o
	$(CO) $(Cflags) -o $@ $(MAIN).c $(H1).o $(H2).o


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(MAIN).x

#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run7
run7: $(MAIN).x
	./$(MAIN).x $(IN) $(OUT)
	#diff $(IN) $(OUT)
	#rm $(OUT)


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
