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
#include <stddef.h>

#ifndef ADT_STACK_SIZE_INIT
/// The initial size of the stack.
#define ADT_STACK_SIZE_INIT 32
#endif
#if ADT_STACK_SIZE_INIT < 0
#error ADT_STACK_SIZE_INIT must be >= 0
#endif

#ifndef ADT_STACK_REALLOC_MULT
/// The multiplier to use when increasing the stack's capacity.
#define ADT_STACK_REALLOC_MULT 2
#endif
#if ADT_STACK_REALLOC_MULT < 2
#error ADT_STACK_REALLOC_MULT must be >= 2
#endif

#ifndef ADT_STACK_SHRINKABLE_PROPORTION
/// The proportion of a stack's size to its capacity at which it can be shrunk.
#define ADT_STACK_SHRINKABLE_PROPORTION 4
#endif
#if ADT_STACK_SHRINKABLE_PROPORTION < 2
#error ADT_STACK_SHRINKABLE_PROPORTION must be >= 2
#endif

/// A sentinel value that is returned if NULL is passed as the stack argument in
/// any stack functions.
extern const void *ADT_STACK_ERROR_NULL_STACK;

/// A sentinel value that is returned if an invalid operation is performed on an
/// empty stack. This sentinel cannot be pushed to a stack.
extern const void *ADT_STACK_ERROR_OPERATION_ON_EMPTY;

/// A stack, which implements a last-in-first-out (LIFO) system.
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
/// @brief Push an item to a stack. This operation may fail if the stack needs
///        to grow and memory cannot be reallocated for it.
///
/// @param stack  - The stack to push to.
/// @param item   - The item to push.
/// @return true  - If this operation was successful.
/// @return false - If this operation was unsuccessful.
///
bool stack_push(stack_t stack, void *item);

///
/// @brief Pop an item from a stack.
///
/// @param stack  - The stack to pop from.
/// @return void* - The popped item, or ADT_STACK_EMPTY if the stack is empty.
///
void *stack_pop(stack_t stack);

///
/// @brief Clear a stack. This operation may fail if attempting to lower the
///        capacity of the stack fails.
///
/// @param stack  - The stack to clear.
/// @return true  - If this operation was successful.
/// @return false - If this operation was unsuccessful.
///
bool stack_clear(stack_t stack);

///
/// @brief Grow the stack in anticipation for the addition of more elements.
///
/// @param stack        - The stack to reserve memory for.
/// @param min_capacity - The minimum capacity of the stack after reserving.
///                       The stack's new capacity will not be lowered below its
///                       current capacity, and will be rounded up to the
///                       nearest power of 2.
/// @return true        - If the operation successfully reserved the desired
///                       space.
/// @return false       - If the operation was unsuccessful (realloc failed).
///
bool stack_reserve(stack_t stack, size_t min_capacity);

///
/// @brief Get the top item on a stack without popping it.
///
/// @param stack  - The stack to view the top item of.
/// @return void* - The top item, or ADT_STACK_EMPTY if the stack is empty.
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
/// @brief Get the number of items in a stack.
///
/// @param stack   - The stack to get the length of.
/// @return size_t - The number of items in the stack, or -1 if the stack is
///                  NULL.
///
size_t stack_length(const stack_t stack);

///
/// @brief Get the current capacity of a stack.
///
/// @param stack   - The stack to get the capacity of.
/// @return size_t - The current capacity of the stack, or -1 if the stack is
///                  NULL.
///
size_t stack_capacity(const stack_t stack);

#endif // ADT_STACK_H