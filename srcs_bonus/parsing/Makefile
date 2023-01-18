include ../../parse.mk

FILES = main.c ../pkg/string.c ../internal/error.c \
		../pkg/list.c ../internal/free_minirt.c ../pkg/split.c ../pkg/string_conv.c \
		../image_calculation/maths.c\
		../gnl/get_next_line.c ../gnl/get_next_line_utils.c
FILES += $(F_PARS)

all:
	cc $(FILES) -Wall -Wextra -Werror -o parse -I../../incs/ -lm -g3

fclean: clean
	rm -f parse

clean:
	rm -f *.o

re: fclean all
