CC := g++
LDLIBS := -lpthread 
CPPFLAGS := -g -I. -Wall
OBJS := manager.o buffer.o

all: manager

manager: $(OBJS)
	$(CC) $(LDLIBS) -o manager $(OBJS)

manager.o: buffer.h
	$(CC) $(CPPFLAGS) -c manager.cpp

buffer.o: buffer.h	
	$(CC) $(CPPFLAGS) -c buffer.cpp

clean:
	rm -rf *~ core manager $(OBJS)