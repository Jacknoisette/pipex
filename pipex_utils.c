/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:47:18 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 13:03:58 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	security(t_pipex *env)
{
	if (access(env->argv[1], F_OK) == -1)
		return (-1);
	if (access(env->argv[4], F_OK) == -1)
		return (-1);
	if (access(env->argv[1], R_OK) == -1)
		return (-1);
	if (access(env->argv[4], W_OK) == -1)
		return (-1);
	return (0);
}

void	free_tab(char **tab)
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

void	ft_exit(t_pipex *env, int message)
{
	if (env->pipe_fd[1] != -1)
		close(env->pipe_fd[1]);
	if (env->pipe_fd[0] != -1)
		close(env->pipe_fd[0]);
	if (env->exec != NULL)
		free_tab(env->exec);
	exit(message);
}
