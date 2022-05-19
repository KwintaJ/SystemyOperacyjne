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

Cflags = -O2 -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE -g
Aflags = rsv
LDLIBS = -lm -lrt
CO = gcc
LD = $(CO)
AR = ar
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))


#==============================================================================
# NAZWY PLIKOW:

# Programy
MAIN = shm7
P = producer
C = consumer

# Pliki
IN = towar.txt
OUT = out.txt

# Bibilioteki
LIB_DIR = ./lib
LIB_NAME = memory_lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LIB_OBJ = $(LIB_NAME).o

# Pliki obiektowe
OBJ_MAIN = $(MAIN).o
OBJ_P = $(P).o
OBJ_C = $(C).o

# Pliki exec
EXEC_MAIN_static = $(MAIN)s.x
EXEC_P_static = $(P)s.x
EXEC_C_static = $(C)s.x

EXEC_MAIN_dynamic1 = $(MAIN)d1.x
EXEC_P_dynamic1 = $(P)d1.x
EXEC_C_dynamic1 = $(C)d1.x

EXEC_MAIN_dynamic2 = $(MAIN)d2.x
EXEC_P_dynamic2 = $(P)d2.x
EXEC_C_dynamic2 = $(C)d2.x

#==============================================================================
# TWORZENIE BIBLIOTEK

$(LIB_OBJ): $(LIB_NAME).c
	$(CO) $(Cflags) -c $<

# Statyczna
$(LIB_STAT): $(LIB_OBJ)
	$(AR) $(Aflags) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Dynamiczna (dzielona)
$(LIB_SHAR): $(LIB_OBJ)
	$(LD) -shared $(Lflags) -o $@ $(LIB_OBJ)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)


#==============================================================================
# ZALEZNOSCI:

# Program glowny
$(OBJ_MAIN): $(MAIN).c
	$(CO) $(Cflags) -c $<

$(EXEC_MAIN_static): $(OBJ_MAIN) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_MAIN) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC_MAIN_dynamic1): $(OBJ_MAIN) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_MAIN) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)

$(EXEC_MAIN_dynamic2): $(OBJ_MAIN) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_MAIN) -L$(LIB_DIR) -l$(LIB_NAME)

# Program producenta
$(OBJ_P): $(P).c
	$(CO) $(Cflags) -c $<

$(EXEC_P_static): $(OBJ_P) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_P) -L$(LIB_DIR) -l$(LIB_NAME)

$(EXEC_P_dynamic1): $(OBJ_P) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_P) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)

$(EXEC_P_dynamic2): $(OBJ_P) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_P) -L$(LIB_DIR) -l$(LIB_NAME)

# Program konsumenta
$(OBJ_C): $(C).c
	$(CO) $(Cflags) -c $<

$(EXEC_C_static): $(OBJ_C) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_C) -L$(LIB_DIR) -l$(LIB_NAME)

$(EXEC_C_dynamic1): $(OBJ_C) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_C) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)

$(EXEC_C_dynamic2): $(OBJ_C) $(LIB_SHAR)
	$(LD) $(Lflags) -o $@ $(OBJ_C) -L$(LIB_DIR) -l$(LIB_NAME)



#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: $(EXEC_MAIN_static) $(EXEC_MAIN_dynamic1) $(EXEC_MAIN_dynamic2) $(EXEC_P_static) $(EXEC_P_dynamic1) $(EXEC_P_dynamic2) $(EXEC_C_static) $(EXEC_C_dynamic1) $(EXEC_C_dynamic2)

#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run7static run7dynamic1 run7dynamic2

run7static: $(EXEC_MAIN_static) $(EXEC_P_static) $(EXEC_C_static)
	./$(EXEC_MAIN_static) $(IN) $(OUT) s
	#diff $(IN) $(OUT)
	#rm $(OUT)

run7dynamic1: $(EXEC_MAIN_dynamic1) $(EXEC_P_dynamic1) $(EXEC_C_dynamic1)
	./$(EXEC_MAIN_dynamic1) $(IN) $(OUT) d1
	#diff $(IN) $(OUT)
	#rm $(OUT)

run7dynamic2: $(EXEC_MAIN_dynamic2) $(EXEC_P_dynamic2) $(EXEC_C_dynamic2)
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC_MAIN_dynamic2) $(IN) $(OUT) d2
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
