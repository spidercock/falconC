#include "../utils/option.h"
#include <stdio.h>
#include <stdint.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[34m"
#define BOLD    "\x1b[01m"
#define RESET   "\x1b[00m"
#define CHECK   "\u2713"
#define CROSS   "\u2717"

void test1_succ(bool *output) {
    Option option = Somel(uint8_t, 10);  // Use macro to create Some
    if(extract(uint8_t, option) == 10) {  // Use macro to extract
        fprintf(stdout, GREEN BOLD "Test1_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test1_succ: Failed" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test1_fail(bool *output) {
    Option option = Somel(uint8_t, 5);  // Incorrect value
    if(extract(uint8_t, option) == 10) {
        fprintf(stdout, GREEN BOLD "Test1_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test1_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test2_succ(bool *output) {
    Option option = Somel(uint8_t, 10);
    if(!is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test2_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test2_succ: Failed" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test2_fail(bool *output) {
    Option option = Somel(uint8_t, 10);
    if(is_none(option)) {  // Expecting false, but it passes
        fprintf(stdout, GREEN BOLD "Test2_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test2_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test3_succ(bool *output) {
    Option option = None(uint8_t);  // Use macro for None
    if(is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test3_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test3_succ: Failed" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test3_fail(bool *output) {
    Option option = Somel(uint8_t, 10);  // Incorrect value, expecting `None`
    if(is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test3_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test3_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test4_succ(bool *output) {
    Option option = None(uint8_t);
    p_match(option, {
        fprintf(stdout, GREEN BOLD "Test4_succ: passed successfully" RESET "\n");
        *output = true;
    }, {
        fprintf(stdout, RED BOLD "Test4_succ: Failed" RESET "\n");
        *output = false;
    });
    destroy_option(option);
}

void test4_fail(bool *output) {
    Option option = Somel(uint8_t, 10);  // Incorrect, should be `None`
    p_match(option, {
        fprintf(stdout, GREEN BOLD "Test4_fail: passed (incorrect)" RESET "\n");
        *output = true;
    }, {
        fprintf(stdout, RED BOLD "Test4_fail: Failed (as expected)" RESET "\n");
        *output = false;
    });
    destroy_option(option);
}

void test5_succ(bool *output) {
    Option option1 = Somel(uint8_t, 10);
    Option option2 = None(uint8_t);
    if(extract_or(uint8_t, option1, 20) == 10 && extract_or(uint8_t, option2, 10) == 10) {  // Use extract_or macro
        fprintf(stdout, GREEN BOLD "Test5_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test5_succ: Failed" RESET "\n");
        *output = false;
    }
    destroy_option(option1);
    destroy_option(option2);
}

void test5_fail(bool *output) {
    Option option1 = None(uint8_t);  // Wrong value for option1
    Option option2 = Somel(uint8_t, 5);  // Wrong value for option2
    if(extract_or(uint8_t, option1, 20) == 10 && extract_or(uint8_t, option2, 10) == 10) {
        fprintf(stdout, GREEN BOLD "Test5_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test5_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    destroy_option(option1);
    destroy_option(option2);
}

void test6_succ(bool *output) {
    Option option = Somel(uint8_t, 10);
    assignl(uint8_t, option, 20);  // Use assignv macro
    if(extract(uint8_t, option) == 20) {
        fprintf(stdout, GREEN BOLD "Test6_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test6_succ: Failed" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

void test6_fail(bool *output) {
    Option option = Somel(uint8_t, 10);
    assignl(uint8_t, option, 15);  // Wrong assignment
    if(extract(uint8_t, option) == 20) {
        fprintf(stdout, GREEN BOLD "Test6_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test6_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    destroy_option(option);
}

#define n_succ 6
#define n_fail 6

void run_tests_succ() {
    bool output[n_succ];
    test1_succ(output);
    test2_succ(output+1);
    test3_succ(output+2);
    test4_succ(output+3);
    test5_succ(output+4);
    test6_succ(output+5);
    for(unsigned i = 0; i < n_succ; i++){
        if(output[i])
            fprintf(stdout, BOLD GREEN CHECK RESET);
        else
            fprintf(stdout, BOLD RED CROSS RESET);
    }
    fprintf(stdout, "\n");
}

void run_tests_fail() {
    bool output[n_fail];
    test1_fail(output);
    test2_fail(output+1);
    test3_fail(output+2);
    test4_fail(output+3);
    test5_fail(output+4);
    test6_fail(output+5);
    for(unsigned i = 0; i < n_fail; i++){
        if(output[i])
            fprintf(stdout, BOLD GREEN CHECK RESET);
        else
            fprintf(stdout, BOLD RED CROSS RESET);
    }
    fprintf(stdout, "\n");
}

int main() {
    fprintf(stdout, YELLOW BOLD "Running success tests:" RESET "\n");
    run_tests_succ();

    fprintf(stdout, YELLOW BOLD "Running failure tests:" RESET "\n");
    run_tests_fail();

    return 0;
}
