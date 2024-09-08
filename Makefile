# ----------------------------
# Makefile Options
# ----------------------------

NAME = ez80op

LINUX_X86_ARCHITECTURE=linux_elf_x86_64
AGON_Z80_ARCHITECTURE=agon_bin_z80

# Tools and arguments
CC=gcc
OUTFLAG=-o 
RELEASE_LFLAGS=-s -static -Wall -O2 -DNDEBUG -DUNIX -Wno-unused-result
RELEASE_CFLAGS=$(RELEASE_LFLAGS) -c

# project directories
SRCDIR=src
OBJDIR=obj
BINDIR=bin
RELEASEDIR=releases

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BIN=$(BINDIR)/$(NAME)

all: linux agon windows haiku

directories:
	@echo === Creating directories
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(RELEASEDIR)

linux: directories
linux: LFLAGS=-g -Wall -DUNIX
linux: CFLAGS=-g -Wall -DUNIX -c
linux: $(BIN)

agon: directories
agon: CFLAGS = -Werror -Wall -Wextra -Oz -DCEDEV
agon: CXXFLAGS = -Werror -Wall -Wextra -Oz - DCEDEV
agon: 
	@echo === Compiling Agon target	
	touch $(BINDIR)/$(NAME).bin

windows: directories
	@echo === Compiling windows target
	touch $(BINDIR)/windows.bin

haiku: directories
	@echo === Compiling Haiku target
	touch $(BINDIR)/haiku.bin

$(BIN):$(OBJS)
ifeq ($(CC),gcc)
	$(CC) $(LFLAGS) $(OBJS) $(OUTFLAG) $@
else
	$(LINKER) $(LINKERFLAGS)$@ $(OBJS)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
ifeq ($(CC),gcc)
	$(CC) $(CFLAGS) $< $(OUTFLAG) $@
else
	$(CC) $(CFLAGS)$@ $<
endif

package: all
package: directories
	@echo === Packaging binaries
	@tar -zcvf $(RELEASEDIR)/$(NAME)_$(LINUX_X86_ARCHITECTURE).tar.gz $(BINDIR)/$(NAME)
	@tar -zcvf $(RELEASEDIR)/$(NAME)_$(AGON_Z80_ARCHITECTURE).tar.gz `$(BINDIR)/$(NAME).bin`

release: directories
release: all
release: package
release: CFLAGS=$(RELEASE_CFLAGS)
release: LFLAGS=$(RELEASE_LFLAGS)

clean:
	@echo === Cleaning directories
	@$(RM) -r $(BINDIR) $(OBJDIR) $(RELEASEDIR)