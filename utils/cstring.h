#ifdef CSTRING_H
#define CSTRING_H

#include <stdint.h>
#include <stdbool.h>
#include <vector.h>

typedef struct string* string;
typedef struct vector* vector;
DEFINE_VECTOR_T(uint8_t);
IMPL_VECTOR(uint8_t);


string init_string();
string init_string_with_capacity(uint8_t);
#define string_fromcstr _Generic((x),\
    const char*: string_fromconstcstring,\
    char*      : string_fromcstring\
)(x)
void free_string(string);
uint8_t len(const string);
uint8_t capacity(const string);
char* string_to_cstring(const string);
char get_string_char(const string, uint8_t);
char* get_substring(const string, uint8_t, uint8_t);
uint8_t index(const string, char);
bool isalpha(const string);
bool isnum(const string);
bool isalnum(const string);
vector_uint8_t string_to_bytes(const string);
vector_string split(string, const string); 


#endif