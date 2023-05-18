#include "lib\header.h"

int main(void)
{
	menu();
	FILE* ptr;
	int n = 0, nom = 0;
	struct people* person;
	person = (struct people*)calloc(1000, sizeof(struct people));
	char ch;
	if ((ptr = fopen("input.txt", "r")) != NULL) {
		while (!feof(ptr)) {
			ch = fgetc(ptr);
			if (ch == 'm') { find_inf(person, ch, &n, ptr); }
		}
		fclose(ptr);
	}
	else { printf("\nFile not found.\n"); }

	person = (struct people*)realloc(person, n * sizeof(struct people));

	work_prog(person, n);
	return 0;
}

