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

int check_type(char ch, char* str, FILE* ptr)
{
    int i = 0;
    int count = 0;
    int chr;
    while (ch == str[i] && i < (int)strlen(str)) {
        chr = fgetc(ptr);
        ch = (char)chr;
        count++;
        i++;
    }
    if (count == strlen(str)) { return 1; }
    else { return 0; }
}

void add_person(struct people* person, int n, int t, FILE* ptr)
{
    char* line = NULL;
    int num = 0;
    line = (char*)malloc(1000*sizeof(char));
    for (int i = 0;; i++)
    {
        line = (char*)realloc(line, (i + 1) * sizeof(char));
        int chr;
        chr = fgetc(ptr);
        line[i] = (char)chr;
        if (line[i] == '<')
        {
            line[i] = '\0';
            num = i + 1;
            break;
        }
    }

    if (line[0] == 32) {
        int length = num;
        if (length >= 2) {
            for (int j = 0; j < length - 1; j++) {
                line[j] = line[j + 1];
            }
            line[length - 1] = '\0';
        } else {
            line[0] = '\0';
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
        unsigned long long j;
        
        for (j = 0; j < num - 1; j++) {
            line[j] = line[j + 1];
        }
        for (j = num; j > num - 5; j--) {
            line[j] = '\0';
        }

        int a = line[0] - '0';
        int b;
        if (num>1) {b = line[1] - '0';}
        int c;
        if (num>2) {c = line[2] - '0';}
        if (c >= 0 && c <= 9) {
            person[n].money = a * 100 + b * 10 + c;
        }
        else { person[n].money = a * 10 + b; }
    }

    free(line);
}


void made(struct people* person, int n, char c, int t, char const_find[], FILE*ptr)
{
    int chr;
    char ch;
    chr = fgetc(ptr);
    ch = (char)chr;
    while (!feof(ptr) && ch != c) {
        chr = fgetc(ptr);
        ch = (char)chr;
    }

    while (check_type(ch, const_find, ptr) != 1) {
        while (!feof(ptr) && ch != c) {
            chr = fgetc(ptr);
            ch = (char)chr;
        }
    }

    while (!feof(ptr) && ch != '>') {
        chr = fgetc(ptr);
        ch = (char)chr;
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
            int chr;
            chr = fgetc(ptr);
            ch = (char)chr;
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

    if (strcmp(p1->name, p2->name)) return strcmp(p1->name, p2->name);
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
                    if (n!=0) {
                        person = (struct people*)realloc(person, n * sizeof(struct people));
                    }
                }
                break;
            default:
                t=0;
                break;
              
        }
    }
    free(person);
}
