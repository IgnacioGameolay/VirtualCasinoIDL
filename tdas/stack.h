#ifndef STACK_H
#define STACK_H
#include "list.h"

typedef List Stack;

Stack *stack_create(Stack *stack);

void stack_push(Stack *stack, void *data);

void *stack_top(Stack *stack);

void *stack_pop(Stack *stack);

void stack_clean(Stack *stack);

#endif /* STACK_H */