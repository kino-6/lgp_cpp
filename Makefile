CC            = g++
CFLAGS        = -O3 -Wall
DEST          = /bin
LDFLAGS       = -L/src
LIBS          = -lm
PROGRAM       = SLGP
OBJS          = src/main.o src/SLGP.o src/SLGP_Problem.o src/SLGP_Code.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)
	$(PROGRAM).exe

clean:
	rm -f *.o *~ $(PROGRAM)
	rm -f src/*.o src/*~ src/$(PROGRAM)
	rm debug.log

install: $(PROGRAM)
	install -s $(PROGRAM) $(DEST)