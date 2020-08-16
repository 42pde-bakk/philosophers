# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/08/16 04:55:21 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one.out

ifeq ($(shell uname), Linux)
 CXX = gcc
else
 CXX = clang
endif
ifdef REALG
 CXX = ~/.brew/bin/gcc-10
endif
FLAGS = -Wall -Wextra -Werror -pedantic
ifdef DEBUG
 FLAGS += -g -fsanitize=address
endif

FILES = main.c utils.c gettime.c

all: $(NAME)

$(NAME):
	$(CXX) $(FILES) $(FLAGS) -o $(NAME)
	
clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

