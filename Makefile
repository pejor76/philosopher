# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 11:03:12 by pecampos          #+#    #+#              #
#    Updated: 2023/08/01 10:39:44 by pecampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phil.a

SRC = main.c init.c ft_atoi.c phil.c utils.c

OBJ = $(SRC:.c=.o)

RM = rm -f

CC = gcc 

FLAGS = -Wall -Werror -Wextra

INCLUDE = -lglfw -L /Users/$$USER/.brew/opt/glfw/lib


all:			$(NAME)
				
$(NAME):  		$(OBJ)
				$(CC) $(FLAGS) -c $(SRC)
				$(CC) $(FLAGS) $(SRC) $(INCLUDE) -o philo
				ar rcs $(NAME) $(OBJ)

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME) philo
				
exe: all
	@./$(NAME)
	
re:				fclean 
				make
	
