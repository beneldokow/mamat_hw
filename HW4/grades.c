#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked-list.h"
#include "grades.h"

struct course
{
    char *course_name;
    int grade;
};

struct student{
    int id;
    char *name;
    struct list *courses;
};

struct grades{
    struct list *students;
};

typedef struct grades *pgrades_t;
typedef struct student *pstudent_t;
typedef struct course *pcourse_t;

int course_clone(void *course,void **output);
void course_destroy(void* course);
int student_clone(void *student, void **output);
void student_destroy(void* student);

/**
 * @brief clones a course struct.
 * @param course - the course to clone.
 * @param[out] output - points to pointer to the new course.
 * @return 0 on success, 1 on failure.
 */
int course_clone(void *course,void **output) {
    if (course == NULL) {
        return 1;
    }
    if(output == NULL){
        return 1;
    }

    pcourse_t c = (pcourse_t)course;
    pcourse_t new_course = (pcourse_t)malloc(sizeof(struct course));
    
    if (new_course == NULL) {
        course_destroy((void*)new_course);
        return 1;
    }

    new_course->course_name = (char*)malloc(strlen(c->course_name) + 1);
    new_course->grade = c->grade;

    if (new_course->course_name == NULL) {
        course_destroy((void*)new_course);
        return 1;
    }

    strcpy(new_course->course_name, c->course_name);

    *output = (void*)new_course;
    return 0;
}

/**
 * @brief destroys a course struct.
 * @param course - the course to destroy.
 */
void course_destroy(void* course) {
    if (course == NULL) {
        return;
    }

    free(((pcourse_t)course)->course_name);
    free(course);
}

/**
 * @brief clones a student struct.
 * @param student - the student to clone.
 * @param[out] output - points to pointer to the new student.
 * @return 0 on success, 1 on failure.
 */
int student_clone(void* student,void **output) {
  
    if(student == NULL) {
        return 1;
    }


    pstudent_t s = (pstudent_t)student;
    if(s->name == NULL){
        return 1;
    }

    pstudent_t new_student = (pstudent_t)malloc(sizeof(struct student));
    
    if (new_student == NULL) {
        student_destroy((void*)new_student);
        return 1;
    }

    new_student->id = s->id;
    new_student->name = (char*)malloc(strlen(s->name) + 1);
    
    if(new_student->name == NULL){
        student_destroy((void*)new_student);
        return 1;
    }

    strcpy(new_student->name, s->name);
    new_student->courses = list_init(course_clone, course_destroy);
    
    struct iterator *it_student = list_begin(s->courses);
    if(it_student == NULL && list_size(s->courses) != 0){
        student_destroy(new_student);
        return 1;
    }

    if(!list_push_front(new_student->courses,list_get(it_student))){
        student_destroy((void*)new_student);
        return 1;
    }

    struct iterator *it_new_student = list_begin(s->courses);
    if(it_new_student == NULL && list_size(s->courses) != 0){
        student_destroy((void*)new_student);
        return 1;
    }
    
    for(int i = 1; i < list_size(s->courses); i++){
        if(!list_insert(new_student->courses,it_new_student, list_get(it_student))){
            student_destroy((void*)new_student);
            return 1;
        }

        it_student = list_next(it_student);
        it_new_student = list_next(it_new_student);
        if(it_student == NULL || it_new_student == NULL){
            student_destroy((void*)new_student);
            return 1;
        }
    }
    
    if (new_student->name == NULL || new_student->courses == NULL) {
        student_destroy((void*)new_student);
        return 1;
    }

    *output = (void*)new_student;
    return 0;
}

/**
 * @brief destroys a student struct.
 * @param student - the student to destroy.
 */
void student_destroy(void* student) {
    if (student == NULL) {
        return;
    }

    list_destroy(((pstudent_t)student)->courses);
    free(((pstudent_t)student)->name); 
    free(student);
}

struct grades* grades_init() {
    struct grades *grades = (pgrades_t) malloc(sizeof(struct grades));
    if (grades == NULL) {
        grades_destroy(grades);
        return NULL;
    }
    
    grades->students = list_init(student_clone, student_destroy);
    
    if (grades->students == NULL) {
        grades_destroy(grades);
        return NULL;
    }

    return grades;
}

