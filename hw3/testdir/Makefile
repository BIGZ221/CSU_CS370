ASSIGNMENT = HW3
CC = gcc
FILES = Starter.c Prime.c Fibb.c Total.c CharacterReader.c
EXE_FILES = Starter Prime Fibb Total CharacterReader
TAR_NAME = Zachary-Fuchs-$(ASSIGNMENT).tar
CWARNINGS = -Wall -Wextra
all: clean $(EXE_FILES)

Starter:
	$(CC) $(CWARNINGS) -o Starter Starter.c -lrt
Prime:
	$(CC) $(CWARNINGS) -o Prime Prime.c -lrt
Fibb:
	$(CC) $(CWARNINGS) -o Fibb Fibb.c -lrt
Total:
	$(CC) $(CWARNINGS) -o Total Total.c -lrt
CharacterReader:
	$(CC) $(CWARNINGS) -o CharacterReader CharacterReader.c -lrt

build: all

package:
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f *.o $(EXE_FILES)
