all: dep
	g++ -std=c++2a -Wall test1.cpp Form.o -o test1.elf
	g++ -std=c++2a -Wall test2.cpp Vector.o Trace.o -o test2.elf
dep:
	g++ -c -std=c++2a -Wall Form.cpp -o Form.o
	g++ -c -std=c++2a -Wall Vector.cpp -o Vector.o
	g++ -c -std=c++2a -Wall Trace.cpp -o Trace.o
clean:
	rm -f *.o *.elf *.out