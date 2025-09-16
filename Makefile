# DO NOT MODIFY THIS FILE

GCC = gcc -std=c11 -D_POSIX_C_SOURCE=200809L -g -Wall -Wshadow --pedantic -Wvla -Werror
SRCS = main.c stack.c tree.c
OBJS = $(SRCS:%.c=%.o)

all: expr

expr: $(OBJS) 
	$(GCC) $(OBJS) -o expr

%.o: %.c
	$(GCC) -c $< -o $@

test%: expr
	./expr tests/test$*.txt output$*
	diff output$* expected/expected$*.txt



testall: test1 test2 test3 test4 test5

memory: expr
	valgrind --leak-check=full ./expr tests/test5.txt output5
	diff output5 expected/expected5.txt

clean:
	rm -f expr $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
