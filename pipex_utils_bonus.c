/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:45:33 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 12:42:22 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	security_bonus(t_pipex *env)
{
	if (env->hd == 0)
	{
		if (access(env->argv[1], F_OK) == -1)
			return (-1);
		if (access(env->argv[1], R_OK) == -1)
			return (-1);
	}
	else
	{
		if (access("hd_temp", F_OK) == -1)
			return (-1);
		if (access("hd_temp", R_OK) == -1)
			return (-1);
	}
	if (access(env->argv[env->argc - 1], F_OK) == -1)
		return (-1);
	if (access(env->argv[env->argc - 1], W_OK) == -1)
		return (-1);
	return (0);
}

void	free_tab_bonus(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_exit_bonus(t_pipex *env, int message)
{
	if (env->pipe_fd[1] != -1)
		close(env->pipe_fd[1]);
	if (env->pipe_fd[0] != -1)
		close(env->pipe_fd[0]);
	if (env->hd == 1)
	{
		if (env->hd_fd != -1)
			close(env->hd_fd);
	}
	if (env->exec != NULL)
		free_tab_bonus(env->exec);
	if (env->child != NULL)
		free(env->child);
	if (env->hd == 1 && unlink("hd_temp") == -1)
		perror("Failed to unlink hd_temp");
	exit(message);
}
