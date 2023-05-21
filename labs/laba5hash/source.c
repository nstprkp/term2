#include "header.h"

char* get_str(char *s, int k)
{
    char c;
    int ch;
    int i=0;
    while(--k > 0 && (ch = getchar())!=EOF && ch != 13) {
        c = (char)ch;
        s[i++] = c;
    }
    s[i] = '\0';
    return s;
}

unsigned int hash(const char* key, int num_buckets) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % 3;
}

int input_check(const char* str)
{
    int g = 0;
    int point = 0;
    int sum = 0;
    int i = 0;
    for (int j = 0; j < strlen(str); j++) {
        if (str[j] == 46) {point++;}
    }
    if (point != 3) {
        g++;
        return g;
    }
    while (i < strlen(str)) {
        int k[4];
        for (int j = 0; j <=3; j++) { k[j] = 0;}
        int j = 3;
        point = 0;
        while (str[i] != '.' && i<strlen(str)) {
            k[j] = str[i] - '0';
            j--;
            point++;
            i++;
        }
        if (point > 3) {
            g++;
            return g;
        }
        if (point == 1) {sum = k[3];}
        if (point == 2) {sum = k[3]*10+k[2];}
        if (point == 3) {sum = k[3]*100 + k[2]*10 + k[1]; }
        if (sum > 255 || sum < 0) {
            g++;
            return g;
        }
        i++;

    }
    return g;
}

HashTable* create_hash_table() {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = 0;
    table->capacity = 3;
    table->num_buckets = 3;
    table->buckets = (ListNode**) calloc(table->num_buckets, sizeof(ListNode*));
    table->head = NULL;
    table->tail = NULL;
    return table;
}

int move_to_head_in_cash(HashTable* table, const char* key, const char* value)
{
    int ch = 0;
    int index = hash(key, table->num_buckets);
    ListNode *node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            free(node->value);
            node->value = (char *) malloc(strlen(value) + 1);
            strcpy(node->value, value);
            // Move the node to the head of the list
            if (node != table->head) {

                if (node == table->tail) {
                    table->tail = node->prev;
                }
                if (node->prev != NULL) {
                    node->prev->next = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = node->prev;
                }
                node->prev = NULL;
                node->next = table->head;
                table->head->prev = node;
                table->head = node;
            }
            ch++;
            return ch;
        }
        node = node->next;
    }
    return ch;
}

void putt(HashTable* table, const char* key, const char* value)
{
    int index = hash(key, table->num_buckets);

    ListNode *new_node = (ListNode *) malloc(sizeof(ListNode));
    new_node->key = (char *) malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = (char *) malloc(strlen(value) + 1);
    strcpy(new_node->value, value);
    new_node->prev = NULL;

    if (table->head != NULL) {
        table->head->prev = new_node;
    }
    new_node->next = table->head;
    table->head = new_node;
    table->size++;

    if (table->buckets[index] != NULL) {
        table->buckets[index]->prev = new_node;
    }
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;

    ListNode* dop_tail = table->head;
    while (dop_tail->next != NULL) {
        dop_tail = dop_tail->next;
    }
    table->tail = dop_tail;

    table->head = table->buckets[index];

}

void full_cash(HashTable* table)
{
    if (table->size > table->capacity) {
        ListNode *evict_node = table->tail;

        table->tail = evict_node->prev;
        if (table->tail->next != NULL) {
            table->tail->next = NULL;
            free(table->tail->next);
        }
        int evict_index = hash(evict_node->key, table->num_buckets);
        if (table->buckets[evict_index] == evict_node) {
            table->buckets[evict_index] = evict_node->next;
        }
        if (evict_node->prev != NULL) {
            evict_node->prev->next = evict_node->next;
        }
        if (evict_node->next != NULL) {
            evict_node->next->prev = evict_node->prev;
        }
        free(evict_node->key);
        free(evict_node->value);
        free(evict_node);
        table->size--;
    }
}

