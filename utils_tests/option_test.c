#include "../utils/option.h"
#include <stdio.h>
#include <stdint.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BOLD    "\x1b[01m"
#define RESET   "\x1b[00m"
#define CHECK   "\u2713"
#define CROSS   "\u2717"

OPTION_DEF(uint8_t)

void test1_succ(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);
    if(option_uint8_t_extract(option) == 10) {
        fprintf(stdout, GREEN BOLD "Test1_succ: passed successfully" RESET "\n");
        *output = true;
        option_uint8_t_destroy(option);
        return;
    }
    fprintf(stdout, RED BOLD "Test1_succ: Failed" RESET "\n");
    *output = false;
    option_uint8_t_destroy(option);
}

void test1_fail(bool *output) {
    Option_uint8_t option = option_uint8_t_some(5);  // Incorrect value
    if(option_uint8_t_extract(option) == 10) {
        fprintf(stdout, GREEN BOLD "Test1_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test1_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    option_uint8_t_destroy(option);
}

void test2_succ(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);
    if(!option_uint8_t_is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test2_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test2_succ: Failed" RESET "\n");
        *output = false;
    }
    option_uint8_t_destroy(option);
}

void test2_fail(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);
    if(option_uint8_t_is_none(option)) {  // Expecting false, but it passes
        fprintf(stdout, GREEN BOLD "Test2_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test2_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    option_uint8_t_destroy(option);
}

void test3_succ(bool *output) {
    Option_uint8_t option = option_uint8_t_none();
    if(option_uint8_t_is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test3_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test3_succ: Failed" RESET "\n");
        *output = false;
    }
    option_uint8_t_destroy(option);
}

void test3_fail(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);  // Incorrect value, expecting `None`
    if(option_uint8_t_is_none(option)) {
        fprintf(stdout, GREEN BOLD "Test3_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test3_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    option_uint8_t_destroy(option);
}

void test4_succ(bool *output) {
    Option_uint8_t option = option_uint8_t_none();
    p_match(uint8_t, option, {
        fprintf(stdout, GREEN BOLD "Test4_succ: passed successfully" RESET "\n");
        *output = true;
    }, {
        fprintf(stdout, RED BOLD "Test4_succ: Failed" RESET "\n");
        *output = false;
    });
    option_uint8_t_destroy(option);
}

void test4_fail(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);  // Incorrect, should be `None`
    p_match(uint8_t, option, {
        fprintf(stdout, GREEN BOLD "Test4_fail: passed (incorrect)" RESET "\n");
        *output = true;
    }, {
        fprintf(stdout, RED BOLD "Test4_fail: Failed (as expected)" RESET "\n");
        *output = false;
    });
    option_uint8_t_destroy(option);
}

void test5_succ(bool *output) {
    Option_uint8_t option1 = option_uint8_t_some(10);
    Option_uint8_t option2 = option_uint8_t_none();
    if(option_uint8_t_extract_or(option1, 20) == 10 && option_uint8_t_extract_or(option2, 10) == 10) {
        fprintf(stdout, GREEN BOLD "Test5_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test5_succ: Failed" RESET "\n");
        *output = false;
    }
    options_destroy(uint8_t, option1, option2);
}

void test5_fail(bool *output) {
    Option_uint8_t option1 = option_uint8_t_none();  // Wrong value for option1
    Option_uint8_t option2 = option_uint8_t_some(5); // Wrong value for option2
    if(option_uint8_t_extract_or(option1, 20) == 10 && option_uint8_t_extract_or(option2, 10) == 10) {
        fprintf(stdout, GREEN BOLD "Test5_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test5_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    options_destroy(uint8_t, option1, option2);
}

void test6_succ(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);
    option_uint8_t_assign(option, 20);
    if(option_uint8_t_extract(option) == 20) {
        fprintf(stdout, GREEN BOLD "Test6_succ: passed successfully" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test6_succ: Failed" RESET "\n");
        *output = false;
    }
    options_destroy(uint8_t, option);
}

void test6_fail(bool *output) {
    Option_uint8_t option = option_uint8_t_some(10);
    option_uint8_t_assign(option, 15);  // Wrong assignment
    if(option_uint8_t_extract(option) == 20) {
        fprintf(stdout, GREEN BOLD "Test6_fail: passed (incorrect)" RESET "\n");
        *output = true;
    } else {
        fprintf(stdout, RED BOLD "Test6_fail: Failed (as expected)" RESET "\n");
        *output = false;
    }
    options_destroy(uint8_t, option);
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
