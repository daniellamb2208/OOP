all: dep
	g++ main.cpp mytar.o -o mytar.elf
dep:
	g++ -c mytar.cpp -o mytar.o
clean:
	rm -f *.o *.elf