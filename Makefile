all:main

main:
	g++ -std=c++11 -o a.out main.cc PMTClass.C -lEG `root-config --cflags` `root-config --libs` -lTreePlayer

