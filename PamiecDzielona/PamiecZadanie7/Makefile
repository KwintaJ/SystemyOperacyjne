###############################################################################
#							  Makefile do projektu							  #
#							Pamiec Dzielona Zadanie 7						  #
#																			  #
#  Jan Kwinta													  DD.MM.YYYY  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run7, clean, tar

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
# PLIKI:

IN = towar.txt
OUT = out.txt


#==============================================================================
# ZALEZNOSCI:

%.o: %.c
	$(LD) $(Lflags) -c $<

shm7.x: shm7.o memory_lib.c
	$(CO) $(Cflags) -o $@ $^ memory_lib.h $(LIBflags)

producer.x: producer.o memory_lib.c
	$(CO) $(Cflags) -o $@ $^ memory_lib.h $(LIBflags)

consumer.x: consumer.o memory_lib.c
	$(CO) $(Cflags) -o $@ $^ memory_lib.h $(LIBflags)


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: shm7.x producer.x consumer.x
	

#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run7
run7: shm7.x producer.x consumer.x
	./shm7.x $(IN) $(OUT)
	diff -s $(IN) $(OUT)
	rm $(OUT)


#==============================================================================
# Sprzataczka

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
