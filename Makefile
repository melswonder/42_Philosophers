# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:36:04 by hirwatan          #+#    #+#              #
#    Updated: 2025/04/22 18:25:29 by hirwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = 	src/dinner.c \
        src/dinner_util.c \
        src/error.c \
        src/get_set.c \
        src/init.c \
        src/main.c \
        src/philo.c \
        src/safe_function.c \
        src/util.c

OBJS 	= $(SRCS:.c=.o)
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -I./inc

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	
v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

.PHONY: all clean fclean re v