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

#ifndef ADT_STACK_SIZE_INIT
/// THe initial size of the stack.
#define ADT_STACK_SIZE_INIT 32
#endif

#if ADT_STACK_SIZE_INIT < 0
#error Initial stack size must be >= 0
#endif

#ifndef ADT_STACK_REALLOC_MULT
/// The initial size of the stack.
#define ADT_STACK_REALLOC_MULT 2
#endif

#if ADT_STACK_REALLOC_MULT < 1
#error Stack realloc multiplier must be >= 1
#endif

#ifndef ADT__STACK_IMPLEMENTATION
/// A stack, which implements a last-in-first-out (LIFO) system.
typedef struct {
} *stack_t;
#endif

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
void stack_push(stack_t stack, void *item);

///
/// @brief Pop an item from a stack.
///
/// @param stack - The stack to pop from.
/// @return int  - The popped item.
///
void *stack_pop(stack_t stack);

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
void *stack_top(const stack_t stack);

///
/// @brief Check if a stack is empty.
///
/// @param stack  - The stack to check.
/// @return true  - If the stack is empty.
/// @return false - If the stack is not empty.
///
bool stack_is_empty(const stack_t stack);

///
/// @brief Get the number of items in the stack.
///
/// @param stack   - The stack to get the size of.
/// @return size_t - The number of items in the stack.
///
size_t stack_length(const stack_t stack);

#endif // ADT_STACK_H