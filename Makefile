all: B-Trees-Based-Database

B-Trees-Based-Database: src/main.cpp src/btree.cpp src/table.cpp src/cli.cpp
	g++ -std=c++17 -o B-Trees-Based-Database src/main.cpp src/btree.cpp src/table.cpp src/cli.cpp

clean:
	rm -f B-Trees-Based-Database
