all:
	@make -C src all

clean:
	@make -C src clean

install:
	@make -C src install

precompile:
	@make -C src precompile

.PHONY: all clean install precompile

