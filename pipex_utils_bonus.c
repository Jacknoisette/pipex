/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:45:33 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/08 11:22:25 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	security_bonus(t_pipex *env)
{
	if (access(env->argv[1], F_OK) == -1)
		return (-1);
	if (access(env->argv[env->argc - 1], F_OK) == -1)
		return (-1);
	if (access(env->argv[1], R_OK) == -1)
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
	ft_printf(1, "When there is a problem you know it\n");
	if (env->exec != NULL)
		free_tab_bonus(env->exec);
	if (env->child != NULL)
		free(env->child);
	exit(message);
}

