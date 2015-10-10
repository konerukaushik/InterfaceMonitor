#
#
#InterfaceMonitor Main MakeFile


CC=gcc
CFLAGS=-g -fPIC -lpcap -lpthread -Wall -I .  

DEPS= -I$(SRC)/include

OBJDIR=$(SRC)/obj
    

%.o: %.c $(DEPS)
	mkdir -p $(OBJDIR)
	$(CC) -c -o $(OBJDIR)/$@ $< $(CFLAGS)

#OBJ_FILES = $(OBJDIR)/InMn_main.o

OBJ_FILES = $(OBJDIR)/$(wildcard *.o)

SRC_FILES = $(wildcard *.c)

InMn: $(SRC_FILES)
	mkdir -p $(OBJDIR)
	$(CC) -o $(OBJDIR)/$@ $^ $(CFLAGS) $(DEPS)

