#include "stack.h"

typedef struct node {
    elem_t data;
    struct node *next;
} *pnode_t, node_t;

typedef struct stack{
    pnode_t top;
    size_t capacity;
    size_t size;
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
} *pstack_t, stack_t;

// Function to create a new node
pnode_t new_node(elem_t data)
{
    pnode_t node = (pnode_t)malloc(sizeof(struct node));
    if(node == NULL){
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

// Function to create a new stack
pstack_t stack_create(size_t max_num_of_elem,
                      clone_t clone_func_t, 
                      destroy_t destroy_func_t,
                      print_t print_func_t)
{
    pstack_t stack = (pstack_t)malloc(sizeof(struct stack));
    
    if(stack == NULL){
        return NULL;
    }

    stack->top = NULL;
    stack->capacity = max_num_of_elem;
    stack->size = 0;
    stack->clone_func = clone_func_t;
    stack->destroy_func = destroy_func_t;
    stack->print_func = print_func_t;
    return stack;
}

// Function to destroy a stack
Result stack_destroy(pstack_t s)
{
    if (s == NULL)
        return FAIL;

    while (s->top != NULL) {
        stack_pop(s);
    }

    free(s);
    return SUCCESS;
}

// Function to push an element onto the stack
Result stack_push(pstack_t s, elem_t e)
{
    if (s == NULL || s->size >= s->capacity)
        return FAIL;

    pnode_t node = new_node(s->clone_func(e));
    if(node == NULL){
        return FAIL;
    }
    
    node->next = s->top;
    s->top = node;
    s->size++;

    return SUCCESS;
}

// Function to remove the top element from the stack
void stack_pop(pstack_t s)
{
    if (s == NULL || s->top == NULL)
        return;
    
    pnode_t node = s->top;

    if(s->size == 1){
        s->top = NULL;
    }
    
    else {
        s->top = node->next;
    }
    
    if (s->destroy_func != NULL)
        s->destroy_func(node->data);

    free(node);
    s->size--;
}

// Function to get the value of the top element of the stack
elem_t stack_peek(pstack_t s)
{
    if (s == NULL || s->top == NULL)
        return NULL;

    return s->top->data;
}

// Function to get the size of the stack
size_t stack_size(pstack_t s)
{
    if (s == NULL)
        return 0;

    return s->size;
}

// Function to check if the stack is empty
bool stack_is_empty(pstack_t s)
{
    if (s == NULL){
        return false;
    }
    if (s->top == NULL){
        return true;
    }
    return false;
}

// Function to get the maximum capacity of the stack
size_t stack_capacity(pstack_t s)
{
    if(s == NULL){
        return 0;
    }
    return (s->capacity) - (s->size);
}

// Function to print the elements of the stack
void stack_print(pstack_t s)
{
    if (s == NULL || s->print_func == NULL)
        return;

    node_t *node = s->top;

    while (node != NULL) {
        s->print_func(node->data);
        node = node->next;
    }
}
