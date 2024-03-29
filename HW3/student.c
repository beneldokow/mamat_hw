#include "student.h"
#include <string.h>
#include <stdio.h>

elem_t student_clone(elem_t e) {
    if(e == NULL){
        fprintf(stderr, "Error: null element passed to student_clone.\n");
        return NULL;
    }
    pstudent_t ps = (pstudent_t)e;

    if(ps->age < 0 || ps->id < 0){
        fprintf(stderr, "Error: invalid age or id in student_clone.\n");
        return NULL;
    }

    pstudent_t new_ps = (pstudent_t)malloc(sizeof(student_t));
    if (new_ps == NULL) {
        fprintf(stderr, "Error: allocation failed in student_clone.\n");
        return NULL;
    }
    new_ps->name = (char*)malloc(strlen(ps->name) + 1);
    if (new_ps->name == NULL) {
        fprintf(stderr, "Error: allocation failed in student_clone.\n");
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
        fprintf(stderr, "Error: null element passed to student_destroy.\n");
        return;
    }
    free(ps->name);
    free(ps);
}

void student_print(elem_t e) {
    if(e == NULL){
        fprintf(stderr, "Error: null element passed to student_print.\n");
        return;
    }
    pstudent_t ps = (pstudent_t)e;
    printf("student name: %s, age: %d, id: %d.\n", ps->name, ps->age, ps->id);
}
