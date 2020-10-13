CPPFLAGS=-std=c++11 -I ../../

SOURCES=Main.cpp ../../Munola.cpp
HEADERS=../../Munola.h

main: $(SOURCES) $(HEADERS)
	clang++ $(SOURCES) $(CPPFLAGS) -o main

.PHONY: run

run: main
	./main
