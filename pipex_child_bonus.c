/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:08:12 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/08 17:20:32 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open(char *file, int read_or_write, char *where)
{
	int fd;

	if (read_or_write == 0)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fprintf(stderr, "open = %d at %s\n", fd, where);
	return (fd);
}

void	first_child_bonus(t_pipex *env, int i)
{
	// ft_printf(1, "If no one start, this will never end\n");
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		env->input = ft_open(env->argv[1], 0, "first child");
		dprintf(2, "input : %i\n", env->input);
		if (env->input == -1)
		{
			perror("Error opening input file");
			ft_exit_bonus(env, ERROR);
		}
		execute_command_bonus(env, env->input, env->pipe_fd[1], i + 2);
	}
}

void	middle_child_bonus(t_pipex *env, int i)
{
	// ft_printf(1, "Always a middle man in good interraction\n");
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		execute_command_bonus(env, env->prev, env->pipe_fd[1], i + 2);
	}
}

void	last_child_bonus(t_pipex *env, int i)
{
	// ft_printf(1, "I am here at last\n");
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		env->output = ft_open(env->argv[env->argc - 1], 1, "second child");
		dprintf(2, "output : %i\n", env->output);
		if (env->output == -1)
		{
			perror("Error opening output file");
			ft_exit_bonus(env, ERROR);
		}
		execute_command_bonus(env, env->prev, env->output, i + 2);
	}
}