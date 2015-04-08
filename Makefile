CC = g++
CFLAGS = -Wall -g 
LDLIBS = 
OBJS = q1.o funcs.o
EXE = q1

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE) $(LDLIBS)

funcs.o: funcs.cpp funcs.h
	$(CC) $(CFLAGS) -c funcs.cpp

q1.o: q1.cpp funcs.h
	$(CC) $(CFLAGS) -c q1.cpp

clean:
	rm -f $(OBJS)
	rm -f *~
	rm -f $(EXE)

