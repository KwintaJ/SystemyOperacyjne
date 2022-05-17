###############################################################################
#							  Makefile do projektu							  #
#								 PotokiZadanie5								  #
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

PIPENAME = pFIFO

# Argumenty wywolania programu

P = 
C = consumer.txt

#==============================================================================
# ZALEZNOSCI:

progProducer.x: progProducer.c
	$(CO) $(Cflags) -o $@ progProducer.c

progConsumer.x: progConsumer.c
	$(CO) $(Cflags) -o $@ progConsumer.c

pipes5A.x: pipes5A.c progProducer.x progConsumer.x
	$(CO) $(Cflags) -o $@ pipes5A.c

#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: pipes5A.x progProducer.x progConsumer.x


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run5A run5B
run5A: pipes5A.x
	./pipes5A.x $(P) $(C) $(PIPENAME)
	diff -s $(P) $(C)
	rm $(C)

run5B: progProducer.x progConsumer.x
	touch $(C)
	mkfifo -m 0644 $(PIPENAME)
	xterm -hold -title progProducer -e ./progProducer.x $(P) $(PIPENAME) & xterm -hold -title progConsumer -e ./progConsumer.x $(C) $(PIPENAME) 
	rm $(PIPENAME)
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
