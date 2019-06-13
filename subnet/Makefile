CC=gcc
DBG_CFLAGS=-g -Wall -Wextra
CFLAGS=-Wall -Wextra
MATHLIB=-lm
BUILDIR=../build

all: subnet

subnet: ip_maths.c test.c
ifeq ($(NDEBUG), )
	@$(CC) $(CFLAGS) -o $(BUILDIR)/subnet ip_maths.c test.c $(MATHLIB)
else
	@$(CC) $(DBG_CFLAGS) -o $(BUILDIR)/subnet ip_maths.c test.c $(MATHLIB)
endif

clean:
	@rm -rf $(BUILDIR)/*
