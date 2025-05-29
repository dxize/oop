#include <stdexcept>
#include "CStringStack.h"

const char* StackEmpty::what() const noexcept 
{
    return "stack is empty";
}

const char* MemoryError::what() const noexcept 
{
    return "memory allocation failed";
}
