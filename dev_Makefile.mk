DEV_FLAGS			:= -Wall -Werror -Wextra -std=c11 -pedantic \
 						-Wnested-externs -Wcast-qual -Wshadow \
 						-Wstrict-prototypes
DEBUG_FLAGS 		:= -g
VALGRIND_FLAGS  	:= --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
CC					:= gcc
CFLAGS				:= -Wall -Werror -Wextra -std=c11 -pedantic

FUNC_ARITHMETIC_DIR	:= functions/arithmetic
FUNC_COMMON_DIR		:= functions/common
FUNC_COMPARISON_DIR	:= functions/comparison
FUNC_CONVERSION_DIR	:= functions/conversion
FUNC_ROUNDING_DIR	:= functions/rounding
FUNC_DEVELOP_DIR	:= functions/develop

FUNC_TEST_DIR   	:= tests/
OBJ_DIR        		:= ./
BUILD_DIR			:= ../build/
LIB_HEADER      	:= s21_decimal.h
ifeq ($(shell head -n 1 /etc/lsb-release), DISTRIB_ID=Ubuntu)
UBUNTU_FLAGS      	:= -lrt -lsubunit $(shell pkg-config --cflags check) $(shell pkg-config --libs check)
endif
TEST_FLAGS			:= -lcheck -lm -lpthread $(UBUNTU_FLAGS)
GCOV_FLAGS      	:= -fprofile-arcs -ftest-coverage
TEST_DIR_BUILD		:= tests/build/
LIB_STATIC      	:= s21_decimal.a


FUNC_SRCS			:= $(addprefix $(FUNC_COMMON_DIR)/, s21_common.c \
 														s21_overloads.c \
 														s21_binary_api.c) \
                   					$(addprefix $(FUNC_ARITHMETIC_DIR)/, s21_add.c \
                                                               s21_sub.c \
                                                               s21_mul.c \
                                                               s21_div.c \
                                                               s21_negate.c) \
                                   	$(addprefix $(FUNC_COMPARISON_DIR)/, s21_is_less.c \
                                                               s21_is_less_or_equal.c \
                                                               s21_is_greater.c \
                                                               s21_is_greater_or_equal.c \
                   											s21_is_equal.c \
                                                               s21_is_not_equal.c) \
                                   	$(addprefix $(FUNC_CONVERSION_DIR)/, s21_from_int_to_decimal.c \
                                                               s21_from_float_to_decimal.c \
                                                               s21_from_decimal_to_int.c \
                                                               s21_from_decimal_to_float.c \
                                                               s21_conversion_aux.c) \
                                   	$(addprefix $(FUNC_ROUNDING_DIR)/, s21_floor.c \
                                                               s21_round.c \
                                                               s21_truncate.c\
                                                               s21_rounding_aux.c)

dev_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)main_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_main_test_manual_valgrind:
	$(CC) main_test.c $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $@.out
	valgrind $(VALGRIND_FLAGS) ./$@.out

dev_main_test_manual:
	$(CC) main_test.c $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $@.out
	 ./$@.out

dev_add_test:
	$(CC) $(FUNC_TEST_DIR)s21_add_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_add_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_add_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_sub_test:
	$(CC) $(FUNC_TEST_DIR)s21_sub_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_sub_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_sub_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_div_test:
	$(CC) $(FUNC_TEST_DIR)s21_div_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_div_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_div_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_mul_test:
	make rebuild
	$(CC) $(FUNC_TEST_DIR)s21_mul_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_mul_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_mul_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_less_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_less_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_less_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_less_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_less_or_equal_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_less_or_equal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_less_or_equal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_less_or_equal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_greater_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_greater_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_greater_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_greater_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_greater_or_equal_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_greater_or_equal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_greater_or_equal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_greater_or_equal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_equal_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_equal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_equal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_equal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_is_not_equal_test:
	$(CC) $(FUNC_TEST_DIR)s21_is_not_equal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_is_not_equal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_is_not_equal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_from_int_to_decimal_test:
	$(CC) $(FUNC_TEST_DIR)s21_from_int_to_decimal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_from_int_to_decimal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_from_int_to_decimal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_from_float_to_decimal_test:
	$(CC) $(FUNC_TEST_DIR)s21_from_float_to_decimal_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_from_float_to_decimal_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_from_float_to_decimal_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_from_decimal_to_int_test:
	$(CC) $(FUNC_TEST_DIR)s21_from_decimal_to_int_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_from_decimal_to_int_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_from_decimal_to_int_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_from_decimal_to_float_test:
	$(CC) $(FUNC_TEST_DIR)s21_from_decimal_to_float_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_from_decimal_to_float_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_from_decimal_to_float_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_floor_test:
	$(CC) $(FUNC_TEST_DIR)s21_floor_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_floor_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_floor_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_round_test:
	$(CC) $(FUNC_TEST_DIR)s21_round_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_round_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_round_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_truncate_test:
	$(CC) $(FUNC_TEST_DIR)s21_truncate_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_truncate_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_truncate_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out

dev_negate_test:
	$(CC) $(FUNC_TEST_DIR)s21_negate_test.c -L. $(LIB_STATIC) $(TEST_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	./$(TEST_DIR_BUILD)$@.out

dev_negate_test_valgrind:
	$(CC) $(FUNC_TEST_DIR)s21_negate_test.c -L. $(FUNC_SRCS) $(TEST_FLAGS) $(EXTRA_LIB_FLAGS) $(DEBUG_FLAGS) -o $(TEST_DIR_BUILD)$@.out
	valgrind $(VALGRIND_FLAGS) ./$(TEST_DIR_BUILD)$@.out