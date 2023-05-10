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

/**
*@fn pnode_t new_node(elem_t data)
*@brief Creates a new node.
*@param data pointer to data for new node
*@return the new node, or NULL if failed creating node
*/
pnode_t new_node(elem_t data)
{
    pnode_t node = (pnode_t)malloc(sizeof(struct node));
    if(node == NULL){
        fprintf(stderr, "Error: memory allocation failure\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

pstack_t stack_create(size_t max_num_of_elem,
                      clone_t clone_func_t, 
                      destroy_t destroy_func_t,
                      print_t print_func_t)
{
    pstack_t stack = (pstack_t)malloc(sizeof(struct stack));
    
    if(stack == NULL){
        fprintf(stderr, "Error: memory allocation failure\n");
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

Result stack_destroy(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_destroy.\n");
        return FAIL;
    }

    while (s->top != NULL) {
        stack_pop(s);
    }

    free(s);
    return SUCCESS;
}

Result stack_push(pstack_t s, elem_t e)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_push\n");
        return FAIL;
    }

    if (s->size >= s->capacity){
        fprintf(stderr, "Error: stack is full\n");
        return FAIL;
    }

    if (e == NULL){
        fprintf(stderr, "Error: NULL ptr to elem passed to stack_push\n");
        return FAIL;
    }

    pnode_t node = new_node(s->clone_func(e));
    if(node == NULL){
        fprintf(stderr, "Error: failed to create new node\n");
        return FAIL;
    }
    
    node->next = s->top;
    s->top = node;
    s->size++;

    return SUCCESS;
}

void stack_pop(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_pop\n");
        return;
    }
    if (s->top == NULL){
        fprintf(stderr, "Error: popping empty stack\n");
        return;
    }    
    pnode_t node = s->top;

    if(s->size == 1){
        s->top = NULL;
    }
    
    else {
        s->top = node->next;
    }
    
    if (s->destroy_func != NULL){
        s->destroy_func(node->data);
    }

    else{
        fprintf(stderr, "Error: ptr to destroy func is NULL\n");
    }
    free(node);
    s->size--;
}

elem_t stack_peek(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_peek\n");
        return NULL;
    }
    if (s->top == NULL){
        fprintf(stderr, "Error: peeking empty stack\n");
        return NULL;
    } 

    return s->top->data;
}

size_t stack_size(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_size\n");
        return 0;
    }

    return s->size;
}

bool stack_is_empty(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_is_empty\n");
        return false;
    }
    if (s->top == NULL){
        return true;
    }
    return false;
}

size_t stack_capacity(pstack_t s)
{
    if(s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_capacity\n");
        return 0;
    }
    return (s->capacity) - (s->size);
}


void stack_print(pstack_t s)
{
    if (s == NULL){
        fprintf(stderr, "Error: NULL ptr to stack passed to stack_print\n");
        return;
    }

    if (s->print_func == NULL){
        fprintf(stderr, "Error: ptr to print func is NULL\n");
        return;
    }
    

    node_t *node = s->top;

    while (node != NULL) {
        s->print_func(node->data);
        node = node->next;
    }
}