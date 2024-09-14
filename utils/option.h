#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>

#define OPTION_DEF(T) \
    typedef struct Option_##T* Option_##T; \
    Option_##T option_##T##_some(T); \
    Option_##T option_##T##_none(void); \
    bool option_##T##_is_none(const Option_##T); \
    T option_##T##_extract(const Option_##T); /* unsafe, leads to runtime errors */ \
    T option_##T##_extract_or(const Option_##T, T); /* safe equivalent */ \
    void option_##T##_destroy(Option_##T); \
    void option_##T##_assign(Option_##T, T);

#define p_match(T, option, expr1, expr2) option_##T##_is_none(option) ? (expr1) : (expr2)

#define options_destroy(T, ...) do { \
    Option_##T options[] = {__VA_ARGS__}; \
    for(unsigned i = 0; i < (sizeof(options)/sizeof(Option_##T)); i++) \
        option_##T##_destroy(options[i]); \
} while(0)

#endif