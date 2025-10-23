///
/// @file stack.h
/// @author Zentiph
/// @brief The interface for a stack data type in C.
/// @version 1.0
/// @date 2025-10-22
///
/// @copyright Copyright (c) 2025
///
///

#ifndef ADT_STACK_H
#define ADT_STACK_H

#include <stdbool.h>

#ifndef ADT_INITIAL_STACK_SIZE
/// The initial size of the stack.
#define ADT_INITIAL_STACK_SIZE 128 // 2 ^ 7
#endif

/// A stack, which implements a first-in-last-out (FILO) system.
typedef struct stack_s *stack_t;

///
/// @brief Create a new stack. The stack is empty on creation.
///
/// @return stack_t - The new stack, or NULL if mallocation fails.
///
stack_t stack_create(void);

///
/// @brief Destroy a stack.
///
/// @param stack - The stack to destroy.
///
void stack_destroy(stack_t stack);

///
/// @brief Push an item to a stack.
///
/// @param stack - The stack to push to.
/// @param item  - The item to push.
///
void stack_push(stack_t stack, int item);

///
/// @brief Pop an item from a stack.
///
/// @param stack - The stack to pop from.
/// @return int  - The popped item.
///
int stack_pop(stack_t stack);

///
/// @brief Clear a stack.
///
/// @param stack - The stack to clear.
///
void stack_clear(stack_t stack);

///
/// @brief Get the top item on a stack without popping it.
///
/// @param stack - The stack to view the top item of.
/// @return int  - The top item.
///
int stack_top(stack_t stack);

///
/// @brief Check if a stack is empty.
///
/// @param stack  - The stack to check.
/// @return true  - If the stack is empty.
/// @return false - If the stack is not empty.
///
bool stack_empty(stack_t stack);

///
/// @brief Get the number of items in the stack.
///
/// @param stack   - The stack to get the size of.
/// @return size_t - The number of items in the stack.
///
size_t stack_length(stack_t stack);

#endif // ADT_STACK_H