BUILDIR=./build
SUBNET_EXE=$(BUILDIR)/subnet.o
.PHONY: all clean subnet2 test

all: subnet2

subnet2:
	@cd subnet2 && $(MAKE)

test: subnet2
	@$(SUBNET_EXE)

clean:
	@cd subnet2 && $(MAKE) clean
