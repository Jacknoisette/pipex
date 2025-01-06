/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:18:01 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/06 17:10:30 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int security(t_pipex *env)
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

void	ft_exit(t_pipex *env, int message)
{
	close(env->fd1);
	close(env->fd2);
	exit(message);
}