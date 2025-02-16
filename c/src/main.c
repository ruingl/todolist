#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "database.h"
#include "bprint.h"

void home();
void list();
void add();

void home() {
    while (1) {
        system("clear");
        bprint("To-do List —— Menu\n");
        printf("\n");

        printf("1. See To-do List\n");
        printf("2. Add To-do\n");
        printf("3. Exit\n");
        printf("\n");

        char action[3];

        printf("$: ");
        if (fgets(action, sizeof(action), stdin)) {
            action[strcspn(action, "\n")] = '\0';
        }
        printf("\n");

        if (strcmp(action, "1") == 0) {
            list();
        } else if (strcmp(action, "2") == 0) {
            add();
        } else if (strcmp(action, "3") == 0) {
            printf("Goodbye\n");
            break;
        } else {
            printf("Invalid action.");
            sleep(1);
        }
    }
}

void list() {
    while (1) {
        system("clear");
        bprint("To-do List —— List\n");
        printf("\n");

        print_list();
        printf("\n");

        printf("Done! Go back to menu? (y/n)\n");

        char action[3];

        printf("$: ");
        if (fgets(action, sizeof(action), stdin)) {
            action[strcspn(action, "\n")] = '\0';
        }
        printf("\n");

        if (strcasecmp(action, "y") == 0) {
            home();
        } else if (strcasecmp(action, "n") == 0) {
            printf("Goodbye\n");
            break;
        } else {
            printf("Invalid action.\n");
            sleep(1);
        }
    }
}

void add() {
    while (1) {
        system("clear");
        bprint("To-do List —— Add");
        printf("\n");

        printf("What you wanna add?\n");

        char todo[100];

        printf("$: ");
        if (fgets(todo, sizeof(todo), stdin)) {
            todo[strcspn(todo, "\n")] = '\0';
        }
        printf("\n");

        if (add_todo(todo) == 1) {
            printf("Done! Go back to menu? (y/n)\n");

            char action[3];

            printf("$: ");
            if (fgets(action, sizeof(action), stdin)) {
                action[strcspn(action, "\n")] = '\0';
            }
            printf("\n");

            if (strcasecmp(action, "y") == 0) {
                home();
            } else if (strcasecmp(action, "n") == 0) {
                printf("Goodbye\n");
                break;
            } else {
                printf("Invalid action.\n");
                sleep(1);
            }
        } else {
            printf("[-] Cant add todo.\n");
            break;
        }
    }
}

int main() {
    home();
    return 0;
}
