###############################################################################
#                             Makefile do projektu                            #
#                               Procesy Zadanie 1                             #
#                                                                             #
#  Jan Kwinta                                                     09.03.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run1A, run1B, run1C, run1D, run1E

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -pedantic -std=c99
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
Prog1A = identifiersA
Prog1B = identifiersB
Prog1C = identifiersC
Prog1D = identifiersD
Prog1E = identifiersE

# Headery
H1 = printIDs
H2 = forkProc


#==============================================================================
# ZALEZNOSCI:

$(Prog1A).x: $(Prog1A).c $(H1).h
	$(CO) $(Cflags) -o $@ $^

$(Prog1B).x: $(Prog1B).c $(H1).h $(H2).h
	$(CO) $(Cflags) -o $@ $^

$(Prog1C).x: $(Prog1C).c $(H1).h $(H2).h
	$(CO) $(Cflags) -o $@ $^

$(Prog1D).x: $(Prog1D).c $(H1).h
	$(CO) $(Cflags) -o $@ $^

$(Prog1E).x: $(Prog1E).c $(H1).h
	$(CO) $(Cflags) -o $@ $^


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog1A).x $(Prog1B).x $(Prog1C).x $(Prog1D).x $(Prog1E).x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run1A run1B run1C run1D run1E

run1A: $(Prog1A).x
	./$(Prog1A).x

run1B: $(Prog1B).x
	./$(Prog1B).x

run1C: $(Prog1C).x
	./$(Prog1C).x

run1D: $(Prog1D).x
	./$(Prog1D).x

run1E: $(Prog1E).x
	./$(Prog1E).x


#==============================================================================
# Sprzataczka
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
