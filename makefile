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
1d:
	./a.out ./input/1d.csv out
2d:
	./a.out ./input/2d.csv out
v:
	valgrind ./a.out ./input/1d.csv out
c:
	rm -rf a.out *.o