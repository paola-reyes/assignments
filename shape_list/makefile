build:
	g++ -g -Wall -std=c++20 main.cpp -o tests.exe

ctest:
	rm -f tests.exe
	g++ -Wall -std=c++20 tests.cpp -o tests.exe

gtest:
	rm -f tests.exe
	g++ -g -std=c++20 -Wall gtests.cpp -o tests.exe -lgtest -lgtest_main -lpthread

run:
	./program.exe

runtest:
	./tests.exe

clean:
	rm -f program.exe
	rm -f tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./a.out
