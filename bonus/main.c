/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:47:14 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/07 10:10:41 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
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