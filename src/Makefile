CC = g++
FLAGS = -std=c++11 -O3

a.out: main.o
	$(CC) $(FLAGS) -o a.out main.o

./SUFFIXES:.cpp.o

main.o: main.cpp analysis.h rawfile.h
	$(CC) $(FLAGS) main.cpp -c

#analysis.o: analysis.cpp analysis.h
#	$(CC) $(FLAGS) analysis.cpp -c

.PHONY: run

run:
	./a.out

clean:
	-rm *.o
	-rm a.out
