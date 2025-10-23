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

#include <assert.h>

#include "../err/err.h"

typedef struct stack_s *stack_t;
#define ADT__STACK_IMPLEMENTATION
#include "stack.h"

struct stack_s {
   size_t capacity;
   size_t len;
   void **items;
};

static inline bool stack_is_full(const stack_t stack) {
   return stack->len >= stack->capacity;
}

static inline bool stack_can_shrink(const stack_t stack) {
   return stack->len < stack->capacity / 2;
}

static void stack_grow(stack_t stack) {
   size_t new_cap = (stack->capacity == 0)
                       ? ADT_STACK_SIZE_INIT
                       : stack->capacity * ADT_STACK_REALLOC_MULT;

   if (new_cap < stack->capacity) {
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

static void stack_shrink(stack_t stack) {
   size_t new_cap = (stack->capacity < ADT_STACK_SIZE_INIT)
                       ? ADT_STACK_SIZE_INIT
                       : stack->capacity / ADT_STACK_REALLOC_MULT;

   if (new_cap > stack->capacity) {
      stack_destroy(stack);
      error(1, "Attempt to shrink stack resulted in larger capacity");
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
   stack->len = 0;
   stack->items = NULL;

   return stack;
}

void stack_destroy(stack_t stack) {
   assert(stack);

   free(stack->items);
   free(stack);
}

void stack_push(stack_t stack, void *item) {
   assert(stack);

   if (stack_is_full(stack))
      stack_grow(stack);

   stack->items[stack->len++] = item;
}

void *stack_pop(stack_t stack) {
   assert(stack);

   if (stack_is_empty(stack))
      error(1, "Cannot pop empty stack");

   void *popped = stack->items[--stack->len];

   while (stack_can_shrink(stack)) {
      stack_shrink(stack);
   }

   return popped;
}

void stack_clear(stack_t stack) {
   assert(stack);

   free(stack->items);
   stack = stack_create();
}

void *stack_top(const stack_t stack) {
   assert(stack);

   if (stack_is_empty(stack))
      error(1, "Cannot top empty stack");

   return stack->items[stack->len - 1];
}

bool stack_is_empty(const stack_t stack) {
   assert(stack);

   return stack->len == 0;
}

size_t stack_length(const stack_t stack) {
   assert(stack);

   return stack->len;
}