/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:35:16 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/13 21:09:12 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <ctype.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdarg.h>

typedef struct s_pipe
{
    int     count;
    int     cmds;
    pid_t   *processes;
    int     pipe1[2];
    int     pipe2[2];
    int     fd1;
    int     fd2;
}           t_pipe;

//=========================LIBFT==========================

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char d);

//=========================//////==========================

char    *find_absolute_path(char *str, char *cmd);
char    *find_path(char **env, char *str, int size);

//=========================//////==========================

// void    first_children(char **argv, char **env, t_pipe *p);
// void    second_children(char **argv, char **env, t_pipe *p);

void    create_children(char **argv, char **env, t_pipe *p);

//=======================FT_PRINTF=========================

int	    ft_putchar_count(char c);
int	    ft_putstr_count(char *s);
int	    ft_putnbr_count(long n);
int	    ft_putunbr_count(long n);
int	    ft_hexa_lower(unsigned int n);
int	    ft_hexa_upper(unsigned int n);
int	    ft_hexa_lower_p(size_t n);
int	    ft_pointer_hexa(void *n);
int	    ft_printf(const char *format, ...);

#endif