#include "treeAPI.h"
#include "Header.h"

void play_game(tree_node** tree, int* check) {
    int ans = 0;
    printf("%s", (*tree)->data);
    int j = 0;
    while (ans == 0) {
        int t;
        fflush(stdin);
        printf("Choose: 1 - yes, 0 - no: ");
        scanf("%d", &t);
        if (t == 1) {
            *check = *check * 2;
        } else {
            *check = (*check * 2) + 1;
        }
        char* quest;
        quest = get_elem(*tree, *check);
        ans = get_ans(*tree, *check);
        if (ans == 1) {
            char* str_new = (char*)malloc(sizeof(char));
            while (quest[j] != '!') {
                str_new[j] = quest[j];
                str_new = (char*)realloc(str_new, (strlen(str_new) + 1) * sizeof(char));
                j++;
            }
            str_new[j] = '\0';
            printf("\nYour character is %s!\n", str_new);
            free(str_new);
        } else {
            printf("%s", quest);
        }
    }

    int t;
    printf("Is it true?\nChoose: 1 - yes, 0 - no: ");
    scanf("%d", &t);
    j++;
    if (t == 1) {
        printf("\nYes! We guess your character!\n");
        const char* quest;
        quest = get_elem(*tree, *check);
        char* str_new = (char*)calloc(1, sizeof(char));
        int i = 0;
        while (quest[j] != '!') {
            str_new[i] = quest[j];
            str_new = (char*)realloc(str_new, (strlen(str_new) + 1) * sizeof(char));
            j++;
            i++;
        }
        str_new[i] = '\0';

        char* str_new_type = (char*)calloc(1, sizeof(char));
        j = 0;
        while (quest[j] != '!') {
            str_new_type[j] = quest[j];
            str_new_type = (char*)realloc(str_new_type, (strlen(str_new_type) + 1) * sizeof(char));
            j++;
            i++;
        }
        str_new_type[j] = '\0';
        printf("%s!\n\n", str_new);
        free(str_new);
        time_t time_now;
        char* time_string;
        time_now = time(NULL);
        time_string = ctime(&time_now);
        time_string[strlen(time_string) - 1] = '!';
        
        str_new_type = (char*)realloc(str_new_type, (strlen(str_new_type) + strlen(time_string) + 4) * sizeof(char));
        
        str_new_type = strcat(str_new_type, "!");
        str_new_type = strcat(str_new_type, time_string);
        str_new_type = strcat(str_new_type, "\n");

        new_insert(tree, str_new_type, *check);
        free(str_new_type);
    } else {
        printf("Oh, sorry!\nAdd special question about your character and try again!\n");
        printf("Enter name of your character:\n");
        char* str_name = (char*)calloc(256, sizeof(char));
        getStr(str_name, 256 + 1);
        getStr(str_name, 256 + 1);

        printf("Enter special question:\n");
        char* str_question = (char*)calloc(256, sizeof(char));
        getStr(str_question, 256 + 1);
        str_question = strcat(str_question, "\n");
        str_name = strcat(str_name, "!It's first time!\n");

        const char* val1;
        val1 = get_elem(*tree, *check);
        new_insert(tree, str_question, *check);
        new_insert(tree, str_name, *check * 2);
        new_insert(tree, val1, (*check * 2) + 1);
    }
}

void save_game(tree_node* tree, int q) {
    printf("Thank you for game!\n");
    FILE* fp = fopen("input.txt", "w");
    int check = 1;
    int x = 1;
    while (x < q) {
        for (int i = 1; i <= x; i++) {
            const char* val2;
            val2 = get_elem(tree, check);
            if (val2 != NULL) {
                fprintf(fp, "%s", val2);
            } else {
                char c = '.';
                fprintf(fp, "%c\n", c);
            }
            check++;
        }
        x = x * 2;
    }

    if (fp != NULL) {fclose(fp);}
}

void cleanup(tree_node* tree) {
    free_tree(tree);
}

int main() {
    FILE* f;
    f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File is empty!");
        return 0;
    }

    tree_node* tree = NULL;
    int check = 1;
    while (!feof(f)) {
        char str[256];
        fgets(str, 256, f);
        insert(&tree, str, check);
        check++;
    }
    fclose(f);
    int q = check - 1;
    for (int i = 1; i <= q * 2; i++) {
        insert(&tree, ".\n", check);
        check++;
    }

    play_game(&tree, &check);

    save_game(tree, q);
    cleanup(tree);

    return 0;
}
