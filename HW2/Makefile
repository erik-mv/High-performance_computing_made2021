CC=g++
CFLAGS=-c
OPTFLAGS=-O3
N=2048
LDFLAGS=
SOURCES=main.c mat_on_mat.c mat_on_vec.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=result_$(N)$(OPTFLAGS)

all: $(SOURCES) $(EXECUTABLE) clean 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@ $(OPTFLAGS)

clean :
	rm -f *.o