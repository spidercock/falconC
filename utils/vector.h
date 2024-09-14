#ifndef VECTOR_H 
#define VECTOR_H

#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "Option.h"

enum SortFlag{
    isSorted,
    isUnsorted
}; typedef enum SortFlag SortFlag;

// Declare vector type and function prototypes
#define VECTOR_DEF(T) \
    OPTION_DEF(T)                                                                                 \
    typedef struct Vector_##T*        Vector_##T;                                                 \
    Vector_##T                        vector_##T##_init();                      /* O(1)        */ \
    Vector_##T                        vector_##T##_with_capacity(uint16_t);     /* O(1)        */ \
    bool                              vector_##T##_is_empty(const Vector_##T)   /* O(1)        */ \
    void                              vector_##T##_push_back(Vector_##T, T);    /* O(1+)       */ \
    T                                 vector_##T##_pop_back(Vector_##T);        /* O(1)        */ \
    void                              vector_##T##_insert(Vector_##T, T, uint16_t); /* O(n)     */ \
    T                                 vector_##T##_delete(Vector_##T, uint16_t);    /* O(n)     */ \
    T                                 vector_##T##_get(const Vector_##T, uint16_t); /* O(1)     */ \
    Vector_##T                        vector_##T##_range(const Vector_##T, uint16_t, uint16_t); /* O(m) */ \
    uint16_t                          vector_##T##_len(const Vector_##T);       /* O(1)        */ \
    uint16_t                          vector_##T##_capacity(const Vector_##T);  /* O(1)        */ \
    Vector_##T                        vector_##T##_shallow_copy(Vector_##T);    /* O(1)        */ \
    Vector_##T                        vector_##T##_deep_copy(const Vector_##T); /* O(n)        */ \
    void                              vector_##T##_filter_it(Vector_##T, bool(*)(T));/* O(n)        */ \
    Vector_##T                        vector_##T##_filter(const Vector_##T, bool (*)(T));/* O(n)        */ \
    Vector_##T                        vector_##T##_reverse(const Vector_##T);   /* O(n)        */ \
    void                              vector_##T##_reverse_it(Vector_##T);      /* O(n)         */\
    void                              vector_##T##_sort_it(Vector_##T);         /* O(nlogn)    */ \
    Vector_##T                        vector_##T##_sort(const Vector_##T);      /* O(logn)     */ \
    uint16_t                          vector_##T##_find(const Vector_##T, T, SortFlag); /* O(logn)-O(n) */ \
    void                              vector_##T##_destroy(Vector_##T);    /* O(1)        */ \
    void                              vector_##T##_print(const Vector_##T);     /* O(n)        */ \


#define vectors_destroy(T, ...)({                                                                \
    Vector_##T vectors[] = {__VA_ARGS__};                                                        \
    for(uint8_t i = 0; i < (sizeof(vectors)/sizeof(Vector_##T)); i++) free(vectors[i]);          \
})

#define vec(T, ...) ({                                       \
    Vector_##T v = vector_##T##_init();                      \
    T values[] = {__VA_ARGS__};                              \
    for (uint16_t i = 0; i < sizeof(values)/sizeof(T); ++i){ \
        vector_##T##_push_back(v, values[i]);                \
    }                                                        \
    return v;                                                \
})

#define DEFINE_VECTOR_MAP(T, U)                                                     \
    typedef U (*MapFunc_##T)(T);                                                    \
    Vector_##U vector_##T##_map(const Vector_##T v, MapFunc_##T map_func);          \
                                                                                    \
    /* Macro to implement vector map functions */                                   \
    Vector_##U vector_##T##_map(const Vector_##T v, MapFunc_##T map_func) {         \
        Vector_##U new_vec = vector_##U##_with_capacity(vector_##T##_capacity(v));  \
        for (size_t i = 0; i < v->size; ++i) {                                      \
            vector_##U##_push_back(new_vec, map_func(v->data[i]));                  \
        }                                                                           \
        return new_vec;                                                             \
    }


#endif