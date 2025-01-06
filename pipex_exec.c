/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:54:32 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:12 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *env, int input, int output, int cmd)
{
	env->exec = ft_split(env->argv[cmd], ' ');
	ft_printf(1, "exec : %s\n", env->exec[0]);
	if (input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (env->output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	execve(env->exec[0], env->exec, env->env);
	perror("execve failed");
	exit(EXIT_FAILURE);
}