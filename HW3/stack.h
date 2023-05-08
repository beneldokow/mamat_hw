#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
#include "stdlib.h"
#include "stdio.h"

typedef void *elem_t;

typedef enum { SUCCESS = 0, FAIL } Result; 

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);

struct stack;

pstack_t stack_create(size_t max_num_of_elem, clone_t clone_func_t,
destroy_t destroy_func_t, print_t print_func_t);

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return none
 */

Result stack_destroy(pstack_t s);
Result stack_push(pstack_t s, elem_t e);
void stack_pop(pstack_t s);
elem_t stack_peek(pstack_t s);
size_t stack_size(pstack_t s);
bool stack_is_empty(pstack_t s);
size_t stack_capacity(pstack_t s);
void stack_print(pstack_t s);

#endif /* __STACK__ */