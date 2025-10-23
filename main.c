///
/// @file main.c
/// @author Zentiph
/// @brief Testing file that utilizes multiple data types to perform some tasks.
/// @version 0.1
/// @date 2025-10-23
///
/// @copyright Copyright (c) 2025
///
///

#include <stdio.h>

#include "stack/stack.h"

int main(void) {
   stack_t stack = stack_create();
   printf("Stack length: %lld\n", stack_length(stack));

   int nums = 100;
   for (int i = 1; i <= nums; i++) {
      printf("Pushing %d\n", i);
      stack_push(stack, (void *)i);
   }

   printf("Stack length: %lld\n", stack_length(stack));
   printf("Top value: %lu\n", (unsigned long)stack_top(stack));

   for (int _ = 1; _ <= nums; _++) {
      void *data = stack_pop(stack);
      printf("Popped %lu\n", (unsigned long)data);
   }

   printf("Stack length: %lld\n", stack_length(stack));
}