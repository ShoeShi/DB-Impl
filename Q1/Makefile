CC = g++
CFLAGS = -std=c++11 -Wall -g 
LDLIBS = 
OBJS = q1.o BPTree.o
EXE = BPlusTree

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE) $(LDLIBS)

BPTree.o: Q1/BPTree.cpp Q1/BPTree.hpp
	$(CC) $(CFLAGS) -c Q1/BPTree.cpp

q1.o: Q1/q1.cpp Q1/BPTree.hpp
	$(CC) $(CFLAGS) -c Q1/q1.cpp

clean:
	rm -f $(OBJS)
	rm -f *~
	rm -f $(EXE)

