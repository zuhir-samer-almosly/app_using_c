#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LEN 1024

void print_menu(void) {
    printf("\n=== Text App ===\n");
    printf("1. Enter text\n");
    printf("2. Show text\n");
    printf("3. Clear text\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    char text[MAX_TEXT_LEN] = {0};
    char input[MAX_TEXT_LEN];
    int choice;

    printf("Welcome to the C Text App!\n");

    while (1) {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            /* clear invalid input */
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        /* consume newline */
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter text: ");
                if (fgets(input, sizeof(input), stdin) != NULL) {
                    /* remove trailing newline */
                    input[strcspn(input, "\n")] = '\0';
                    snprintf(text, sizeof(text), "%s", input);
                    printf("Text saved.\n");
                }
                break;

            case 2:
                if (text[0] == '\0') {
                    printf("No text entered yet.\n");
                } else {
                    printf("Stored text: %s\n", text);
                }
                break;

            case 3:
                memset(text, 0, sizeof(text));
                printf("Text cleared.\n");
                break;

            case 4:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Please choose 1-4.\n");
                break;
        }
    }

    return 0;
}
