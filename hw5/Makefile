all: dep
	g++ -Wall test1.cpp Form.o -o test1.elf
#	g++ -Wall test2.cpp Vector.o Trace.o -o test2.elf
dep:
	g++ -c -Wall Form.cpp -o Form.o
#	g++ -c -Wall Vector.cpp -o Vector.o
#	g++ -c -Wall Trace.cpp -o Trace.o
clean:
	rm -f *.o *.elf *.out