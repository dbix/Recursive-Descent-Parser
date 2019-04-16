go: main.c tokenizer.c parser.c
	gcc main.c tokenizer.c parser.c -lfl -ly -o recdec

clean:
	rm -f recdec