/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:35:16 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/29 23:22:30 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_pipe
{
	int	length;
	int	index;
	int	in;
	int	out;
	int	infile;
	int	outfile;
	int	last_arg;
	int	eof_no_limiter;
	int	cmd_number;
	int	pipefd[2];
}		t_pipe;

//=========================LIBFT==========================

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char d);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//=====================GET_NEXT_LINE=======================

char	*get_next_line(int fd);

//========================CORE=============================

int		handling_here_doc(char **argv, t_pipe *get);

void	get_infile_and_outfile(char **argv, t_pipe *get);


char	*get_absolute_path(char **env, char *cmd);
void	execute_command(char **argv, char **env, t_pipe *get, int *pipefd);
void	create_pipe(char **argv, char **env, t_pipe *get);

//=======================ERRORS===========================

void	handle_infile_error(char **argv);
void	handle_outfile_error(char **argv, t_pipe *get);
void	handle_path_not_found(char *path, char **cmd);
void	handling_error(char *message, t_pipe *get);;

//=======================FREES============================

void	free_double_ptr(char **split);
void	close_everything(t_pipe *get);
void	free_everything(t_pipe *get);

#endif