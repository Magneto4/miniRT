FILES = check.c parse.c main.c ../pkg/string.c ../internal/error.c \
		../pkg/list.c ../internal/free_minirt.c ../pkg/split.c ../pkg/string_conv.c \
		set_elem.c set_types.c \
		../gnl/get_next_line.c ../gnl/get_next_line_utils.c

all:
	cc $(FILES) -Wall -Wextra -Werror -o parse -I../../incs/

fclean: clean
	rm -f parse

clean:
	rm -f *.o

re: fclean all
