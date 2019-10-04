if DEBUG
AM_CFLAGS = -DDEBUG -I$(srcdir)/../lib -I$(srcdir)/../include -lreadline
else
AM_CFLAGS = -I$(srcdir)/../lib -I$(srcdir)/../include -lreadline
endif

bin_PROGRAMS = bs
bs_SOURCES = main.c loop.c node.c reader.c

