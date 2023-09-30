CC              := gcc
CFLAGS 			:= -Wall -Werror -Wextra -std=c11
FUNC_DIR        := functions
FUNC_ARITHMETIC_DIR	:= functions/arithmetic
FUNC_COMMON_DIR		:= functions/common
FUNC_COMPARISON_DIR	:= functions/comparison
FUNC_CONVERSION_DIR	:= functions/conversion
FUNC_ROUNDING_DIR	:= functions/rounding
FUNC_DEVELOP_DIR	:= functions/develop
FUNC_TEST_DIR   := tests/
OBJ_DIR         := ./
BUILD_DIR		:= ../build/
LIB_HEADER      := s21_decimal.h

ifeq ($(shell head -n 1 /etc/lsb-release), DISTRIB_ID=Ubuntu)
UBUNTU_FLAGS      	:= -lrt -lsubunit $(shell pkg-config --cflags check) $(shell pkg-config --libs check)
endif

TEST_FLAGS      := -lcheck -lm -lpthread $(UBUNTU_FLAGS)
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage
TEST_DIR_BUILD	:= tests/build/
LIB_STATIC      := s21_decimal.a

FUNC_SRCS       := 	$(addprefix $(FUNC_COMMON_DIR)/, s21_common.c s21_overloads.c s21_binary_api.c ) \
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
                                            s21_truncate.c \
                                            s21_rounding_aux.c)

FUNC_OBJS_WITHOUT_OBJECT_DIRNAME = $(FUNC_SRCS:.c=.o)
FUNC_OBJS = $(subst $(FUNC_DIR), $(OBJ_DIR), $(FUNC_OBJS_WITHOUT_OBJECT_DIRNAME))

$(LIB_STATIC):$(FUNC_SRCS)
	mkdir tests/build
	$(CC) $(CFLAGS) -lm -c $(FUNC_SRCS)
	ar -rcs $@ *.o
	make clean_obj

all: rebuild

build:
	make $(LIB_STATIC)

rebuild: clean build

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h ./*/*.c ./*/*.h ./*/*/*.c ./*/*/*.h
check:
	clang-format -n -style=Google  *.c *.h ./*/*.c ./*/*.h ./*/*/*.c ./*/*/*.h

clang_format:
	clang-format -i -style=Google  *.c *.h ./*/*.c ./*/*.h ./*/*/*.c ./*/*/*.h


gcov_report:
	mkdir report
	gcc tests/main_test.c $(FUNC_SRCS) $(TEST_FLAGS) $(GCOV_FLAGS) -o ./$@.out
	./$@.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

test:
	gcc tests/main_test.c $(LIB_STATIC) $(TEST_FLAGS)  -o ./test.out
	./test.out

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_brew_goinfre: # be careful with this!
	cd ~/goinfre
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew

install_lcov:
	brew install lcov

clean:
	make clean_silent --silent

clean_silent:
	rm -rf "__.SYMDEF SORTED"
	rm -rf ../*/*.o
	rm -rf ../*/*.out
	rm -rf ../*/*.info
	rm -rf ../*/*.a
	rm -rf ../*/*.g*
	rm -rf ../*/*/*.o
	rm -rf ../*/*/*.out
	rm -rf ../*/*/*.info
	rm -rf ../*/*/*.a
	rm -rf ../*/*/*.g*
	rm -rf ../*/*/*/*.o
	rm -rf ../*/*/*/*.out
	rm -rf ../*/*/*/*.info
	rm -rf ../*/*/*/*.a
	rm -rf ../*/*/*/*.g*
	rm -rf ./object_files
	rm -rf ./tests/build
	rm -rf ./report
	rm -rf ./*.log

dev_%:
	make -f dev_Makefile.mk $@

clean_obj :
	rm -f *.o

clean_after_gcov:
	rm -rf ../*.g*
	rm -rf ../*/*.g*
	rm -rf ../*/*/*.g*
	rm -rf ../*/*/*/*.g*
