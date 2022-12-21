# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 16:14:17 by ngiroux           #+#    #+#              #
#    Updated: 2022/12/21 18:57:09 by nseniak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include colors.mk

# Names 
NAME		= minirt
MLX			= minilibx_opengl

LIB			= mlx/libmlx_Linux.a
FILES		= cmd/main.c
F_INT		= error.c
FILES		+= $(addprefix internal/, $(F_INT))
F_PARS		= parse.c check.c
FILES		+= $(addprefix parsing/, $(F_PARS))
F_PKG		= list.c string.c
FILES		+= $(addprefix pkg/, $(F_PKG))
F_PKG		= create_window.c
FILES		+= $(addprefix window_handling/, $(F_PKG))

# Paths
SRCS_PATH	= srcs/
INCS_PATH	= incs/ mlx/
OBJS_PATH	= objs/

# Objects
OBJS		= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

# Flags + compilation
CFLAGS		= -Wall -Wextra -Werror -O0 -g3
CC			= cc
INCS		= $(addprefix -I, $(INCS_PATH))
# LIB_INC		= -lm -Lmlx -lmlx_Linux -lmlx -lXext -lX11

# Create obj and dir
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
			@echo "${MSG_COMP}$<"
			
# Compiling command
all:		${NAME}

${NAME}:	${OBJS} ${LIB}
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_INC) -o $(NAME) $(INCS)
			@echo "${MSG_BUILD}${NAME}${MSG_FINISH}"

${LIB}:
			@echo "${MSG_LIB}${LIB}"
			@make -C mlx >/dev/null 2>/dev/null || true

# Other rules
clean:
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@make -C mlx clean >/dev/null 2>/dev/null || true
			@echo "${MSG_RMV}${LIB}"

fclean:		clean
			@rm -rf ${NAME}
			@rm -rf ${B_NAME}
			@echo "${MSG_RMV}${NAME}"

re:			fclean all

.PHONY:		all clean fclean re
