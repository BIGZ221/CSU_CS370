ASSIGNMENT = HW1
CC = gcc
FILES = Executor.c Starter.c Executor.h
OUT_EXE = Starter
TAR_NAME = Zachary-Fuchs-$(ASSIGNMENT).tar
CWARNINGS = -Wall -Wextra 
build:
	$(CC) $(CWARNINGS) -o $(OUT_EXE) $(FILES)
package:
	tar cvzf $(TAR_NAME) $(FILES) Makefile HW1README.txt
clean:
	rm -f $(OUT_EXE)
