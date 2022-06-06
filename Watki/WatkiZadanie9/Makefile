###############################################################################
#                             Makefile do projektu                            #
#                                Watki Zadanie 9                              #
#                                                                             #
#  Jan Kwinta                                                     06.06.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run9, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=gnu99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=gnu99 -pedantic -pthread -D_POSIX_SOURCE
LIBflags = -lrt -lpthread
CO = gcc
LD = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY:

# Programy
Prog1 = threads9

# Zmienne
THREADSNUM =
SECTNUM = 


#==============================================================================
# ZALEZNOSCI:

$(Prog1).o: $(Prog1).c
	$(LD) $(Lflags) -c $^ $(LIBflags)

$(Prog1).x: $(Prog1).o
	$(CO) $(Cflags) -o $@ $^



#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(Prog1).x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run9
run9: $(Prog1).x
	./$(Prog1).x $(THREADSNUM) $(SECTNUM)


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
