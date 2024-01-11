CXX=mpicxx
CXXFLAGS=-std=c++17 -O2 #-fsanitize=address -fsanitize=leak -fno-omit-frame-pointer

all: a2

clean:
	rm -rf a2

tar:
	tar -czvf A2Q1.tar A2Q1/

