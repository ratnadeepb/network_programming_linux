CC=gcc
CFLAGS=-g -Wall -Wextra
MATHLIB=-lm
BUILDIR=../build

all: subnet

subnet: ip_maths.c test.c
	@$(CC) $(CFLAGS) -o $(BUILDIR)/subnet ip_maths.c test.c $(MATHLIB)

clean:
	@rm -rf $(BUILDIR)/*