char* get(HashTable* table, const char* key)
{
    int index = hash(key, table->num_buckets);
    ListNode *node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (node != table->head) {

                ListNode *dop_tail = table->buckets[index];
                if (dop_tail == table->tail) {
                    while (dop_tail->prev->next != NULL) {
                        dop_tail->prev = dop_tail->prev->next;
                    }
                    table->tail = dop_tail->prev;
                }

                if (node->prev != NULL) {
                    node->prev->next = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = node->prev;
                }
                node->prev = NULL;
                node->next = table->head;
                table->head->prev = node;
                table->head = node;
                table->buckets[index] = node;
            }
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

char* find_IP_add(const char* ip_ent)
{
    FILE* fp;
    fp = fopen("input.txt", "r");
    int n = 3;
    int count = 0;
    char buff[n];
    char* kk;
    char* vv;
    while (fp!=NULL && !feof(fp)) {
        fscanf(fp, "%255s", buff);
        if (count == 0) {
            kk = (char*)malloc((strlen(buff)+2)*sizeof(char));
            strcpy(kk, buff);
        }
        if (count == 3) {
            vv = (char*)malloc((strlen(buff)+1)*sizeof(char));
            strcpy(vv, buff);
            if (strcmp(vv, ip_ent) == 0) {
                free(vv);
                fclose(fp);
                return kk;
            }
            count = 0;
        }
        else {
            count++;
        }
    }
    if (fp!=NULL) {fclose(fp);}
    return NULL;
}

void add_in_file(HashTable* table, FILE* f, char* domen, char* IP)
{
    printf("We don't have this information in database, sorry! You can add it!\n");
    printf("Do you want to add it? (1 - yes, 0 - no)\n");
    int ch;
    scanf("%d", &ch);
    if (ch == 1) {
        printf("Enter information about what you want to add in database:\n");
        if (IP == NULL) {
            printf("IP:\n");
            int n=1000;
            char *ip_ent = (char*)calloc(n, sizeof(char));
            get_str(ip_ent, n+1);
            get_str(ip_ent, n+1);
            while (input_check(ip_ent) != 0) {
                printf("Try again!\n");
                get_str(ip_ent, n+1);
            }
            char* t;
            t = find_IP_add(ip_ent);
            if (t == NULL) {
                fprintf(f, "\n%s\tIN\tA\t%s", domen, ip_ent);
            }
            else {
                fprintf(f, "\n%s\tIN\tCNAME\t%s", domen, t);
            }
            if (move_to_head_in_cash(table, domen, ip_ent) == 0) {
                putt(table, domen, ip_ent);
                full_cash(table);
            }
            printf("Super we did it!\n");
            free(ip_ent);
            free(t);
        }
        if (domen == NULL) {
            printf("Domain:\n");
            int n=1000;
            char *domen_ent = (char*)calloc(n, sizeof(char));
            get_str(domen_ent, n+1);
            get_str(domen_ent, n+1);
            fprintf(f, "%s IN A %s\n", domen_ent, IP);
            if (move_to_head_in_cash(table, domen_ent, IP) == 0) {
                putt(table, domen_ent, IP);
                full_cash(table);
            }
            free(domen_ent);
        }
    }
}

void find_in_file (HashTable* table, char* domen, char* dop_domen)
{
    FILE* f;
    f = fopen("input.txt", "r");
    char buff[256];
    int count = 0;
    char* kk;
    char* vv;
    int check = 0;
    int ch = 0;
    while (f!=NULL && !feof(f) && check == 0) {
        fscanf(f, "%255s", buff);
        if (count == 0) {
            kk = (char*)malloc((strlen(buff)+2)*sizeof(char));
            strcpy(kk, buff);
        }
        if (count == 2 && strcmp(buff, "CNAME") == 0) {
            ch = 1;
        }
        if (count == 3) {
            vv = (char*)malloc(strlen(buff)*sizeof(char));
            strcpy(vv, buff);
            if (strcmp(kk, domen) == 0 && ch == 0) {
                if (move_to_head_in_cash(table, dop_domen, vv) == 0) {
                    putt(table, dop_domen, vv);
                    full_cash(table);
                }
                check = 1;
            }
            if (strcmp(kk, domen) == 0 && ch == 1) {
                ch = 2;
                check = 1;
            }
            if (ch != 0) {
                ch--;
            }
            count=0;
        }
        else {
            count++;
        }
        for (int tt = 0; tt < 256; tt++) {
              buff[tt] = 0;
        }
    }
    if (f!=NULL) {fclose(f);}
    if (ch == 1) {
        find_in_file(table, vv, domen);
    }
}

int find_IP(HashTable* table, char* domen)
{
    int ch = 0;
    char *value = get(table, domen);
    if (value != NULL) {
        printf("IP of this site: %s\n", value);
    }
    else {
        find_in_file(table, domen, domen);
        char *val = get(table, domen);
        if (val != NULL ) {
            printf("IP of this site: %s\n", val);
            return 0;
        }
        else {
            ch++;
        }
    }
    return ch;
}

void domain_by_IP(void)
{
    char needIP[16];
    printf("IP: ");
    scanf("%255s", &needIP);
    FILE* fp = fopen("input.txt", "r");
    printf("\n");
    int count = 0;
    int n = 3;
    char line[n];
    char domain[n];
    char ip[16];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if ( sscanf(line, "%255s IN A %255s", domain, ip) == 2 && strcmp(needIP, ip) == 0 && count == 0) {
            printf("%s\n", domain);
            count++;
            strcpy(needIP, domain);
        }
        if ( sscanf(line, "%255s IN CNAME %255s", domain, ip) == 2 && strcmp(needIP, ip) == 0 && count == 1)
        {
            printf("%s\n", domain);
        }
    }
    printf("\n");
    if (fp!=NULL) {fclose(fp);}
    if(count == 0)
    {
        printf("Try again!\n");
        domain_by_IP();
    }
}

void display_hash_table(const struct HashTable* hashtable)
{
    for (int i = 0; i < hashtable->num_buckets; i++) {
        printf("Bucket %d:\t", i);
        ListNode* current = hashtable->buckets[i];
        while (current != NULL) {
            printf("%s - %s\t", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

void display_cache(HashTable* hash_table) {
    printf("Cache:\n");
    ListNode* current = hash_table->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}


void menu()
{
    printf("1. Find IP.\n");
    printf("2. Find Domain by IP.\n");
    printf("3. Print cash.\n");
    printf("0. Finish programme.\n");
}

void free_hash_table(HashTable* table)
{
    ListNode* node = table->head;
    while (node != NULL) {
        ListNode* next = node->next;
        free(node->key);
        free(node);
        node = next;
    }
    free(table->buckets);
    free(table);
}
