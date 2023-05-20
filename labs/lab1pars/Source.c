#include "Header.h"

int input_check_opt()
{
    int val;
    while (scanf_s("%d", &val) != 1 || getchar() != '\n' || (val < 0 || val > 7)) {
        printf("Wrong! Try again.\n");
        rewind(stdin);
    }
    return val;
}

int input_check_del(int n)
{
    int val;
    while (scanf_s("%d", &val) != 1 || getchar() != '\n' || (val<1 || val>n)) {
        printf("Wrong! Try again.\n");
        rewind(stdin);
    }
    return val;
}

int check_type(char ch, char str[], FILE* ptr)
{
    int i = 0, count = 0;
    while (ch == str[i] && i < (int)strlen(str)) {
        ch = fgetc(ptr);
        count++;
        i++;
    }
    if (count == strlen(str)) { return 1; }
    else { return 0; }
}

void add_person(struct people* person, int n, int t, FILE* ptr)
{
    char* line = NULL;

    line = (char*)malloc(1000*sizeof(char));
    for (int i = 0;; i++)
    {
        line = (char*)realloc(line, (i + 1) * sizeof(char));
        line[i] = fgetc(ptr);
        if (line[i] == '<')
        {
            line[i] = '\0';
            break;
        }
    }

    if (line[0] == 32) {
        for (int i = 0; i < strlen(line) - 2; i++) {
            line[i] = line[i + 1];
        }
        unsigned long long k = strlen(line);
        line[k] = '\0';
        k--;
        line[k] = '\0';
    }

    if (t == 1) {
        person[n].name = (char*)calloc(strlen(line) + 1, sizeof(char));
        strcpy(person[n].name, line);
    }
    if (t == 2) {
        person[n].age = (char*)calloc(strlen(line) + 1, sizeof(char));
        strcpy(person[n].age, line);
    }
    if (t == 3) {
        person[n].residence = (char*)calloc(strlen(line) + 1, sizeof(char));
        strcpy(person[n].residence, line);
    }
    if (t == 4) {
        for (int j = 0; j < strlen(line) - 1; j++) {
            line[j] = line[j + 1];
        }
        for (int j = strlen(line); j > strlen(line) - 5; j--) {
            line[j] = '\0';
        }

        int a = line[0] - '0', b = line[1] - '0', c = line[2] - '0';
        if (c >= 0 && c <= 9) {
            person[n].money = a * 100 + b * 10 + c;
        }
        else { person[n].money = a * 10 + b; }
    }

    free(line);
}


void made(struct people* person, int n, char c, int t, char const_find[], FILE*ptr)
{
    char ch;
    ch = fgetc(ptr);
    while (!feof(ptr) && ch != c) {
        ch = fgetc(ptr);
    }

    while (check_type(ch, const_find, ptr) != 1) {
        while (!feof(ptr) && ch != c) {
            ch = fgetc(ptr);
        }
    }

    while (!feof(ptr) && ch != '>') {
        ch = fgetc(ptr);
    }
    add_person(person, n, t, ptr);
}

void find_inf(struct people* person, char ch, int* n, FILE* ptr)
{
    char name_find[] = "mntl-sc-block-heading__text";
    char age_find[] = "Age:";
    char residence_find[] = "Residence:";
    char money_find[] = "Net Worth:";
    int t = 0;
    if (check_type(ch, name_find, ptr) == 1) {
        int z = 0;
        while (ch != '.' && z < 6) {
            z++;
            ch = fgetc(ptr);
        }

        if (z < 6) { t++; }
        if (t != 0) {
            int k = *n;
            add_person(person, k, t, ptr);
            char c = 'A'; t++;
            made(person, k, c, t, age_find, ptr);
            c = 'R'; t++;
            made(person, k, c, t, residence_find, ptr);
            c = 'N'; t++;
            made(person, k, c, t, money_find, ptr);
            (*n)++;
        }
    }
}

void output(struct people* person, int n)
{
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d. name: %s\t age: %s\t money: $%d billion\t residence: %s\n", i + 1, person[i].name, person[i].age, person[i].money, person[i].residence);
    }
}

int comp_by_name(const void* typ1, const void* typ2) {
    const struct people* p1 = (const struct people*)typ1;
    const struct people* p2 = (const struct people*)typ2;
    return strcmp(p1->name, p2->name);
}

int comp_by_money(const void* typ1, const void* typ2) {
    const struct people* p1 = (const struct people*)typ1;
    const struct people* p2 = (const struct people*)typ2;
    return p1->money - p2->money;
}

int comp_by_age(const void* typ1, const void* typ2) {
    const struct people* p1 = (const struct people*)typ1;
    const struct people* p2 = (const struct people*)typ2;
    return strcmp(p1->age, p2->age);
}

int comp_by_residence(const void* typ1, const void* typ2) {
    const struct people* p1 = (const struct people*)typ1;
    const struct people* p2 = (const struct people*)typ2;
    return strcmp(p1->residence, p2->residence);
}

int comp_full(const void* typ1, const void* typ2)
{
    const struct people* p1 = (const struct people*)typ1;
    const struct people* p2 = (const struct people*)typ2;

    int cmp;
    if (cmp = strcmp(p1->name, p2->name)) return cmp;
    return strcmp(p1->age, p2->age);
}

void delite_elem(struct people* mas, int n)
{
    printf("Choose number of struct that you want to delete (1..%d): ", n);
    int nom = input_check_del(n); nom--;
    for (int i = nom; i < n - 1; i++) {
        mas[i] = mas[i + 1];
    }
}

void menu()
{
    printf("1. Display structure\n");
    printf("2. Sort by name\n");
    printf("3. Sort by money\n");
    printf("4. Sort by residence\n");
    printf("5. Sort by age\n");
    printf("6. Sort by multiple fields\n");
    printf("7. Delete structure\n");
    printf("0. Exit\n");
}

void work_prog(struct people* person, int n)
{
    int t = 10;
    while (t != 0) {
        fflush(stdin);
        printf("\nChoose your option: ");
        t = input_check_opt();
        switch (t) {
            case 0:
                printf("\nThank you! Buy!\n");
                break;
            case 1:
                output(person, n);
                break;
            case 2:
                qsort(person, n, sizeof(struct people), comp_by_name);
                break;
            case 3:
                qsort(person, n, sizeof(struct people), comp_by_money);
                break;
            case 4:
                qsort(person, n, sizeof(struct people), comp_by_residence);
                break;
            case 5:
                qsort(person, n, sizeof(struct people), comp_by_age);
                break;
            case 6:
                qsort(person, n, sizeof(struct people), comp_full);
                break;
            case 7:
                if (n!=0) {
                    delite_elem(person, n);
                    n--;
                    person = (struct people*)realloc(person, n * sizeof(struct people));
                }

                break;
        }
    }
    free(person);
}
