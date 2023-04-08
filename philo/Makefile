# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 18:05:23 by jerhee            #+#    #+#              #
#    Updated: 2023/04/08 18:05:25 by jerhee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
NAME	=	philo
SRCS	=	main.c monitor.c parse.c utils.c \
			philosophers.c philosophers_utils.c
OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

%.o		:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -rf $(NAME)

re		:	fclean all