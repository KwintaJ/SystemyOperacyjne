###############################################################################
#                             Makefile do projektu                            #
#                                     ...                                     #
#                                                                             #
#  Jan Kwinta                                                     DD.MM.YYYY  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run1, ...

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -pedantic -std=c99
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
Prog1 = 

# Headery
H1 = 


#==============================================================================
# ZALEZNOSCI:

$(Prog1).x: $(Prog1).c $(H1).h
	$(CO) $(Cflags) -o $@ $^


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog1).x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run1
run1: $(Prog1).x
	./$(Prog1).x


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
