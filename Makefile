###
#
# Main Makefile to Invoke Internal Folders
# Author:  Koneru, Kaushik
# Email:   konerukaushik@gmail.com
# Project: Interface Monitor
###

export SRC=$(PWD)

CODE_DIR= src

PHONY: InMn

InMn:
	$(MAKE) -C $(CODE_DIR)
	
clean:
	rm -rf obj
