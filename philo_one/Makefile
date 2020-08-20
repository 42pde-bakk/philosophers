# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/08/21 00:54:56 by peer          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one.out

FLAGS = -Wall -Wextra -Werror -pedantic

ifeq ($(shell uname), Linux)
 CXX = gcc
 FLAGS += -pthread
else
 CXX = clang
endif
ifdef REALG
 CXX = ~/.brew/bin/gcc-10
endif
ifdef DEBUG
 FLAGS += -g -fsanitize=address
endif

FILES = main.c philosopher.c initialize_struct.c \
		utils.c gettime.c manager.c

all: $(NAME)

$(NAME):
	$(CXX) $(FILES) $(FLAGS) -o $(NAME)

clean:
	rm -rf $(NAME).dSYM
fclean: clean
	rm -f $(NAME)

re: fclean all
