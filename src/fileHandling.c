#include "labirinto.h"

void trimTrailingSpaces(char *str) {
    int length = strlen(str);
    while (length > 0
           && (str[length - 1] == ' ' || str[length - 1] == '\n' || str[length - 1] == '\r')) {
        str[--length] = '\0';
    }
}

char* loadDescription(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *description = malloc(length + 1);
    if (description) {
        size_t bytesRead = fread(description, 1, length, file);
        description[bytesRead] = '\0';
        trimTrailingSpaces(description);
    } else {
        perror("Erro ao alocar memória");
    }

    fclose(file);
    return description;
}
