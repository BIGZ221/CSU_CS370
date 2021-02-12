ASSIGNMENT = HW2
CC = gcc
FILES = Starter.c Prime.c Fibb.c Total.c
EXE_FILES = Starter Prime Fibb Total
TAR_NAME = Zachary-Fuchs-$(ASSIGNMENT).tar
CWARNINGS = -Wall -Wextra
default: all
all: Starter Prime Fibb Total
build:
	$(CC) $(CWARNINGS) $(FILES)
package:
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f $(EXE_FILES)
