# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 14:51:38 by aarribas          #+#    #+#              #
#    Updated: 2022/10/02 23:31:18 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=thread 
SRCS	=	$(shell find ./ -iname "*.c")
OBJS	=	${SRCS:.c=.o}
INCLUDE	=	-lpthread

all	:	$(NAME)

$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME) -g

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re	:	clean all

bonus	:	

.PHONY:	all, clean, fclean, re, bonus, philo