/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:31:55 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/06 17:12:25 by jdhallen         ###   ########.fr       */
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
	}
}

int	parent(t_pipex *env)
{
	pipe_creation(env);
	first_child_creation(env);
	second_child_creation(env);
	close(env->pipe_fd[0]);
    close(env->pipe_fd[1]);
    waitpid(env->child1, NULL, 0);
    waitpid(env->child2, NULL, 0);
	return (0);
}

int pipex(int argc, char **argv, char **envp)
{
	t_pipex	env;
	
	env.argc = argc;
	env.argv = argv;
	env.env = envp;
	if (env.argc != 5)
	{
		ft_printf(1, "Wrong argument number\n");
		exit(ERROR);
	}
	if (security(&env) == -1)
	{	
		ft_printf(1, "Wrong perm in files\n");
		exit(ERROR);
	}
	// env.fd1 = open(argv[1], O_WRONLY);
	// env.fd2 = open(argv[4], O_CREAT, O_WRONLY, O_TRUNC);
	parent(&env);
	close(env.fd1);
	close(env.fd2);
	free(env.exec);
	return (0);
}
