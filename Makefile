# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 14:51:38 by aarribas          #+#    #+#              #
#    Updated: 2022/09/23 16:01:57 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	$(shell find .inname "*.c")
OBJS	=	${SRCS:.c=.o}

all	:	
clean	:	
fclean	:	
re	:	
bonus	:	

.PHONY:	all, clean, fclean, re, bonus