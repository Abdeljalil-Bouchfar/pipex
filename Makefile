# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 18:45:55 by abouchfa          #+#    #+#              #
#    Updated: 2022/03/28 16:52:37 by abouchfa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFILE = pipex.c \
		utils/execution_utils.c \
		utils/io_utils.c \
		utils/input_validation_utils.c \
		shared/ft_split.c \
		shared/ft_strjoin.c \
		shared/ft_strchr.c \
		shared/ft_strnstr.c \
		shared/ft_strdup.c \
		shared/ft_strncmp.c \
		shared/ft_strcmp.c \
		shared/ft_strlen.c \
		shared/gnl.c \

BONUSFILE = pipx_bonus.c

CFLAGS = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(CFILE)
	$(CFLAGS) $(CFILE) -o $(NAME)

bonus: all

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
.PHONY: all clean fclean re