# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 14:46:57 by ngiroux           #+#    #+#              #
#    Updated: 2022/09/07 14:19:28 by ngiroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_END		= \033[0m
_COMP		= \033[1;33m
_BUILD		= \033[1;32m
_REMOVE		= \033[1;31m
_LIB		= \033[1;30m

# Messages
COMP		= Compiling
BUILD		= Building
REMOVE		= Removing
LIBX		= Building lib

MSG_COMP	= ${_COMP}${COMP}:	${_END}
MSG_BUILD	= ${_BUILD}${BUILD}:	${_END}
MSG_RMV		= ${_REMOVE}${REMOVE}:	${_END}
MSG_LIB		= ${_LIB}${LIBX}:	${_END}
