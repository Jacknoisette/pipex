/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:11:56 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 11:02:54 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "Libft/ft_libft/ft_libft.h"
# include "Libft/ft_printf/ft_printf.h"
# include "Libft/get_next_line/get_next_line.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

# ifndef ERROR
#  define ERROR -1
# endif

// # define close(fd) \
// do \
// { \
// 	fprintf(stderr, "close(%d) at %s:%d\n", \
// 			fd, __FILE__, __LINE__); \
// 	close(fd); \
// } while (0)

// # define pipe(pipefd) \
// ({ \
// 	int ret = pipe(pipefd); \
// 	if (ret == -1) \
// 		fprintf(stderr, "pipe(%p) at %s:%d failed: %s\n", \
// 				pipefd, __FILE__, __LINE__, strerror(errno)); \
// 	else \
// 		fprintf(stderr, "pipe("#pipefd") = {%d,%d} at %s:%d\n", \
// 		pipefd[0], pipefd[1], \
// 		__FILE__, __LINE__); \
// 	ret; \
// })

// # define dup2(fd1, fd2) \
// ({ \
// 	int ret = dup2(fd1, fd2); \
// 	fprintf(stderr, "dup2(%d, %d) at %s:%d\n", \
// 			fd1, fd2, __FILE__, __LINE__); \
// 	if (ret == -1) \
// 	 	perror("dup2"); \
// 	ret; \
// })

typedef struct s_pipex
{
	pid_t	*child;
	char	**exec;
	char	**argv;
	char	**env;
	char	*path;
	char	*hd_limit;
	int		hd;
	int		hd_fd;
	int		hd_size;
	int		pipe_fd[2];
	int		prev;
	int		argc;
	int		output;
	int		input;
	int		fd1;
	int		fd2;
	int		i;
}	t_pipex;

void	ft_exit_bonus(t_pipex *env, int message);
void	first_child_bonus(t_pipex *env, int i);
void	middle_child_bonus(t_pipex *env, int i);
void	last_child_bonus(t_pipex *env, int i);
void	free_tab_bonus(char **tab);
void	execute_command_bonus(t_pipex *env, int input, int output, int cmd);
void	here_doc(t_pipex *env);
int		parent_bonus(t_pipex *env);
int		pipex_bonus(int argc, char **argv, char **envp);
int		security_bonus(t_pipex *env);

int		ft_open(char *file, int read_or_write, char *where);

#endif