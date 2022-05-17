###############################################################################
#							  Makefile do projektu							  #
#								ProcesyZadanie2								  #
#																			  #
#  Jan Kwinta													  09.03.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run2

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -pedantic -std=c99
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
Prog2 = identifiers2
SubP2 = extPrint

# Headery
H1 = printIDs


#==============================================================================
# ZALEZNOSCI:

$(Prog2).x: $(Prog2).c $(SubP2).x $(H1).h
	$(CO) $(Cflags) -o $@ $(Prog2).c $(H1).h

$(SubP2).x: $(SubP2).c $(H1).h 
	$(CO) $(Cflags) -o $@ $^


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog2).x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run2

run2: $(Prog2).x
	./$(Prog2).x


#==============================================================================
# Sprzataczka
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
