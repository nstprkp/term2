#include "Header.h"

int main(void)
{
	menu();
	FILE* ptr;
	int n = 0;
	struct people* person;
	person = (struct people*)calloc(1000, sizeof(struct people));
	int ch;
	if ((ptr = fopen("input.txt", "r")) != NULL) {
		while (!feof(ptr)) {
			ch = fgetc(ptr);
			if (ch == 'm') { find_inf(person, ch, &n, ptr); }
			n++;
		}
		fclose(ptr);
	}
	else { printf("\nFile not found.\n"); 
	      fclose(ptr);
	      return 0;
	     }

	person = (struct people*)realloc(person, n * sizeof(struct people));

	work_prog(person, n);
	return 0;
}

