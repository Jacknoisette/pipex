/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:08:12 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 11:51:19 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_bonus(char *file, int read_or_write)
{
	int	fd;

	if (read_or_write == 0)
		fd = open(file, O_RDONLY);
	else if (read_or_write == 2)
		fd = open(file, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

void	first_child_bonus(t_pipex *env, int i)
{
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		if (env->hd == 0)
			env->input = ft_open_bonus(env->argv[1], 0);
		else
			env->input = env->hd_fd;
		if (env->input == -1)
		{
			perror("Error opening input file");
			ft_exit_bonus(env, ERROR);
		}
		execute_command_bonus(env, env->input, env->pipe_fd[1],
			i + 2 + env->hd);
	}
}

void	middle_child_bonus(t_pipex *env, int i)
{
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		execute_command_bonus(env, env->prev, env->pipe_fd[1], i + 2 + env->hd);
	}
}

void	last_child_bonus(t_pipex *env, int i)
{
	env->child[i] = fork();
	if (env->child[i] == -1)
	{
		perror("fork failed");
		ft_exit_bonus(env, ERROR);
	}
	if (env->child[i] == 0)
	{
		env->output = ft_open_bonus(env->argv[env->argc - 1], 1);
		if (env->output == -1)
		{
			perror("Error opening output file");
			ft_exit_bonus(env, ERROR);
		}
		execute_command_bonus(env, env->prev, env->output, i + 2 + env->hd);
	}
}
