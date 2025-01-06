# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:17:46 by jdhallen          #+#    #+#              #
#    Updated: 2025/01/06 17:05:28 by jdhallen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

NAME = pipex.a
executable = pipex
LIBFT_DIR = Libft

SRCS = main.c pipex.c pipex_utils.c pipex_exec.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(executable)

$(NAME):
	@$(MAKE) -C $(LIBFT_DIR)
	echo "make ok"

$(executable): $(NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(executable) $(LFLAGS)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	echo "clean ok"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(executable)
	echo "fclean ok"

re: fclean all

.PHONY: all clean fclean re
