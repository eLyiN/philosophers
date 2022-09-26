# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 14:51:38 by aarribas          #+#    #+#              #
#    Updated: 2022/09/26 17:53:10 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	$(shell find ./ -iname "*.c")
OBJS	=	${SRCS:.c=.o}
INCLUDE	=	-lpthread

all	:	$(NAME)

$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re	:	clean all

bonus	:	

.PHONY:	all, clean, fclean, re, bonus