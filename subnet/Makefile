CC=gcc
DBG_CFLAGS=-g -Wall -Wextra
CFLAGS=-DNDEBUG=1 -Wall -Wextra
MATHLIB=-lm
DEBUGFILE=../common/dbg.h
BUILDIR=../build
OBJECTS=$(BUILDIR)/subnet.o

.PHONY: clean all

all: $(OBJECTS)

$(OBJECTS): $(DEBUGFILE)

$(BUILDIR)/subnet.o: ip_maths.c test.c
ifeq ($(NDEBUG), )
	@echo Building Release version of subnet
	@$(CC) $(CFLAGS) $^ -o $@ $(MATHLIB)
else
	@echo Building Debug version of subnet
	@$(CC) $(DBG_CFLAGS) $^ -o $@ $(MATHLIB)
endif

clean:
ifeq (,$(wildcard $(OBJECTS)))
	@echo "$(OBJECTS) don't exist"
else
	@echo removing $(OBJECTS)
	@rm -rf $(OBJECTS)
endif
