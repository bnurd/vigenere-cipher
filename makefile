program: main
	./main.out

main:
	g++ main.cpp -o main.out

clean: 
	rm *.o program
