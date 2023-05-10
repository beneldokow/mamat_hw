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

/**
*@fn pstack_t stack_create(size_t max_num_of_elem, clone_t clone_func_t,
*destroy_t destroy_func_t, print_t print_func_t)
*@brief Creates a new stack.
*@param max_num_of_elem The maximum number of elements that the stack can hold
*@param clone_func_t pointer to func that can clone an element in the stack
*@param destroy_func_t pointer to func that can destroy an element in the stack
*@param print_func_t pointer to func that can print an element in the stack
*@return A pointer to the newly created stack, or NULL if failed creating stack
*/

pstack_t stack_create(size_t max_num_of_elem,
                      clone_t clone_func_t,
                      destroy_t destroy_func_t, 
                      print_t print_func_t);

/**
 * @fn Result stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param s - pointer to the stack to destroy
 * @return Result of destruction, SUCCESS or FAIL
 */

Result stack_destroy(pstack_t s);

/**
*@fn Result stack_push(pstack_t s, elem_t e)
*@brief Pushes an element onto the given stack.
*@param s A pointer to the stack onto which the element should be pushed.
*@param e A pointer to the element to push.
*@return SUCCESS if successfully pushed onto the stack, FAIL otherwise.
*/

Result stack_push(pstack_t s, elem_t e);

/**
*@fn void stack_pop(pstack_t s)
*@brief Pops the top element off the given stack.
*@param s A pointer to the stack from which to pop the top element.
*@return none
*/

void stack_pop(pstack_t s);

/**
*@fn elem_t stack_peek(pstack_t s)
*@brief Returns the top element of the given stack without removing it.
*@param s A pointer to the stack from which to peek the top element.
*@return A pointer to the top element of the stack, NULL in case of failure.
*/

elem_t stack_peek(pstack_t s);

/**
*@fn size_t stack_size(pstack_t s)
*@brief Returns the number of elements in the given stack.
*@param s A pointer to the stack of interest.
*@return The number of elements in the stack or 0 in case of failure.
*/

size_t stack_size(pstack_t s);

/**
*@fn bool stack_is_empty(pstack_t s)
*@brief checks if the stack is empty
*@param s A pointer to the stack of interest.
*@return true if the stack is empty, false otherwise.
*/

bool stack_is_empty(pstack_t s);

/**
*@fn size_t stack_capacity(pstack_t
*@brief Returns the maximum number of elements that the given stack can hold.
*@param s A pointer to the stack of interest.
*@return the number of available sapces in the stack, 0 in case of failure
*/

size_t stack_capacity(pstack_t s);

/**
*@fn void stack_print(pstack_t s)
*@brief Prints the elements of the given stack in order from top to bottom.
*@param s A pointer to the stack to print.
*@return none
*/

void stack_print(pstack_t s);

#endif /* __STACK__ */
