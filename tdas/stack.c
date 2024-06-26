#include "list.h"
#include "stack.h"

Stack *stack_create(Stack *stack) { return list_create(); }

void stack_push(Stack *stack, void *data) { list_pushFront(stack, data); }

void *stack_top(Stack *stack) { return list_first(stack); }

void *stack_pop(Stack *stack) { return list_popFront(stack); }

void stack_clean(Stack *stack) { list_clean(stack); }