void grades_destroy(struct grades *grades) {
    if (grades == NULL) {
        return;
    }
    list_destroy(grades->students);
    free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id) {
    
    if (grades == NULL) {
        return 1;
    }

    pstudent_t new_student = (pstudent_t)malloc(sizeof(struct student));
    if (new_student == NULL) {
        student_destroy((void*)new_student);
        return 1;
    }

    new_student->id = id;
    new_student->name = (char*)malloc(strlen(name) + 1);
    new_student->courses = list_init(course_clone, course_destroy);

    if (new_student->name == NULL || new_student->courses == NULL) {
        student_destroy((void*)new_student);
        return 1;
    }

    strcpy(new_student->name, name);

    struct iterator *it = list_begin(grades->students);
    if(list_size(grades->students) != 0 && it == NULL){
        student_destroy((void*)new_student);
        return 1;
    }

    while (it != NULL) {
        pstudent_t current = list_get(it);
        if (current->id == id) {
            student_destroy((void*)new_student);
            return 1;
        }
        it = list_next(it);
    }

    if(!list_push_front(grades->students, new_student)){
        student_destroy((void*)new_student);
        return 0;
    }
    student_destroy((void*)new_student);
    return 1;
}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade) {
    if(grade < 0 || grade > 100){
        return 1;
    }
    
    if (grades == NULL) {
        return 1;
    }
    
    struct iterator *it = list_begin(grades->students);
    if(list_size(grades->students) != 0 && it == NULL){
        return 1;
    }

    while (it != NULL) {
        pstudent_t current = list_get(it);
       
        if(current == NULL){
            return 1;
        }

        if (current->id == id) {
            
            pcourse_t new_course = (pcourse_t)malloc(sizeof(struct course));
            if (new_course == NULL) {
                course_destroy((void*)new_course);
                return 1;
            }

            new_course->course_name = (char*)malloc(strlen(name) + 1);
            new_course->grade = grade;

            if (new_course->course_name == NULL) {
                course_destroy((void*)new_course);
                return 1;
            }
            strcpy(new_course->course_name, name);

            struct iterator *course_it = list_begin(current->courses);
            if (course_it == NULL && list_size(current->courses) != 0) {
                course_destroy((void*)new_course);
                return 1;
            }

            for(int i = 0; i < list_size(current->courses); i++){  
                pcourse_t current_course = list_get(course_it);
                if(current_course == NULL){
                    course_destroy((void*)new_course);
                    return 1;
                }
                if(strcmp(current_course->course_name, name) == 0){
                    course_destroy((void*)new_course);
                    return 1;
                }
                course_it = list_next(course_it);
            }
            
            if(!list_push_front(current->courses, new_course)){
                course_destroy((void*)new_course);
                return 0;
            }

            course_destroy((void*)new_course);
            return 1;
        }
        it = list_next(it);
    }

    return 1;
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    
    if (grades == NULL) {
        *out = NULL;
        return -1;
    }

    struct iterator *it = list_begin(grades->students);
    if(list_size(grades->students) != 0 && it == NULL){
        *out = NULL;
        return -1;
    }

    while (it != NULL) {
       
        pstudent_t current = list_get(it);
        if(current == NULL){
            *out = NULL;
            return -1;
        }

        if (current->id == id) {
            if(list_size(current->courses) == 0){
                *out = (char*) malloc(strlen(current->name) + 1);
                strcpy(*out, current->name);
                return 0;
            }
            float sum = 0;
            int count = 0;
            
            struct iterator *course_it = list_begin(current->courses);
            if (course_it == NULL && list_size(current->courses) != 0) {
                *out = NULL;
                return -1;
            }

            while (course_it != NULL) {
                pcourse_t course = list_get(course_it);
                if(course == NULL){
                    *out = NULL;
                    return -1;
                }

                sum += course->grade;
                count++;
                course_it = list_next(course_it);
            }

            *out = (char*) malloc(strlen(current->name) + 1);
            strcpy(*out, current->name);
            return sum/count;
        }
        it = list_next(it);
    }
    *out = NULL;
    return -1;
}

int grades_print_student(struct grades *grades, int id){
    if (grades == NULL) {
        return 1;
    }

    struct iterator *it = list_begin(grades->students);
    if(list_size(grades->students) != 0 && it == NULL){
        return 1;
    }

    while (it != NULL) {
        pstudent_t current = list_get(it);
        if(current == NULL){
            return 1;
        }

        if (current->id == id) {
            printf("%s %d:", current->name, current->id);
            struct iterator *course_it = list_end(current->courses);
            
            if (course_it == NULL && list_size(current->courses) != 0) {
                return 1;
            }

            while (course_it != NULL) {
                pcourse_t course = list_get(course_it);
                if(course == NULL){
                    return 1;
                }
            
                course_it = list_prev(course_it);
            
                if(course_it == NULL){
                    printf(" %s %d", course->course_name, course->grade);
                    break;
                }
            
                else{
                    printf(" %s %d,", course->course_name, course->grade);
                }
            
            }
            printf("\n");
            return 0;
        }
        it = list_next(it);
    }
    return 1;
}

int grades_print_all(struct grades *grades){
    if (grades == NULL) {
        return 1;
    }

    struct iterator *it = list_end(grades->students);
    if(list_size(grades->students) != 0 && it == NULL){
        return 1;
    }

    while (it != NULL) {
        pstudent_t current = list_get(it);
        if(current == NULL){
            return 1;
        }

        printf("%s %d:", current->name, current->id);
        struct iterator *course_it = list_end(current->courses);
        
        if (course_it == NULL && list_size(current->courses) != 0) {
            return 1;
        }
    
        while (course_it != NULL) {
            pcourse_t course = list_get(course_it);
            if(course == NULL){
                return 1;
            }
            
            course_it = list_prev(course_it);
            if(course_it == NULL){
                printf(" %s %d", course->course_name, course->grade);
                break;
            }
            else{
                printf(" %s %d,", course->course_name, course->grade);
            }
            
        }
        printf("\n");
        it = list_prev(it);
    }
    return 0;
}   

        

