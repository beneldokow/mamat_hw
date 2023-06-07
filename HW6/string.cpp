#include "string.h"
#include <cstring>

String :: String() : data(NULL) ,length(0) {
}

String :: String(const String &str) {
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
}

String :: String(const char *str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

String :: ~String() {
    delete[] data;
}

String& String :: operator=(const String &rhs) {
    if (this != &rhs) {
        if(data != NULL){
            delete[] data;
        }
        length = rhs.length;
        data = new char[length + 1];
        strcpy(data, rhs.data);
    }
    return *this;
}

String& String :: operator=(const char *str) {
    if(data != NULL){
        delete[] data;
    }
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
    return *this;
}

bool String :: equals(const String &rhs) const {
    return strcmp(data, rhs.data) == 0;
}

bool String :: equals(const char *rhs) const {
    return strcmp(data, rhs) == 0;
}

void String :: split(const char *delimiters, String **output, size_t *size) const {
    char *str = new char[length + 1];
    if(data == NULL){
        return;
    }
    strcpy(str, data);
    if(delimiters == NULL){
        return;
    }
    char *token = strtok(str, delimiters);
    if(size != NULL){
        *size = 0;
        while (token != NULL) {
            (*size)++;
            token = strtok(NULL, delimiters);
        }
    }
    if (output != NULL) {
        *output = new String[*size];
        strcpy(str, data);
        token = strtok(str, delimiters);
        for (int i = 0; i < (int)*size; i++) {
            (*output)[i] = token;
            token = strtok(NULL, delimiters);
        }
    }
    delete[] str;
}

int String :: to_integer() const {
    if(data == NULL){
        return -1;
    }
    return atoi(data);
}

String String::trim() const {
    int start = 0;
    while (data[start] == ' ') {
        start++;
    }
    int end = length - 1;
    while (end >= start && data[end] == ' ') {
        end--;
    }

    char *str = new char[end - start + 2];
    strncpy(str, data + start, end - start + 1);
    str[end - start + 1] = '\0';
    String s(str);
    delete[] str;
    return s;
}