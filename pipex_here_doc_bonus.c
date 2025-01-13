/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:44:18 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 11:29:48 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmpn(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
	{
		i++;
		if (s1[i] != s2[i] && s1[i] == '\n' && s2[i] == '\0')
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void		write_in_hd(t_pipex *env)
{
	char *line;
	
	while (1)
	{
		line = get_next_line(1);
		if (line == NULL)
		{
			env->hd = 0;
			ft_exit_bonus(env, ERROR);
		}
		if (ft_strcmpn(line, env->hd_limit) == 0)
			break ;
		ft_printf(env->hd_fd, "%s", line);
		free(line);
	}
	free(line);
}
void	here_doc(t_pipex *env)
{
	env->hd_limit = env->argv[2];
	env->hd = 1;
	env->hd_fd = ft_open("hd_temp", 2, "here_doc");
	if (env->hd_fd == -1)
	{
		env->hd = 0;
		perror("open here_doc");
		ft_exit_bonus(env, ERROR);
	}
	write_in_hd(env);
	close(env->hd_fd);
	env->hd_fd = ft_open("hd_temp", 0, "here_doc2");
}