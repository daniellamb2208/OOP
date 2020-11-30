all: dep
	g++ main.cpp lexer.o -o main.elf
dep:
	g++ -c lexer.cpp -o lexer.o
clean:
	rm -f *.o *.elf *.out