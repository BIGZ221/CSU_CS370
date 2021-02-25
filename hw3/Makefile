ASSIGNMENT = HW2
CC = gcc
FILES = Starter.c Prime.c Fibb.c Total.c CharacterReader.c
EXE_FILES = Starter Prime Fibb Total CharacterReader
TAR_NAME = Zachary-Fuchs-$(ASSIGNMENT).tar
CWARNINGS = -Wall -Wextra
all: clean $(EXE_FILES)

Starter:
	$(CC) $(CWARNINGS) -o Starter -lrt Starter.c
Prime:
	$(CC) $(CWARNINGS) -o Prime -lrt Prime.c
Fibb:
	$(CC) $(CWARNINGS) -o Fibb -lrt Fibb.c
Total:
	$(CC) $(CWARNINGS) -o Total -lrt Total.c
CharacterReader:
	$(CC) $(CWARNINGS) -o CharacterReader -lrt CharacterReader.c

build: all

package:
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f *.o $(EXE_FILES)
