/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:00:56 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/06 17:05:18 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/ft_libft/ft_libft.h"
# include "Libft/ft_printf/ft_printf.h"
# include "Libft/get_next_line/get_next_line.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

# ifndef ERROR
# define ERROR -1
# endif

typedef	struct s_pipex
{
	pid_t	child1;
	pid_t	child2;
	char	**exec;
	char 	**argv;
	char 	**env;
	int		pipe_fd[2];
	int		argc;
	int		output;
	int		input;
	int		fd1;
	int		fd2;
}	t_pipex;

void	ft_exit(t_pipex *env, int message);
void	first_child_creation(t_pipex *env);
void	second_child_creation(t_pipex *env);
void	execute_command(t_pipex *env, int input, int output, int cmd);
int		parent(t_pipex *env);
int		pipex(int argc, char **argv, char **envp);
int 	security(t_pipex *env);

#endif