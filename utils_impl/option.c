#include "../utils/option.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define     RED    "\e[31m"
#define     BOLD   "\e[01m"
#define     RESET  "\e[00m"
#define     endl   "\n"



struct Option{
    void* content;
    bool isnone;
};
typedef struct Option* Option;

Option Some_(void* x, size_t size){
    Option op = (Option)malloc(sizeof(struct Option));
    if ( op == NULL ){
        fprintf(stderr, RED BOLD "Error allocating memory for the Option Object, aborting now" RESET endl);
        exit(EXIT_FAILURE);
    }
    op -> content = malloc(size);
    if(op -> content == NULL){
        fprintf(stderr, RED BOLD "Error allocating memory for the Option Object's contents, aboring now" RESET endl);
        free(op);
        exit(EXIT_FAILURE);
    }
    memcpy(op -> content, x, size);
    op -> isnone  = false;
    return op;
}

Option None_(){
    Option option = (Option)malloc(sizeof(struct Option));
    if ( option == NULL ){
        fprintf(stderr, RED BOLD "Error allocating memory for the Option Object, aborting now" RESET endl);
        exit(EXIT_FAILURE);
    }

    option->isnone = true;
    return option;
}

void assign_(Option option, void* x, size_t size){
    free(option->content);
    option->content = malloc(sizeof(size));
    if(option->content == NULL){
        fprintf(stderr, RED BOLD "Error reallocating memory for the Option Object in value assigning, aborting now" RESET endl);
        exit(EXIT_FAILURE);
    }
    memcpy(option->content, x, size);
    option->isnone  = false;
}

bool is_none(Option op){
    return op->isnone;
}

void* extract_(Option option, size_t size){
    void* retval = malloc(sizeof(size));
    memcpy(retval, option->content, size);
    return retval;
}

void destroy_option(Option op){
    if(!op -> isnone) free(op->content);
    free(op);
}