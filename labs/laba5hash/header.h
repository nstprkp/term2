#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 3;
#define SIZE 256;

typedef struct ListNode {
    char* key;
    char* value;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

typedef struct HashTable {
    int size;
    int capacity;
    int num_buckets;
    ListNode** buckets;
    ListNode* head;
    ListNode* tail;
} HashTable;

char* get_str(char *s, int k);
unsigned int hash(const char* key, int num_buckets);
HashTable* create_hash_table();
int move_to_head_in_cash(HashTable* table, char* key, char* value);
void putt(HashTable* table, char* key, char* value);
void full_cash(HashTable* table);
char* get(HashTable* table, char* key);
void add_in_file(HashTable* table, FILE* f, char* domen, char* IP);
void find_in_file (HashTable* table, char* domen, char* dop_domen);
int find_IP(HashTable* table, char* domen);
void domain_by_IP(void);
void display_hash_table(HashTable* hashtable);
void display_cache(HashTable* hash_table);
void menu();
void free_hash_table(HashTable* table);
