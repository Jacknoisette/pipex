/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:12:00 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/08 18:02:36 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_creation_bonus(t_pipex *env)
{
	if (pipe(env->pipe_fd) == -1)
	{
		perror("pipe failed");
		ft_exit_bonus(env, ERROR);
	}
}

int	parent_bonus(t_pipex *env)
{
	int	j;
	
	env->child = malloc((env->argc - 4) * sizeof(pid_t));
	if (env->child == NULL)
		ft_exit_bonus(env, ERROR);
	env->i = 0;
	while (env->i < env->argc - 3)
	{
		dprintf(2, "\nchild number %d\n", env->i);
		if (env->i > 0)
		{
			if (env->prev == env->pipe_fd[0])
				ft_printf(1, "okayyy\n");
			env->prev = env->pipe_fd[0];
			close(env->pipe_fd[0]);
			close(env->pipe_fd[1]);
		}
		// if (env->i < env->argc - 4)
		pipe_creation_bonus(env);
		ft_printf(1, "i : %s\n", env->argv[env->i + 2]);
		ft_printf(1, "i : %i\n", env->i);
		if (env->i == 0)
			first_child_bonus(env, env->i);
		else if (env->i == env->argc - 4)
			last_child_bonus(env, env->i);
		else
			middle_child_bonus(env, env->i);
		close(env->pipe_fd[1]);
		if (env->path != NULL)
		{
			free(env->path);
			env->path = NULL;
		}
		env->i++;
		sleep(1);
	}
	close(env->pipe_fd[0]);
	close(env->pipe_fd[1]);
	j = 0;
	while (j < env->argc - 3)
	{
		waitpid(env->child[j], NULL, 0);
		ft_printf(1,"|%i\n", j);
		j++;
	}
	if (env->exec != NULL)
		free(env->exec);
	if (env->child != NULL)
		free(env->child);
	return (0);
}

int	pipex_bonus(int argc, char **argv, char **envp)
{
	t_pipex	env;

	env.argc = argc;
	env.argv = argv;
	env.env = envp;
	env.exec = NULL;
	env.path = NULL;
	if (env.argc < 5)
	{
		ft_printf(1, "Wrong number of arg\n");
		ft_exit_bonus(&env, ERROR);
	}
	if (security_bonus(&env) == -1)
	{
		ft_printf(1, "file error\n");
		ft_exit_bonus(&env, ERROR);
	}
	parent_bonus(&env);
	return (0);
}