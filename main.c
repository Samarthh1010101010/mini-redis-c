#include <stdio.h>  // Use standard input/output functions like printf and scanf.
#include <string.h> // Use string utilities like strcmp.
#include "store.h"  // Use the hash table functions declared in store.h.

int main() { // Program entry point.
    HashTable *table = create_table(); // Create the in-memory key-value store.

    char command[16]; // Buffer to store the command word (e.g., SET, GET).
    char key[128]; // Buffer to store the key string.
    char value[128]; // Buffer to store the value string.

    printf("Mini Redis (Phase 1)\n"); // Print a title banner.
    printf("Commands: SET key value | GET key | DEL key | EXIT\n"); // Print usage help.

    while (1) { // Loop forever until EXIT is entered.
        printf("> "); // Show a prompt.
        scanf("%s", command); // Read the command word from the user.

        if (strcmp(command, "SET") == 0) { // If the command is SET...
            scanf("%s %s", key, value); // Read the key and the value.
            set(table, key, value); // Store the key-value pair.
            printf("OK\n"); // Confirm success.
        }
        else if (strcmp(command, "GET") == 0) { // If the command is GET...
            scanf("%s", key); // Read the key.
            char *result = get(table, key); // Look up the value by key.
            if (result) // If a value was found...
                printf("%s\n", result); // Print the value.
            else // Otherwise...
                printf("(nil)\n"); // Print a Redis-like not-found message.
        }
        else if (strcmp(command, "DEL") == 0) { // If the command is DEL...
            scanf("%s", key); // Read the key.
            del(table, key); // Delete the key from the table.
            printf("Deleted\n"); // Confirm deletion.
        }
        else if (strcmp(command, "EXIT") == 0) { // If the command is EXIT...
            break; // Leave the loop and end the program.
        }
        else { // Any other command...
            printf("Unknown command\n"); // Tell the user the command is invalid.
        }
    }

    free_table(table); // Free all memory used by the table.
    return 0; // Indicate successful program exit.
} // End of main function.
