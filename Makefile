BUILDIR=./build
SUBNET_EXE=$(BUILDIR)/subnet.o
.PHONY: all clean dir subnet2 test

all: subnet

dir:
	@mkdir -p build

subnet: dir
	@cd subnet && $(MAKE)

test: subnet
	@$(SUBNET_EXE)

clean:
	@cd subnet && $(MAKE) clean
