CC=gcc
CFLAGS=-m32 -g -std=c99 
VULN_CFLAGS=-fno-stack-protector -z execstack -no-pie

all: clean win meow

win:
	$(CC) -o win win.c $(CFLAGS)

meow:
	$(CC) -o meow meow.c $(CFLAGS) $(VULN_CFLAGS)

clean:
	rm -f meow win
