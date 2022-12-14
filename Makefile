#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 17:13:05 by mcourtoi          #+#    #+#              #
#    Updated: 2022/03/14 19:29:17 by mcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

MAIN = ./srcs/main.c 

SRCS = ./srcs/utils.c ./srcs/init.c \
		./srcs/actions.c ./srcs/utils_2.c \
		./srcs/routine.c

OBJS = ${SRCS:.c=.o}
OBJSMAIN = ${MAIN:.c=.o}

INC = ./includes

FLAGS = -Wall -Wextra -Werror -pthread

.c.o:
	${CC} -g3 ${FLAGS} -I${INC} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJS} ${OBJSMAIN}
	    ${CC} ${FLAGS} ${OBJS} ${OBJSMAIN} -o ${NAME}


all:    ${NAME}

clean:
	rm -f ${OBJS} ${OBJSMAIN}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
