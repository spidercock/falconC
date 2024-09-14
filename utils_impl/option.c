#include "../utils/option.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define RED "\x1b[31m"
#define BOLD "\x1b[01m"
#define RESET "\x1b[00m"

#define OPTION_IMPL(T) \
struct Option_##T { \
    bool isNone; \
    T val; \
}; \
\
typedef struct Option_##T* Option_##T;\
Option_##T option_##T##_some(T x) { \
    Option_##T ret = (Option_##T)malloc(sizeof(struct Option_##T)); \
    if (ret == NULL) { \
        fprintf(stderr, RED BOLD "Option Error: Critical Error! Memory Allocation Failed" RESET "\n"); \
        exit(EXIT_FAILURE); \
    } \
    ret->isNone = false; \
    ret->val = x; \
    return ret; \
} \
\
Option_##T option_##T##_none(void) { \
    Option_##T ret = (Option_##T)malloc(sizeof(struct Option_##T)); \
    if (ret == NULL) { \
        fprintf(stderr, RED BOLD "Option Error: Critical Error! Memory Allocation Failed" RESET "\n"); \
        exit(EXIT_FAILURE); \
    } \
    ret->isNone = true; \
    return ret; \
} \
\
bool option_##T##_is_none(Option_##T option) { \
    return option->isNone; \
} \
\
T option_##T##_extract(Option_##T option) { \
    if(option->isNone) { \
        fprintf(stderr, RED BOLD "Option Error: Forced Extraction Failed! Option is None" RESET "\n"); \
        exit(EXIT_FAILURE); \
    } \
    return option->val; \
} \
\
T option_##T##_extract_or(Option_##T option, T default_val) { \
    return option->isNone ? default_val : option->val; \
} \
\
void option_##T##_destroy(Option_##T option) { \
    free(option); \
} \
\
void option_##T##_assign(Option_##T option, T val) { \
    option->isNone = false; \
    option->val = val; \
}

// Include the implementation for uint8_t
OPTION_IMPL(uint8_t)