#include "string.h"
#include <cstring>

/**
 * @brief Construct a new String object
 * @return empty String object.
*/
String :: String() : data(NULL) ,length(0) {
}

/**
 * @brief Construct a new String object
 * @param str - String object to copy.
 * @return copied String object.
*/
String :: String(const String &str) {
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
}

/**
 * @brief Construct a new String object
 * @param str - char* to copy.
 * @return copied String object.
*/
String :: String(const char *str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

/**
 * @brief Destroy the String object
*/
String :: ~String() {
    delete[] data;
}

/**
 * @brief set the String object to be equal to the given String object.
 * @param rhs - String object to copy.
 * @return copied String object.
*/
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

/**
 * @brief set the String object to be equal to the given char*.
 * @param str - char* to copy.
 * @return copied String object.
*/
String& String :: operator=(const char *str) {
    if(data != NULL){
        delete[] data;
    }
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
    return *this;
}

/**
 * @brief compare two String objects.
 * @param rhs - String object to compare to.
 * @return true if the two String objects are equal, false otherwise.
*/
bool String :: equals(const String &rhs) const {
    return strcmp(data, rhs.data) == 0;
}

/**
 * @brief compare two String objects.
 * @param rhs - char* to compare to.
 * @return true if the two String objects are equal, false otherwise.
*/
bool String :: equals(const char *rhs) const {
    return strcmp(data, rhs) == 0;
}

/**
 * @brief split the String object by the given delimiters.
 * @param delimiters - ptr to delimiters to split by.
 * @param output - ptr to array of String objects to store the split String objects.
 * @param size - ptr to size_t to store the size of the output array.
*/
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

/**
 * @brief turn the String object to an integer.
 * @return the integer value of the String object.
*/
int String :: to_integer() const {
    if(data == NULL){
        return -1;
    }
    return atoi(data);
}

/**
 * @brief remove all spaces from the beginning and end of String object.
 * @return the trimmed String object.
 */
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