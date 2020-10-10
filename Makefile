all: dep
	gcc c/main.c stack_c.o -o a.elf
	gcc c/main2.c stack_c.o -o b.elf
	g++ cpp/main.cpp stack_cpp.o -o c.elf
	g++ cpp/main2.cpp stack_cpp.o -o d.elf
dep:
	gcc -c c/stack.c -o stack_c.o
	g++ -c cpp/stack.cpp -o stack_cpp.o 
clean:
	rm -f *.o *.elf