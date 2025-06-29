#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	puts("hi from userland!\nargs:\n");
	for (int i = 0; i < argc; i++) {
		puts(argv[i]);
		puts("\n");
	}
	puts("\n");
	return 0;
}