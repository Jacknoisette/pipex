/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:09:45 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 13:44:48 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_creation(t_pipex *env)
{
	if (pipe(env->pipe_fd) == -1)
	{
		perror("pipe failed");
		ft_exit(env, ERROR);
	}
}

void	first_child_creation(t_pipex *env)
{
	env->child1 = fork();
	if (env->child1 == -1)
	{
		perror("fork failed");
		ft_exit(env, ERROR);
	}
	if (env->child1 == 0)
	{
		env->input = open(env->argv[1], O_RDONLY);
		if (env->input == -1)
		{
			perror("Error opening input file");
			ft_exit(env, ERROR);
		}
		close(env->pipe_fd[0]);
		execute_command(env, env->input, env->pipe_fd[1], 2);
		close(env->input);
	}
}

void	second_child_creation(t_pipex *env)
{
	env->child2 = fork();
	if (env->child2 == -1)
	{
		perror("fork failed");
		ft_exit(env, ERROR);
	}
	if (env->child2 == 0)
	{
		env->output = open(env->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (env->output == -1)
		{
			perror("Error opening output file");
			ft_exit(env, ERROR);
		}
		close(env->pipe_fd[1]);
		execute_command(env, env->pipe_fd[0], env->output, 3);
		close(env->output);
	}
}

int	parent(t_pipex *env)
{
	pipe_creation(env);
	first_child_creation(env);
	if (env->path != NULL)
		free(env->path);
	second_child_creation(env);
	if (env->path != NULL)
		free(env->path);
	close(env->pipe_fd[0]);
	close(env->pipe_fd[1]);
	waitpid(env->child1, NULL, 0);
	waitpid(env->child2, NULL, 0);
	if (env->exec != NULL)
		free(env->exec);
	return (0);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_pipex	env;

	env.argc = argc;
	env.argv = argv;
	env.env = envp;
	env.pipe_fd[0] = -1;
	env.pipe_fd[1] = -1;
	env.exec = NULL;
	env.path = NULL;
	if (env.argc != 5)
	{
		ft_printf(1, "Wrong number of arg\n");
		ft_exit(&env, ERROR);
	}
	if (security(&env) == -1)
	{
		ft_printf(1, "file error\n");
		ft_exit(&env, ERROR);
	}
	parent(&env);
	return (0);
}
