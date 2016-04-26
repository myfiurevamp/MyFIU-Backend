prog:	compile-main

compile-main:	main.cpp
	#g++ -I/usr/local/include main.cpp src/*.cpp -lpqxx -lpq -std=c++1y -Wall	
	 clang++ -I/usr/local/include main.cpp -o main src/*.cpp -lpqxx -lpq -msse4 -std=c++1y -stdlib=libc++ -Wall

