#include "header.h"

void handleChoice(HashTable* table, int choice) {
    FILE* f;
    switch (choice) {
        case 0:
            printf("Thank you! Bye!\n");
            break;
        case 1:
            f = fopen("input.txt", "r");
            if (f == NULL) {
                printf("File not found!\n");
                break;
            }
            printf("Choose what you want to find:\n");
            char* domain = (char*)calloc(256, sizeof(char));
            get_str(domain, 256);
            get_str(domain, 256);
            int ch = find_IP(table, domain);
            fclose(f);

            if (ch == 1) {
                f = fopen("input.txt", "a");
                if (f == NULL) {
                    printf("File not found!\n");
                    break;
                }
                add_in_file(table, f, domain, NULL);
                fclose(f);
            }
            free(domain);
            break;
        case 2:
            domain_by_IP();
            break;
        case 3:
            display_cache(table);
            break;
        default:
            break;
    }
}

int main() {
    HashTable* table = create_hash_table();
    int choice = 10;
    
    do {
        fflush(stdin);
        menu();
        scanf("%d", &choice);
        
        while (choice < 0 || choice > 3) {
            printf("Wrong input, try again!\n");
            scanf("%d", &choice);
        }
        
        handleChoice(table, choice);
    } while (choice != 0);
    
    free_hash_table(table);
    return 0;
}
