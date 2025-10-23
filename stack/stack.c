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

#include "stack.h"

struct stack_s {
   size_t size;
   size_t ptr;
   int *items;
};

static inline bool _stack_full(stack_t stack) {
   return stack->ptr >= stack->size;
}

static bool _stack_realloc(stack_t stack) {
   stack->size *= 2;
   stack->items = realloc(stack->items, stack->size);
   return (stack->items != NULL);
}

stack_t stack_create(void) {
   stack_t stack = (stack_t)malloc(sizeof(*stack));
   if (!stack)
      return NULL;

   stack->size = ADT_INITIAL_STACK_SIZE;
   stack->ptr = 0;

   stack->items = (int *)malloc(stack->size * sizeof(int));
   if (!stack->items) {
      free(stack);
      return NULL;
   }

   return stack;
}

void stack_destroy(stack_t stack) {
   if (!stack)
      return;
   free(stack->items);
   free(stack);
}

void stack_push(stack_t stack, int item) {
   if (_stack_full(stack)) {
      bool success = _stack_realloc(stack);

      if (!success) {
         stack_destroy(stack);
         error(1, "Could not push new value to stack; unable to "
                  "reallocate more memory to stack");
      }
   }

   stack->items[stack->ptr++] = item;
}

int stack_pop(stack_t stack) {
   if (stack->ptr == 0) {
      error(1, "Cannot pop empty stack");
   }

   return stack->items[--stack->ptr];
}

void stack_clear(stack_t stack) { stack->ptr = 0; }

int stack_top(stack_t stack) { return stack->items[stack->ptr - 1]; }

bool stack_empty(stack_t stack) { return stack->ptr == 0; }

size_t stack_length(stack_t stack) { return stack->ptr; }