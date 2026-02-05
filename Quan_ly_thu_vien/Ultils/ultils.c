#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ultils.h"

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int getIntInput(const char* prompt) {
    int value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr;
            value = (int)strtol(buffer, &endptr, 10);
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                return value;
            }
        }
        printf(">> Loi: Vui long nhap mot so nguyen hop le!\n");
    }
}

void getStringInput(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        removeNewline(buffer);
    }
}