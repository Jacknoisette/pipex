/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:47:14 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 11:29:44 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	pipex_bonus(argc, argv, envp);
	return (0);
}

	// char *argv[] = {"ls", "-l", NULL};
	// char *envp[] = {NULL};

	// if (execve("/bin/ls", argv, envp) == -1) 
	// {
	// 	perror("execve failed");
	// 	exit(EXIT_FAILURE);
	// }
	// return 0;