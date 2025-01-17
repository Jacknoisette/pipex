/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:12:00 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 14:03:40 by jdhallen         ###   ########.fr       */
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

void	parent_child_exec(t_pipex *env)
{
	if (env->i > 0)
	{
		if (env->i > 1)
			close(env->prev);
		env->prev = env->pipe_fd[0];
		if (env->prev == -1)
			ft_exit_bonus(env, ERROR);
		close(env->pipe_fd[1]);
	}
	if (env->i < env->argc - (4 + env->hd))
		pipe_creation_bonus(env);
	if (env->i == 0)
		first_child_bonus(env, env->i);
	else if (env->i == env->argc - (4 + env->hd))
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
}

int	parent_bonus(t_pipex *env)
{
	int	j;

	env->child = malloc((env->argc - (3 + env->hd)) * sizeof(pid_t));
	if (env->child == NULL)
		ft_exit_bonus(env, ERROR);
	env->i = 0;
	while (env->i < env->argc - (3 + env->hd))
	{
		parent_child_exec(env);
	}
	close(env->pipe_fd[0]);
	close(env->pipe_fd[1]);
	j = 0;
	while (j < env->argc - (3 + env->hd))
	{
		waitpid(env->child[j], NULL, 0);
		j++;
	}
	if (env->exec != NULL)
		free(env->exec);
	if (env->child != NULL)
		free(env->child);
	if (env->hd == 1)
		close(env->hd_fd);
	return (0);
}

int	pipex_bonus(int argc, char **argv, char **envp)
{
	t_pipex	env;

	env.argc = argc;
	env.argv = argv;
	env.env = envp;
	env.pipe_fd[0] = -1;
	env.pipe_fd[1] = -1;
	env.child = NULL;
	env.exec = NULL;
	env.path = NULL;
	env.hd = 0;
	if (env.argc < 2)
		ft_exit_bonus(&env, ERROR);
	if (ft_strncmp(env.argv[1], "here_doc", 9) == 0)
		here_doc(&env);
	if (env.argc < 5 + env.hd)
		ft_exit_bonus(&env, ERROR);
	if (security_bonus(&env) == -1)
	{
		ft_printf(1, "file error\n");
		ft_exit_bonus(&env, ERROR);
	}
	parent_bonus(&env);
	unlink("hd_temp");
	return (0);
}
