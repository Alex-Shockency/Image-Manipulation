CXXFLAGS=-std=c++11 -Wall -O2 -march=native

pa7: Image.o main.o Mapping.o Morph.o Interpolation.o
	g++ $(CXXFLAGS) Image.o main.o -o pa7 Mapping.o Morph.o Interpolation.o
Image.o: Image.cpp Image.h
	g++ $(CXXFLAGS) -g -c -I. Image.cpp
Mapping.o: Mapping.cpp Mapping.h
	g++ $(CXXFLAGS) -g -c -I. Mapping.cpp
Morph.o: Morph.cpp Morph.h
	g++ $(CXXFLAGS) -g -c -I. Morph.cpp
Interpolation.o: Interpolation.cpp Interpolation.h
	g++ $(CXXFLAGS) -g -c -I. Interpolation.cpp
main.o: main.cpp 
	g++ $(CXXFLAGS) -g -c -I. main.cpp
target: 
	tar -cf PA7.tar ./Makefile *.{cpp,h}
clean:
	-rm -f pa7 *.o

