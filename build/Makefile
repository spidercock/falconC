FLAGS = -fprofile-arcs -ftest-coverage
UTILS_IMPL = ../utils_impl/option.c
UTILS_TEST = ../utils_tests/option_test.c

all: test_option

# Compile, run the test, and generate coverage data
test_option: $(UTILS_IMPL) $(UTILS_TEST)
	@rm -rf output/test_option
	@mkdir -p output/test_option
	@gcc $(FLAGS) -o output/test_option/test_option.exe $(UTILS_TEST) $(UTILS_IMPL) && ./output/test_option/test_option.exe

# Generate coverage report
coverage_option: test_option
	@mkdir -p output/test_option_cov
	@lcov --capture --directory output/test_option --output-file output/test_option_cov/option_coverage.info
	@genhtml output/test_option_cov/option_coverage.info --output-directory output/test_option_cov/option_cov
	@xdg-open output/test_option_cov/option_cov/index.html

clean:
	@rm -rf output/test_option output/test_option_cov
