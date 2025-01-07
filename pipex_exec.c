/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:54:32 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/07 11:32:04 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path_in_env(t_pipex *env, char **paths)
{
	int		i;

	i = 0;
	while (env->env[i] != NULL)
	{
		if (ft_strncmp(env->env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env->env[i], ':');
			if (paths == NULL)
				ft_exit(env, ERROR);
			break ;
		}
		i++;
	}
	if (paths == NULL)
		ft_exit(env, ERROR);
	return (paths);
}

int	find_path_command(t_pipex *env)
{
	char	**paths;
	char	*temp;
	int		i;

	paths = NULL;
	paths = find_path_in_env(env, paths);
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			ft_exit(env, ERROR);
		env->path = ft_strjoin(temp, env->exec[0]);
		free(temp);
		if (env->path == NULL)
			ft_exit(env, ERROR);
		if (access(env->path, F_OK) == 0 || access(env->path, X_OK) == 0)
			return (free_tab(paths), 0);
		free(env->path);
		i++;
	}
	ft_printf(2, "command not found: %s\n", env->exec[0]);
	free_tab(paths);
	ft_exit(env, ERROR);
	return (-1);
}

void	execute_command(t_pipex *env, int input, int output, int cmd)
{
	env->exec = ft_split(env->argv[cmd], ' ');
	if (env->exec == NULL)
		ft_exit(env, ERROR);
	if (env->exec[0][0] == '/')
	{
		ft_printf(2, "permission denied: %s\n", env->exec[0]);
		ft_exit(env, ERROR);
	}
	if (input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	find_path_command(env);
	if (env->path == NULL)
		ft_exit(env, ERROR);
	execve(env->path, env->exec, env->env);
	perror("\nexecve failed");
	ft_exit(env, ERROR);
}
