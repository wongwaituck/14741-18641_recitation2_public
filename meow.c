/*
 * 14741/18641 Fall 2018 Recitation 2
 * Meow - lrn2bin
 *
 * Demonstrates x86 calling convention
 * Compile with flags in Makefile!
 * waituckw@andrew.cmu.edu
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void win(){
    puts("                                  ___________");
    puts("                             .---'::'        `---.");
    puts("                            (::::::'              )");
    puts("                            |`-----._______.-----'|");
    puts("                            |              :::::::|");
    puts("                           .|               ::::::!-.");
    puts("                           \\|               :::::/|/");
    puts("                            |               ::::::|");
    puts("                            |    YOU'RE WINNER!:::|");
    puts("                            |                :::::|");
    puts("                            |               ::::::|");
    puts("                            |              .::::::|");
    puts("                            J              :::::::F");
    puts("                             \\            :::::::/");
    puts("                              `.        .:::::::'");
    puts("                                `-._  .::::::-'");
    puts("____________________________________|  \"\"\"|\"_________________________________________");
    puts("                                    |  :::|");
    puts("                                    F   ::J");
    puts("                                   /     ::\\");                                        
    puts("                              __.-'      :::`-.__");
    puts("                             (_           ::::::_)");
    puts("                               `\"\"\"---------\"\"\"'");

    exit(0);
}


void print_vuln1_stack(char* _buf){
    // prints the vuln1 stack frame in a nice ASCII art
    int* buf = (int *) _buf;
    puts("|   ....   |");
    puts(" ---------- ");
    // print arguments
    uint32_t* arg1 = buf + 8;
    uint32_t* arg2 = arg1 + 1;
    uint32_t* arg3 = arg2 + 1;
    
    printf("| %08x | <--- c\n", *arg3);
    puts(" ---------- ");
    printf("| %08x | <--- b\n", *arg2);
    puts(" ---------- ");
    printf("| %08x | <--- a\n", *arg1);
    puts(" ---------- ");
 
    // print saved eip
    uint32_t* eip = arg1 - 1;
    printf("| %08x | <--- saved return address\n", *eip);
    puts(" ---------- ");
   
    // print saved ebp
    uint32_t* ebp = eip - 1;
    printf("| %08x | <--- saved ebp\n", *ebp);
    puts(" ---------- ");

    // print rubbish
    uint32_t* rubbish1 = ebp - 1;
    uint32_t* rubbish2 = rubbish1 - 1;
    printf("| %08x | <--- ??? \n", *rubbish1);
    puts(" ---------- ");
    printf("| %08x | <--- ??? \n", *rubbish2);
    puts(" ---------- ");

    // print best variables
    uint32_t* first = rubbish2 - 1;
    uint32_t* second = first - 1;
    printf("| %08x | <--- first \n", *first);
    puts(" ---------- ");
    printf("| %08x | <--- second \n", *second);
    puts(" ---------- ");
    
    // print buffer
    uint32_t* buf1 = second - 1;
    uint32_t* buf2 = buf1 - 1;
    printf("| %08x | <--- buf(cont.)\n", *buf1);
    puts(" ---------- ");
    printf("| %08x | <--- buf \n", *buf2);
    puts(" ---------- ");

    puts("|   ....   |");
}


int vuln1(int a, int b, int c) {
    // simple program to demonstrate the stack and a simple buffer overflow
    unsigned int first = 0xcafebabe;
    unsigned int second = 0xdabbface;
    char buf[8];
 
    gets(buf);
}


int vuln1_soln(int a, int b, int c) {
    // simple program to demonstrate the stack and a simple buffer overflow
    // also prints the stack
    unsigned int first = 0xcafebabe;
    unsigned int second = 0xdabbface;
    char buf[8];
 
    gets(buf);

    print_vuln1_stack(buf);
}

int vuln2() {
    // demonstrate stack canary
    unsigned int canary = 0xdeadbeef;
    char buf[8];

    gets(buf);

    if (canary != 0xdeadbeef) {
        puts("HACKER DETECTED. Try harder!");
        exit(-1);    
    } 
}


int vuln3() {
    // ret2libc
    char buf[8];
    
    system("/bin/date");
    puts("Oh wow. Would you look at the time? Now it's your time to win!");
    printf("Place the '/bin/bash\\x00' string here and feed this address to system: 0x%08x\n", (unsigned int)(buf + 32));
    puts("Find where system is and WIN!");
    puts("Prepare your input below:"); 
    gets(buf);
   
}


void print_banner(){
    puts("Welcome to the 2nd Recitation!");
    puts("");
    puts("Choose what you want to learn:");
    puts("1. Learn about buffer overflows");
    puts("2. Print the solution for 1.");
    puts("3. Learn about stack canaries");
    puts("4. Learn about ret2libc");
    puts("0. Exit");
}

int main(int argc, char* argv[]){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice = -1;

    while(choice){
        print_banner();
        
        scanf("%d", &choice);
        // ignore the new line
        int c = getchar();
        switch(choice) {
            case 1:
                puts("Launching lesson 1...\nCalling vuln1(1, 2, 3)...\nplease prepare your input below:");
                vuln1(1, 2, 3);
                break;
            case 2:
                puts("Launching lesson 1 with solution...\nCalling vuln1(1, 2, 3)...\nplease prepare your input below:");
                vuln1_soln(1, 2, 3);
                break;
            case 3:
               puts("Launching lesson...\nCalling vuln2()...\nplease prepare your input below:");
                vuln2();
                break;
            case 4:
                puts("Launching lesson...\nCalling vuln3()...");
                vuln3();
                break;
            case 0:
                break;
            default:
                puts("What?");
        
        }

    }
    puts("Thanks for coming!");
    return 0;
}
