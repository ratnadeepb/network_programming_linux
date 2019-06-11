CC=gcc
CFLAGS=-Wall -Wextra
BUILDIR=../build

subnet: ip_maths.c test.c
	@$(CC) -o $(BUILDIR)/subnet ip_maths.c test.c -lm

clean:
	@rm -rf $(BUILDIR)/*
