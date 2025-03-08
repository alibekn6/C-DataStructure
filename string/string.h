#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *data;
    size_t length;
} String;


String create(const char *text);
void printStr(const String str);
size_t len(const String str);
void append(String *str, const char *text);
void freeStr(String *str);

#endif