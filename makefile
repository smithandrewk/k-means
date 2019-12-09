#makefile for k-means in c++
default:
	g++ -g src/main.cpp src/DataAnalytics.cpp
# default: main.o DataAnalytics.o
# 	g++ -g src/main.cpp src/DataAnalytics.cpp
# FileHandler.o:g++
# 	g++ -c -g src/FileHandler.cpp -o FileHandler.o
# DataAnalytics.o:
# 	g++ -c -g src/DataAnalytics.cpp -o ../bin
# main.o:
# 	g++ -c -g src/main.cpp -o main.o
run:
	./a.out
v:
	valgrind ./a.out
c:
	rm -rf a.out *.o