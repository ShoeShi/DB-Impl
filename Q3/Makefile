CC = g++
CFLAGS = -std=c++11 -Wall -g 
LDLIBS = 
OBJS = q3.o
EXE = Join

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE) $(LDLIBS)

q3.o: Q3/q3.cpp
	$(CC) $(CFLAGS) -c Q3/q3.cpp

clean:
	rm -f $(OBJS)
	rm -f *~
	rm -f $(EXE)

