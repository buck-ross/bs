if DEBUG
AM_CFLAGS = -DDEBUG -I$(srcdir)/../lib -I$(srcdir)/../include
else
AM_CFLAGS = -I$(srcdir)/../lib -I$(srcdir)/../include
endif

bin_PROGRAMS = brainfuck-shell
brainfuck_shell_SOURCES = brainfuck.c loop.c node.c reader.c
