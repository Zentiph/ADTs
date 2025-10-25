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

#include <stdlib.h>

#include <assert.h>
#include <limits.h>

#include "stack.h"

static const char _null_stack_sentinel_obj;
const void *ADT_STACK_ERROR_NULL_STACK = &_null_stack_sentinel_obj;

static const char _stack_empty_sentinel_obj;
const void *ADT_STACK_ERROR_OPERATION_ON_EMPTY = &_stack_empty_sentinel_obj;

struct stack_s {
   size_t capacity;
   size_t len;
   void **items;
};

static inline bool stack_is_full(const stack_t stack) {
   return stack->len >= stack->capacity;
}

static inline bool stack_should_shrink(const stack_t stack) {
   return stack->capacity > ADT_STACK_SIZE_INIT && stack->len > 0 &&
          (stack->capacity / ADT_STACK_SHRINKABLE_PROPORTION) >= stack->len;
}

static size_t next_pow2(size_t x) {
   if (x <= 1) // define next_pow2(0) = 1
      return 1;

   x--; // if x is already a power of two, it looks like 100(...)000.
        // decrementing it by 1 make it look like 011(...)111.

   // for each bit position, propagate the top bit rightward and perform an OR
   // so that every bit below the highest 1 becomes 1.
   // e.g. 01010000 -> 01111111
   for (size_t shift = 1; shift < sizeof(size_t) * CHAR_BIT; shift <<= 1)
      x |= x >> shift;

   // add one to carry all 1s over to get a clean power of 2
   // e.g. 01111111 + 1 = 10000000
   x++;

   // if x exceeded the highest power of 2, it will wrap to 0.
   // saturate by returning the highest power of 2.
   if (x == 0)
      x = (size_t)1 << (sizeof(size_t) * CHAR_BIT - 1);

   return x;
}

static bool stack_grow(stack_t stack, size_t new_cap) {
   if (new_cap < stack->capacity) {
      return false; // overflow
   }

   void **tmp = realloc(stack->items, sizeof(*stack->items) * new_cap);
   if (!tmp)
      return false;

   stack->items = tmp;
   stack->capacity = new_cap;
   return true;
}

static bool stack_grow_mult(stack_t stack) {
   size_t new_cap = (stack->capacity == 0)
                       ? ADT_STACK_SIZE_INIT
                       : stack->capacity * ADT_STACK_REALLOC_MULT;

   if (stack->capacity != 0 &&
       new_cap / ADT_STACK_REALLOC_MULT != stack->capacity)
      return false;

   if (!stack_grow(stack, new_cap))
      return false;

   return true;
}

static void stack_shrink(stack_t stack) {
   size_t new_cap = stack->capacity / 2;
   if (new_cap < ADT_STACK_SIZE_INIT)
      new_cap = ADT_STACK_SIZE_INIT;

   void **tmp = realloc(stack->items, sizeof(*stack->items) * new_cap);
   if (tmp) {
      stack->items = tmp;
      stack->capacity = new_cap;
   }
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
   if (!stack)
      return;

   free(stack->items);
   free(stack);
}

bool stack_push(stack_t stack, void *item) {
   if (!stack || item == ADT_STACK_ERROR_OPERATION_ON_EMPTY)
      return false;

   if (stack_is_full(stack)) {
      stack_grow_mult(stack);

      if (!stack->items) {
         return false;
      }
   }

   stack->items[stack->len++] = item;
   return true;
}

void *stack_pop(stack_t stack) {
   if (!stack)
      return (void *)ADT_STACK_ERROR_NULL_STACK;

   if (stack_is_empty(stack))
      return (void *)ADT_STACK_ERROR_OPERATION_ON_EMPTY;

   void *popped = stack->items[--stack->len];
   if (stack_should_shrink(stack))
      stack_shrink(stack);

   return popped;
}

bool stack_clear(stack_t stack) {
   if (!stack)
      return false;

   stack->len = 0;
   if (stack->capacity > ADT_STACK_SIZE_INIT) {
      void **tmp =
         realloc(stack->items, sizeof(*stack->items) * ADT_STACK_SIZE_INIT);

      if (tmp) {
         stack->items = tmp ? tmp : stack->items;
         stack->capacity = ADT_STACK_SIZE_INIT;
      } else
         return false;
   }

   return true;
}

bool stack_reserve(stack_t stack, size_t min_capacity) {
   if (min_capacity <= stack->capacity)
      return true;

   size_t target = next_pow2(min_capacity);
   if (target < ADT_STACK_SIZE_INIT)
      target = ADT_STACK_SIZE_INIT;

   return stack_grow(stack, target);
}

bool stack_reserve_exact(stack_t stack, size_t capacity) {
   if (capacity <= stack->capacity)
      return true;

   if (capacity < ADT_STACK_SIZE_INIT)
      capacity = ADT_STACK_SIZE_INIT;

   return stack_grow(stack, capacity);
}

void *stack_top(const stack_t stack) {
   if (!stack)
      return (void *)ADT_STACK_ERROR_NULL_STACK;

   if (stack_is_empty(stack))
      return (void *)ADT_STACK_ERROR_OPERATION_ON_EMPTY;

   return stack->items[stack->len - 1];
}

bool stack_is_empty(const stack_t stack) {
   if (!stack)
      return (void *)ADT_STACK_ERROR_NULL_STACK;

   return stack->len == 0;
}

size_t stack_length(const stack_t stack) {
   if (!stack)
      return -1;

   return stack->len;
}

size_t stack_capacity(const stack_t stack) {
   if (!stack)
      return -1;

   return stack->capacity;
}