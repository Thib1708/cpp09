# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 11:12:25 by tgiraudo          #+#    #+#              #
#    Updated: 2023/09/21 09:37:22 by tgiraudo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE

NAME			=	btc

LIST_SRCS		=	main.cpp			\
					BitcoinExchange.cpp	\

LIST_INCS		=	BitcoinExchange.hpp

# DIRECTORY
DIR_OBJS		=	.objs/

DIR_SRCS		=	srcs/

DIR_INCS		=	include/

# CONSTANT

PRINT 			= 	@printf

FLAGS			=	-Wall -Wextra -Werror -g3

STD				=	-std=c++98

MAKEFLAGS		+=	--no-print-directory

CC 				=	c++

OBJS 			=	$(patsubst %.cpp, $(DIR_OBJS)%.o, $(SRCS))

SRCS			=	${addprefix ${DIR_SRCS}, ${LIST_SRCS}}

INCLUDES		=	${addprefix ${DIR_INCS}, ${LIST_INCS}}

# COLOR

RED 			=	\033[1;31m
GREEN 			=	\033[1;32m
YELLOW 			=	\033[1;33m
SUPPR   		=	\r\033[2K
DEFAULT 		=	\033[0m

# RULES

${DIR_OBJS}%.o 	:	%.cpp Makefile  ${INCLUDES}
				@mkdir -p $(shell dirname $@)
				@${PRINT} "${YELLOW}${SUPPR}Creating ${NAME}'s objects : $@${DEFAULT}"
				@${CC} ${FLAGS} ${STD} -I ${DIR_INCS} -c $< -o $@ 

${NAME}			:	${OBJS} ${INCLUDES}
				@${PRINT} "${GREEN}${SUPPR}Creating ${NAME}'s objects : DONE${DEFAULT}"
				@${PRINT} "\n${YELLOW}Compiling ${NAME}...${DEFAULT}"
				@${CC} ${OBJS} -o ${NAME} # -fsanitize=address
				@${PRINT} "\r${GREEN}Compiling ${NAME} : DONE${DEFAULT}\n\n"

all				:	${NAME}

clean			:
				@${PRINT} "${RED}Deleting objects : DONE\n"
				@rm -rf ${DIR_OBJS}

fclean			:	clean
				@${PRINT} "${RED}Deleting executable : DONE\n\n${DEFAULT}"
				@rm -f ${NAME}

re				:	fclean all

${DIR_OBJS}		:
				mkdir -p ${DIR_OBJS}

.PHONY		: all clean fclean re