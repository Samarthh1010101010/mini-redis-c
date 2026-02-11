#include <stdio.h> // Use standard input/output like printf.
#include <stdlib.h> // Use memory allocation and exit.
#include <string.h> // Use string utilities like strcmp and strdup.
#include "store.h" // Use the hash table types and function declarations.

static int bucket_length(Entry *head) { // Count entries in a bucket list.
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Hash function
unsigned int hash(const char *key) { // Turn a string key into a bucket index.
    unsigned int hash = 0; // Start the hash value at 0.
    while (*key) { // Loop until the end of the string.
        hash = (hash * 31) + *key; // Mix in the next character.
        key++; // Move to the next character.
    }
    return hash % TABLE_SIZE; // Map the hash to a valid bucket index.
}

// Create hash table
HashTable* create_table() { // Allocate and initialize a new table.
    HashTable *table = malloc(sizeof(HashTable)); // Allocate memory for the table.
    if (!table) { // Check if allocation failed.
        printf("Memory allocation failed\n"); // Print an error message.
        exit(1); // Stop the program with an error code.
    }

    for (int i = 0; i < TABLE_SIZE; i++) { // Initialize each bucket.
        table->buckets[i] = NULL; // Start each bucket as empty.
    }
    return table; // Return the initialized table.
}

// SET key value
void set(HashTable *table, const char *key, const char *value) { // Insert or update a key.
    unsigned int index = hash(key); // Find the bucket for this key.
    printf("Key '%s' goes to bucket %d\n", key, index);
    Entry *current = table->buckets[index]; // Start at the first entry in that bucket.

    // Update if key exists
    while (current) { // Walk through the linked list in this bucket.
        if (strcmp(current->key, key) == 0) { // If the key matches...
            free(current->value); // Free the old value.
            current->value = strdup(value); // Copy and store the new value.
            printf("Key '%s' stored in bucket %u (length %d)\n",
                   key,
                   index,
                   bucket_length(table->buckets[index]));
            return; // Done updating.
        }
        current = current->next; // Move to the next entry.
    }

    // Insert new entry
    Entry *newEntry = malloc(sizeof(Entry)); // Allocate a new entry node.
    newEntry->key = strdup(key); // Copy and store the key string.
    newEntry->value = strdup(value); // Copy and store the value string.
    newEntry->next = table->buckets[index]; // Point to the current head of the list.
    table->buckets[index] = newEntry; // Make the new entry the new head.
    printf("Key '%s' stored in bucket %u (length %d)\n",
           key,
           index,
           bucket_length(table->buckets[index]));
}

// GET key
char* get(HashTable *table, const char *key) { // Find the value for a key.
    unsigned int index = hash(key); // Find the bucket for this key.
    Entry *current = table->buckets[index]; // Start at the first entry in that bucket.

    while (current) { // Walk through the linked list.
        if (strcmp(current->key, key) == 0) { // If the key matches...
            return current->value; // Return the stored value.
        }
        current = current->next; // Move to the next entry.
    }
    return NULL; // Return NULL if the key was not found.
}

// DEL key
void del(HashTable *table, const char *key) { // Remove a key and its value.
    unsigned int index = hash(key); // Find the bucket for this key.
    Entry *current = table->buckets[index]; // Start at the first entry in that bucket.
    Entry *prev = NULL; // Keep track of the previous entry.

    while (current) { // Walk through the linked list.
        if (strcmp(current->key, key) == 0) { // If the key matches...
            if (prev) // If this is not the first node...
                prev->next = current->next; // Skip over the current node.
            else // Otherwise, we are removing the head node...
                table->buckets[index] = current->next; // Update the bucket head.

            free(current->key); // Free the stored key string.
            free(current->value); // Free the stored value string.
            free(current); // Free the entry itself.
            return; // Done deleting.
        }
        prev = current; // Move prev to current before advancing.
        current = current->next; // Move to the next entry.
    }
}

// Free entire table
void free_table(HashTable *table) { // Release all memory used by the table.
    for (int i = 0; i < TABLE_SIZE; i++) { // Loop over each bucket.
        Entry *current = table->buckets[i]; // Start at the first entry in the bucket.
        while (current) { // Walk through the linked list.
            Entry *temp = current; // Save the current entry.
            current = current->next; // Move to the next entry.
            free(temp->key); // Free the key string.
            free(temp->value); // Free the value string.
            free(temp); // Free the entry node.
        }
    }
    free(table); // Free the table structure itself.
}
