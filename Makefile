CXX=g++
CPPFLAGS=-g -Wall -Wextra -std=c++11 -O2
LDFLAGS=-lSDL2

all: clean gameboy

gameboy:
	$(CXX) $(CPPFLAGS) src/*.cpp -o gameboy $(LDFLAGS) 

clean:
	rm -f gameboy 
