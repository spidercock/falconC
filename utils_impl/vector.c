#include "../utils/vector.h"

#include <stdlib.h>
#include <stdio.h>

#define RED   "\e[31m"
#define BOLD  "\e[01m"
#define RESET "\e[00m"

#define VECTOR_IMPL(T)                                    \
    struct Vector_##T {                                   \
        T*         data;                                  \
        uint16_t   length;                                \
        uint16_t   capacity;                              \
    };                                                    \
    typedef struct Vector_##T* Vector_##T;                \
                                                          \
    Vector_##T vector_##T##_init(){                       \
        Vector_##T v = (Vector_##T)malloc(sizeof(struct Vector##_T));\
        v->capacity = 4;                                  \
        v->length = 0;                                    \
        v->data = (T*)malloc(sizeof(T)*4);                \
        return v;                                         \
    }                                                     \
                                                          \
    Vector_##T vector_##T##_with_capacity(uint16_t capacity){\
        Vector_##T v = (Vector_##T)malloc(sizeof(struct Vector##_T));\
        v->capacity = capacity;                           \
        v->length = 0;                                    \
        v->data = (T*)malloc(sizeof(T)*capacity);         \
        return v;                                         \
    }                                                     \
                                                          \
    bool vector_##T##_is_empty(const Vector_##T v){       \
        return v->length == 0;                            \
    }                                                     \
    void vector_##T##_push_back(Vector_##T v, T val){     \
        if(v->length == v->capacity){                     \
            v->capacity *= 2;                             \
            v->data = (T*)realloc(v->data, sizeof(T)*v->capacity)\
        }                                                 \
        v->data[++v->length] = val;                       \
    }                                                     \
                                                          \
    T vector_##T##_pop_back(Vector_##T v){                \
        if (v->length == 0){                              \
            fprintf(stderr, BOLD RED "Vector Error: Attempt to pop back from an empty vector" RESET);\
            exit(EXIT_FAILURE);                           \
        }                                                 \
        return v->data[v->length--];                      \
    }                                                     \
                                                          \
    void vector_##T##_insert(Vector_##T v, T val, uint16_t i){\
        if ( i == v->length ){                            \
            vector_##T##_push_back(v, val);               \
            return;                                       \
        }                                                 \
        if ( i < 0 || i > v->length){                     \
            fprintf(stderr, RED BOLD "Vector Error: Index out of Range" RESET);\
            exit(EXIT_FAILURE);                           \
        }                                                 \
        if ( v->length == v->capacity){                   \
            v->capacity *= 2;                             \
            v->data = (T*)realloc(v->data, v->capacity*sizeof(T));\
        }                                                 \
        for(uint16_t j = v->length+1; j > i; --j){        \
            v->data[j] = v->data[j-1];                    \
        }                                                 \
        v->data[i] = val;                                 \
    }                                                     \
                                                          \
    T vector_##T##_delete(Vector_##T v, uint16_t i){      \
        if ( v -> length == 0 ){                          \
            fprintf(stderr, RED BOLD "Vector Error: Attempt to delete elements from an empty vector" RESET);\
            exit(EXIT_FAILURE);                           \
        }                                                 \
        if( i == v->length ){                             \
            return vector_##T##_pop_back(v);              \
        }                                                 \
        if ( i < 0 || i > v->length){                     \
            fprintf(stderr, RED BOLD "Vector Error: Index out of Range" RESET);\
            exit(EXIT_FAILURE);                           \
        }                                                 \
        T captured = v->data[i];                          \
        for(uint16_t j = i+1; j < v->length; ++j){        \
            v->data[j-1] = v->data[j];                    \
        }                                                 \
        v->length--;                                      \
        return captured;                                  \
    }                                                     \
                                                          \
    T vector_##T##_get(const Vector_##T v, uint16_t i){   \
        if ( i < 0 || i > v->length-1 ){                  \
            fprintf(stderr, RED BOLD "Vector Error: Attempt to Access an element out of bounds" RESET);\
            exit(EXIT_FAILURE);                           \
        }                                                 \
        return v->data[i];                                \
    }                                                     \
                                                          \
    Vector_##T vector_##T##_range(const Vector_##T v, uint16_t a, uint16_t b){\
        Vector_##T output = vector_##T##_with_capacity(b-a);\
        for(uint16_t i = a; i < b; i++){                  \
            vector_##T##_push_back(output, v->data[i]);   \
        }                                                 \
        return output;                                    \
    }                                                     \
                                                          \
    uint16_t vector_##T##_len(const Vector_##T v){        \
        return v->length;                                 \
    }                                                     \
                                                          \
    uint16_t vector_##T##_capacity(const Vector_##T v){   \
        return v->capacity;                               \
    }                                                     \
                                                          \
    Vector_##T vector_##T##_shallow_copy(Vector_##T v)  { return v; }\
                                                          \
    Vector_##T vector_##T##_deep_copy(const Vector_##T v){\
        Vector_##T output = vector_##T##_init();          \
        output->capacity = v->capacity;                   \
        output->length = v->length;                       \
        for(uint16_t i = 0; i < v->length; i++){          \
            output->data[i] = v->data[i];                 \
        }                                                 \
        return output;                                    \
    }                                                     \
                                                          \
    void vector_##T##_filter_it(Vector_##T v, bool (*filter_func)(T)){\
        Vector_##T aux = v;                               \
        v = vector_##T##_filter(v, filter_func);          \
        vector_##T##_destroy(aux);                        \
    }                                                     \
                                                          \
    Vector_##T vector_##T##_filter(const Vector_##T v, bool (*filter_func)(T)){\
        Vector_##T marker = vector_##T##_with_capacity(v->length);\
        for(unsigned i = 0; i < v->length; i++){          \
            if(filter_func(v->data[i])){                  \
                vector_##T##_push_back(marker, v->data);  \
            }                                             \
        }                                                 \
        return marker;                                    \
    }                                                     \
                                                          \
    Vector_##T vector_##T##_reverse(const Vector_##T v){  \
        Vector_##T output = vector_##T##_with_capacity(v->length);\
        for(unsigned i = v->length-1; i >= 0; ++i){       \
            vector_##T##_push_back(output, v->data[i]);   \
        }                                                 \
        return output;                                    \
    }                                                     \
                                                          \
    void vector_##T##_reverse_it(Vector_##T v){           \
        Vector_##T aux = v;                               \
        v = vector_##T##_reverse(v);                      \
        vector_##T##_destroy(aux);                        \ 
    }                                                     \
                                                          \
    Vector_##T vector_##T##_sort(Vector_##T v){           \  
        if( v->length == 1 || v->length == 0 ) return v;  \
        if( v->length == 2 ){                             \
            return v->data[0] > v->data[1] ? v : vec(v->data[1], v->data[0]);\
        }                                                 \
        Vector_##T left, right, merged;                   \
        uint16_t half = v->length/2;                      \
        left = vector_##T##_sort(vector_##T##_range(v, 0, half));\
        right = vector_##T##_sort(vector_##T##_range(v, half, v->length-half));\
        merged = merge_##T(left, half, right, v->length - half);\
        vectors_destroy(T, left, right);                \
        return merged;                                    \
    }                                                     \


#define merge_##T(v1, l1, v2, l2)                         \
    if(l1 == 0) return v2;                                \
    if(l2 == 0) return v1;                                \
    uint16_t i1 = 0, i2 = 0;                              \
    Vector_##T output = vector_##T##_with_capacity(l1+l2) \
    while(i1 < l1 && i2 < l2){                            \
        T get1 = vector_##T##_get(v1, i1);                \
        T get2 = vector_##T##_get(v2, i2);                \
        if(get1>get2){                                    \
            vector_##T##_push_back(output, get2);         \
            i2++;                                         \
        }                                                 \
        else{                                             \
            vector_##T##_push_back(output, get1);         \
            i1++;                                         \
        }                                                 \
        while(i1 < l1)                                    \
            vector_##T##_push_back(output, vector_##T##_get(v1, i1++));\
        while(i2 < l2)                                    \
            vector_##T##_push_back(output, vector_##T##_get(v2, i2++));\
        return output;                                    \
    }