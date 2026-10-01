CC = clang
CFLAGS = -std=c17 -fsanitize=address,undefined -Wall -Wextra -g -O0
LDFLAGS = -fsanitize=address,undefined
LDLIBS = -lm

objects = ./src/main.o ./src/greet.o ./src/sum.o
target = hello
$(target): $(objects)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

./src/main.o: ./src/main.c ./src/greet.h
	$(CC) $(CFLAGS) -c $< -o $@

./src/greet.o: ./src/greet.c ./src/greet.h
	$(CC) $(CFLAGS) -c $< -o $@

./src/sum.o: ./src/sum.c ./src/sum.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm hello $(objects)