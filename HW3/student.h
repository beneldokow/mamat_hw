#ifndef __STUDENT__
#define __STUDENT__

#include "stack.h"
#include "stdlib.h"

typedef struct student {
	char *name;
	int age;
    int id;
}*pstudent_t, student_t;

/**
*@fn elem_t student_clone (elem_t e)
*@brief Creates and returns a clone of the given student element.
*@param e A pointer to the student element to clone.
*@return A pointer to the cloned student element, or NULL in case of failure.
*/

elem_t student_clone (elem_t e);

/**
*@fn void student_destroy(elem_t e)
*@brief Frees the memory used by the given student element.
*@param e A pointer to the student element to destroy.
*@return none
*/

void student_destroy(elem_t e);

/**
*@fn void student_print(elem_t e)
*@brief Prints the given student element.
*@param e A pointer to the student element to print.
*@return none
*/

void student_print(elem_t e);

#endif /* __STUDENT__ */ 