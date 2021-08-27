IDIR =../util
CC=g++
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =../naive_algorithm
UDIR =../.

_DEPS = useful_code.h samplesManager.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = compare.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_LDEPS = naive_string_matching.h 
LDEPS = $(patsubst %,$(LDIR)/%,$(_LDEPS))

_UDEPS = string_matching_automata.h
UDEPS = $(patsubst %,$(UDIR)/%,$(_UDEPS))


$(UDIR)/%.o: %.c $(UDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LDIR)/%.o: %.c $(LDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(IDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compare: $(DEPS) $(OBJ) $(LDEPS) $(UDEPS)
	$(CC) -o $@ $^ $(CFLAGS)
