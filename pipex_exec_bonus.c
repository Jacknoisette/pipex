/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:10:03 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 13:53:46 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**find_path_in_env_bonus(t_pipex *env, char **paths)
{
	int		i;

	i = 0;
	while (env->env[i] != NULL)
	{
		if (ft_strncmp(env->env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env->env[i], ':');
			if (paths == NULL)
				ft_exit_bonus(env, ERROR);
			break ;
		}
		i++;
	}
	if (paths == NULL)
		ft_exit_bonus(env, ERROR);
	return (paths);
}

int	path_finder(t_pipex *env)
{
	char	**paths;
	char	*temp;
	int		i;

	paths = NULL;
	paths = find_path_in_env_bonus(env, paths);
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			ft_exit_bonus(env, ERROR);
		env->path = ft_strjoin(temp, env->exec[0]);
		free(temp);
		if (env->path == NULL)
		{
			free_tab_bonus(paths);
			ft_exit_bonus(env, ERROR);
		}
		if (access(env->path, F_OK) == 0 || access(env->path, X_OK) == 0)
			return (free_tab_bonus(paths), 0);
		free(env->path);
		i++;
	}
	return (free_tab_bonus(paths), -1);
}

int	find_path_command_bonus(t_pipex *env)
{
	int	res;

	if (env->exec[0][0] == '/')
	{
		if (env->exec[0][1] == '\0')
			ft_exit_bonus(env, ERROR);
		env->path = ft_strdup(env->exec[0]);
		if (access(env->path, F_OK | X_OK) == 0)
			return (0);
		ft_printf(2, "command not found: %s\n", env->exec[0]);
		free(env->path);
		ft_exit_bonus(env, ERROR);
	}
	res = path_finder(env);
	if (res == 0)
		return (0);
	ft_printf(2, "command not found: %s\n", env->exec[0]);
	ft_exit_bonus(env, ERROR);
	return (-1);
}

void	execute_command_bonus(t_pipex *env, int input, int output, int cmd)
{
	env->exec = ft_split(env->argv[cmd], ' ');
	if (env->exec == NULL)
		ft_exit_bonus(env, ERROR);
	if (input != STDIN_FILENO)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			ft_exit_bonus(env, ERROR);
		close(input);
	}
	if (output != STDOUT_FILENO)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			ft_exit_bonus(env, ERROR);
		close(output);
	}
	find_path_command_bonus(env);
	if (env->path == NULL)
		ft_exit_bonus(env, ERROR);
	if (env->path[ft_strlen(env->path) - 1] == '/')
	{
		ft_printf(2, "permission denied: %s\n", env->exec[0]);
		ft_exit_bonus(env, ERROR);
	}
	execve(env->path, env->exec, env->env);
	ft_exit_bonus(env, ERROR);
}
