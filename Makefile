# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:17:46 by jdhallen          #+#    #+#              #
#    Updated: 2025/01/07 12:33:22 by jdhallen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

NAME = pipex.a
exec = pipex
exec_bonus = pipex_bonus
LIBFT_DIR = Libft

SRCS = main.c pipex.c pipex_utils.c pipex_exec.c
BONUS = main_bonus.c pipex_bonus.c pipex_utils_bonus.c \
	pipex_exec_bonus.c pipex_child_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

all: $(NAME) $(exec)

bonus : $(NAME) $(exec_bonus)

$(NAME):
	@$(MAKE) -C $(LIBFT_DIR)
	echo "make ok"

$(exec): $(NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(exec) $(LFLAGS)

$(exec_bonus): $(NAME) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(exec_bonus) $(LFLAGS)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	echo "clean ok"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(exec)
	@rm -f $(exec_bonus)
	echo "fclean ok"

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re
