CC=gcc
CFLAGS=-m32 -std=c99 
VULN_CFLAGS=-fno-stack-protector -z execstack -no-pie

all: clean meow

meow:
	$(CC) -o meow meow.c $(CFLAGS) $(VULN_CFLAGS)

clean:
	rm -f meow win
