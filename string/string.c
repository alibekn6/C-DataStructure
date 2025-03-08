#include "string.h"

String create(const char *text) {
    String str;
    str.length = strlen(text);
    str.data = malloc(str.length + 1);

    if (str.data) {
        strcpy(str.data, text);
    }
    return str;
}

void printStr(const String str) {
    printf("%s\n", str.data);
}

size_t getStringLength(const String str) {
    return str.length;
}

void append(String *str, const char *text) {
    size_t newLength = str->length + strlen(text);
    str->data = realloc(str->data, newLength+1);
    if (str->data) {
        strcat(str->data, text);
        str->length = newLength;
    }
}

void freeStr(String *str) {
    free(str->data);
    str->data = NULL;
    str->length = 0;
}