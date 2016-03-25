CC=gcc

lab5:	cscd340hw8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./alias/alias.o ./shell/shell.o ./linkedlist/listUtils.c
	gcc -g cscd340hw8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./history/history.o ./alias/alias.o ./shell/shell.o  ./linkedlist/listUtils.c ./linkedlist/linkedList.c -o mssh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

history.o:	./history/history.c ./history/history.h
	gcc -g -c .history/history.c

alias.o:	./alias/alias.c ./alias/alias.h
	gcc -g -c ./alias/alias.c

shell.o:	./shell/shell.c ./shell/shell.h
	gcc -g -c ./shell/shell.c
clean:
	rm ./*/*.o	
	rm mssh

