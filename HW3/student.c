#include "student.h"
#include <string.h>
#include <stdio.h>


elem_t student_clone(elem_t e) {
    pstudent_t ps = (pstudent_t)e;
    pstudent_t new_ps = (pstudent_t)malloc(sizeof(student_t));
    if (new_ps == NULL) {
        return NULL;
    }
    new_ps->name = (char*)malloc(strlen(ps->name) + 1);
    if (new_ps->name == NULL) {
        free(new_ps);
        return NULL;
    }
    strcpy(new_ps->name, ps->name);
    new_ps->age = ps->age;
    new_ps->id = ps->id;
    return (elem_t)new_ps;
}

void student_destroy(elem_t e) {
    pstudent_t ps = (pstudent_t)e;
    if (ps == NULL) {
        return;
    }
    free(ps->name);
    free(ps);
}

void student_print(elem_t e) {
    pstudent_t ps = (pstudent_t)e;
    printf("student name: %s, age: %d, id: %d.\n", ps->name, ps->age, ps->id);
}

