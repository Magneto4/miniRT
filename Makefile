# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 16:14:17 by ngiroux           #+#    #+#              #
#    Updated: 2023/01/25 18:18:20 by ngiroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include colors.mk
include parse.mk


# Names 
NAME		= minirt
NAME_B	= minirt_bonus
MLX			= minilibx_opengl

LIB			= mlx/libmlx_Linux.a
#MANDATORY
FILES		= cmd/main.c
F_GNL		= get_next_line.c get_next_line_utils.c
FILES		+= $(addprefix gnl/, $(F_GNL))
F_INT		= error.c free_minirt.c
FILES		+= $(addprefix internal/, $(F_INT))

FILES		+= $(addprefix parsing/, $(F_PARS))
F_PKG		= list.c string.c string_conv.c split.c
FILES		+= $(addprefix pkg/, $(F_PKG))
F_WIN		= create_window.c hooks.c
FILES		+= $(addprefix window_handling/, $(F_WIN))
F_IM		= loop.c colour.c intersection.c sphere.c cylinder.c plane.c shadows.c cylinder2.c lit.c
FILES		+= $(addprefix image_calculation/, $(F_IM))
F_MA		= vectors.c vectors2.c quadratics.c matrix.c
FILES		+= $(addprefix maths/, $(F_MA))

# Paths
SRCS_PATH	= srcs/
INCS_PATH	= incs/ mlx/
OBJS_PATH	= objs/

# Objects
OBJS		= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

INCS		= $(addprefix -I, $(INCS_PATH))

#BONUS

# Names 
FILES_BONUS	= cmd/main.c
F_GNL_BONUS	= get_next_line.c get_next_line_utils.c
FILES_BONUS	+= $(addprefix gnl/, $(F_GNL_BONUS))
F_INT_BONUS	= error.c free_minirt.c
FILES_BONUS	+= $(addprefix internal/, $(F_INT_BONUS))

FILES_BONUS	+= $(addprefix parsing/, $(F_PARS_BONUS))
F_PKG_BONUS	= list.c string.c string_conv.c split.c
FILES_BONUS	+= $(addprefix pkg/, $(F_PKG_BONUS))
F_WIN_BONUS	= create_window.c hooks.c
FILES_BONUS	+= $(addprefix window_handling/, $(F_WIN_BONUS))
F_IM_BONUS	= loop.c colour.c sphere.c cylinder.c cylinder2.c plane.c cone.c cone2.c shadows.c shadows2.c intersection.c texturing.c lit.c
FILES_BONUS	+= $(addprefix image_calculation/, $(F_IM_BONUS))
F_MA_BONUS	= vectors.c vectors2.c quadratics.c colour_operations.c matrix.c
FILES_BONUS	+= $(addprefix maths/, $(F_MA_BONUS))

# Paths
SRCS_PATH_BONUS	= srcs_bonus/
INCS_PATH_BONUS	= incs_bonus/ mlx/
OBJS_PATH_BONUS	= objs_bonus/

# Objects
OBJS_BONUS	= $(addprefix $(OBJS_PATH_BONUS), $(FILES_BONUS:.c=.o))

INCS_BONUS	= $(addprefix -I, $(INCS_PATH_BONUS))

# Create obj and dir
$(OBJS_PATH_BONUS)%.o: $(SRCS_PATH_BONUS)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCS_BONUS)
			@echo "${MSG_COMP}$<"

# Flags + compilation
CFLAGS		= -Wall -Wextra -Werror -O0 -g3
CC			= cc
LIB_INC		= -lm -Lmlx -lmlx_Linux -lmlx -lXext -lX11

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

bonus:		${NAME_B}

${NAME_B}:	${OBJS_BONUS} ${LIB}
			@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIB_INC) -o $(NAME_B) $(INCS_BONUS)
			@echo "${MSG_BUILD}${NAME_B}${MSG_FINISH}"

${LIB}:
			@echo "${MSG_LIB}${LIB}"
			@make -C mlx >/dev/null 2>/dev/null || true

# Other rules
clean:
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"
			@rm -rf ${OBJS_PATH_BONUS}
			@echo "${MSG_RMV}${OBJS_PATH_BONUS}*"
			@make -C mlx clean >/dev/null 2>/dev/null || true
			@echo "${MSG_RMV}${LIB}"

fclean:		clean
			@rm -rf ${NAME}
			@rm -rf ${B_NAME}
			@echo "${MSG_RMV}${NAME}"

re:			fclean all

re_bonus:	fclean bonus

.PHONY:		all clean fclean re bonus re_bonus
