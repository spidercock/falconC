FLAGS = -fprofile-arcs -ftest-coverage
UTILS_TEST = ../utils_tests/option_test.c
UTILS_IMPL = ../utils_impl/option.c

all: test_option

# Compile, run the test, and generate coverage data
test_option: $(UTILS_IMPL) $(UTILS_TEST) $(UTILS_IMPL)
	@rm -rf output/test_option
	@mkdir -p output/test_option
	@gcc $(FLAGS) -o output/test_option/test_option.exe $(UTILS_TEST) $(UTILS_IMPL) -g && ./output/test_option/test_option.exe

# Generate coverage report
coverage_option: test_option
	@mkdir -p output/test_option_cov
	@lcov --capture --directory output/test_option --output-file output/test_option_cov/option_coverage.info >/dev/null 2>&1
	@genhtml output/test_option_cov/option_coverage.info --output-directory output/test_option_cov/option_cov >/dev/null 2>&1
	@xdg-open output/test_option_cov/option_cov/index.html >/dev/null 2>&1

clean:
	@rm -rf output/test_option output/test_option_cov
