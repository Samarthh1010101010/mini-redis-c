#ifndef STORE_H
#define STORE_H

#define TABLE_SIZE 5
typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
} HashTable;

// Hash table functions
HashTable* create_table();
void set(HashTable *table, const char *key, const char *value);
char* get(HashTable *table, const char *key);
void del(HashTable *table, const char *key);
void free_table(HashTable *table);

#endif
