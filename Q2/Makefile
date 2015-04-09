CC = g++
CFLAGS = -std=c++11 -Wall -g 
LDLIBS = 
OBJS = q2.o mergesort.o
EXE = q2

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE) $(LDLIBS)

mergesort.o: mergesort.cpp mergesort.h
	$(CC) $(CFLAGS) -c mergesort.cpp

q2.o: q2.cpp mergesort.h
	$(CC) $(CFLAGS) -c q2.cpp

clean:
	rm -f $(OBJS)
	rm -f *~
	rm -f $(EXE)

