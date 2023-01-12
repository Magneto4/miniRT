FILES = check_elem.c check_types.c parse.c main.c ../pkg/string.c ../internal/error.c \
		../pkg/list.c ../internal/free_minirt.c ../pkg/split.c ../pkg/string_conv.c \
		set_elem.c set_types.c ../image_calculation/maths.c\
		../gnl/get_next_line.c ../gnl/get_next_line_utils.c

all:
	cc $(FILES) -Wall -Wextra -Werror -o parse -I../../incs/ -lm -g3

fclean: clean
	rm -f parse

clean:
	rm -f *.o

re: fclean all
