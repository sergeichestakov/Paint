paint.out: main.o board.o line.o valInput.o commands.o 
	gcc -g -Wall -Werror -o paint.out main.o board.o valInput.o commands.o line.o
valInput.o: valInput.c valInput.h board.h
	gcc -g -Wall -Werror -c -o valInput.o valInput.c
commands.o: commands.c commands.h
	gcc -g -Wall -Werror -c -o commands.o commands.c
board.o: board.c board.h
	gcc -g -Wall -Werror -c -o board.o board.c
line.o: line.c line.h
	gcc -g -Wall -Werror -c -o line.o line.c
main.o: main.c board.h valInput.h commands.h
	gcc -g -Wall -Werror -c -o main.o main.c
clean:
	rm -f *.o *.out *.txt
