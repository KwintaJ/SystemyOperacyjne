###############################################################################
#							  Makefile do projektu							  #
#								 PotokiZadanie4								  #
#																			  #
#  Jan Kwinta													  05.04.2022  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run4, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -pedantic -std=c99
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# ZMIENNE:

# Argumenty wywolania programu

P = 
C = 

#==============================================================================
# ZALEZNOSCI:

progProducer.x: progProducer.c
	$(CO) $(Cflags) -o $@ progProducer.c

progConsumer.x: progConsumer.c
	$(CO) $(Cflags) -o $@ progConsumer.c

pipes4.x: pipes4.c progProducer.x progConsumer.x
	$(CO) $(Cflags) -o $@ pipes4.c


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: pipes4.x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run4
run4: pipes4.x
	./pipes4.x $(P) $(C)
	diff -s $(P) $(C)
	rm $(C)

#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out consumer.txt; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
