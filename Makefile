all: main1

#main1: main.cpp regularExpression.cpp
#	g++ -std=c++11 main.cpp regularExpression.cpp
main1: main.o regularExpression.o
	g++ -std=c++11 main.o regularExpression.o -o main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

regularExpression.o: regularExpression.cpp
	g++ -std=c++11 -c regularExpression.cpp

compile:
	./main

clean:
	rm -rf *.o main