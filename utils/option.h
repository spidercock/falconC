#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Option* Option;

Option Some_(void*, size_t);
Option None_();
void assign_(Option, void*, size_t);
bool is_none(Option);
void destroy_option(Option);
void *extract_(Option, size_t);
void *extract_or_(Option, void*);


#define p_match(option, expr1, expr2) \
    if(is_none(option)) expr1\
    else expr2

#define Somev(T, x) Some_((void*)&x, sizeof(T))
#define Somel(T, x) Some_((void*)&(T){x}, sizeof(T))
#define None(T) None_()
#define assignv(T, option, value) assign_(option, (void*)&value, sizeof(T))
#define assignl(T, option, value) assign_(option, (void*)&(T){value}, sizeof(T))
#define extract(T, option) (*(T*)extract_(option, sizeof(T)))
#define extract_or(T, option, default) (is_none(option) ? default : extract(T, option))

#define options_destroy(T, ...) do { \
    Option_##T options[] = {__VA_ARGS__}; \
    for(unsigned i = 0; i < (sizeof(options)/sizeof(Option_##T)); i++) \
        option_##T##_destroy(options[i]); \
} while(0)



#endif

