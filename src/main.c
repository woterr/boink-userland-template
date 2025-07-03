#include <stdio.h>
#include <stdlib.h>
#include <util.h>

int main(int argc, char** argv) {
	clear();
	puts("hi from userland!\nargs:\n");
	puts("\n");

	for (int i = 0; i < argc; i++) {
		puts(argv[i]);
		puts("\n");
	}

	puts("What is your age? ");
	char buf[4];
	input(buf, 4);

	int age = atoi(buf);

	puts("In 10 years you will be: ");
	puts(itoa(age+10, 10));
	putchar('\n');

	sleep(100);
	putchar('\n');
	
	return 0;
}