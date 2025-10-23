///
/// @file stack.c
/// @author Zentiph
/// @brief An implementation of a stack data type in C.
/// @version 1.0
/// @date 2025-10-22
///
/// @copyright Copyright (c) 2025
///
///

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../err/err.h"

typedef struct stack_s *stack_t;
#define ADT__STACK_IMPLEMENTATION
#include "stack.h"

struct stack_s {
   size_t capacity;
   size_t ptr;
   void **items;
};

static inline bool stack_is_full(const stack_t stack) {
   return stack->ptr >= stack->capacity;
}

static void stack_grow(stack_t stack) {
   size_t new_cap = (stack->capacity == 0)
                       ? ADT_STACK_SIZE_INIT
                       : stack->capacity * ADT_STACK_ALLOC_MULT;

   if (ADT_STACK_ALLOC_MULT < 1 || new_cap < stack->capacity) {
      stack_destroy(stack);
      error(1, "Stack capacity overflow");
   }

   void **tmp = realloc(stack->items, sizeof(*stack->items) * new_cap);
   if (!tmp) {
      stack_destroy(stack);
      error(1, "Out of memory");
   }

   stack->items = tmp;
   stack->capacity = new_cap;
}

stack_t stack_create(void) {
   stack_t stack = malloc(sizeof(*stack));
   if (!stack)
      return NULL;

   stack->capacity = 0;
   stack->ptr = 0;
   stack->items = NULL;

   return stack;
}

void stack_destroy(stack_t stack) {
   if (!stack)
      return;
   free(stack->items);
   free(stack);
}

void stack_push(stack_t stack, void *item) {
   if (stack_is_full(stack))
      stack_grow(stack);

   stack->items[stack->ptr++] = item;
}

void *stack_pop(stack_t stack) {
   if (stack->ptr == 0)
      error(1, "Cannot pop empty stack");

   return stack->items[--stack->ptr];
}

void stack_clear(stack_t stack) { stack->ptr = 0; }

void *stack_top(const stack_t stack) {
   if (stack->ptr == 0)
      error(1, "Cannot top empty stack");

   return stack->items[stack->ptr - 1];
}

bool stack_is_empty(const stack_t stack) { return stack->ptr == 0; }

size_t stack_length(const stack_t stack) { return stack->ptr; }