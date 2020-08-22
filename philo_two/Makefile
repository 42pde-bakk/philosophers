# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/08/22 22:33:28 by peer          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_two.out

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
ifdef THREADDEBUG
 FLAGS += -g -fsanitize=thread
endif

FILES =	main.c philosopher.c \
		initialize_struct.c manager.c \
		utils.c gettime.c

all: $(NAME)

$(NAME):
	$(CXX) $(FILES) $(FLAGS) -o $(NAME)

clean:
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

test: FLAGS += -g -fsanitize=thread
test: re
	TSAN_OPTIONS=second_deadlock_stack=1 ./$(NAME) 4 310 200 100 2
