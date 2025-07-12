#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include <syscall.h>

#define MAX_WRONG 6
#define MAX_WORD_LEN 32

// Multiple words
const char* words[] = {
	"BOINK",
	"TESTER",
	"USERLAND"
};
#define NUM_WORDS (sizeof(words) / sizeof(words[0]))

char guessed[256];
int wrong_guesses = 0;
char current_word[MAX_WORD_LEN];

void draw_hangman(int wrong) {
	puts("\n\n");
	puts("  +---+\n");
	puts("  |   |\n");

	if (wrong >= 1) puts("  O   |\n");
	else puts("      |\n");

	if (wrong == 2) puts("  |   |\n");
	else if (wrong == 3) puts(" /|   |\n");
	else if (wrong >= 4) puts(" /|\\  |\n");
	else puts("      |\n");

	if (wrong == 5) puts(" /    |\n");
	else if (wrong >= 6) puts(" / \\  |\n");
	else puts("      |\n");

	puts("      |\n");
	puts("=========\n");
}

void print_word_state() {
	puts("\nWord: ");
	for (int i = 0; current_word[i]; i++) {
		if (guessed[(unsigned char)current_word[i]]) {
			putchar(current_word[i]);
		} else {
			putchar('_');
		}
		putchar(' ');
	}
}

int already_guessed(char c) {
	return guessed[(unsigned char)c];
}

int main(int argc, char** argv) {
	clear();
	puts("=== Welcome to Hangman on BoinkOS ===\n");

	int word_len = 0;

    // randomize 
	int index = syscall(SYSCALL_UPTIME, 0, 0, 0, 0, 0) % NUM_WORDS;
    
	const char* selected = words[index];
	while (selected[word_len] && word_len < MAX_WORD_LEN - 1) {
		current_word[word_len] = selected[word_len];
		word_len++;
	}
	current_word[word_len] = '\0';

	int correct = 0;

	while (wrong_guesses < MAX_WRONG && correct < word_len) {
		print_word_state();

		puts("\n\nGuess a letter: ");
		char c = getchar();
		putchar(c); // echo
		putchar('\n');

		// Normalize case
		if (c >= 'a' && c <= 'z') {
			c -= 32;
		}

		if (already_guessed(c)) {
			puts("Already guessed.\n");
			continue;
		}

		guessed[(unsigned char)c] = 1;

		int found = 0;
		for (int i = 0; i < word_len; i++) {
			if (current_word[i] == c) {
				found = 1;
				correct++;
			}
		}

		if (!found) {
			wrong_guesses++;
			puts("Wrong guess!\n");
		}

		draw_hangman(wrong_guesses);
	}

	if (correct == word_len) {
		puts("\nYou won!\n");
	} else {
		puts("\nYou lost. The word was: ");
		puts(current_word);
		putchar('\n');
	}

	puts("\nPress any key to exit.");
	getchar();
	return 0;
}
