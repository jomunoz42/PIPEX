/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:35:16 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/19 22:44:02 by jomunoz          ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_pipe
{
    int     index;
    int     in;
    int     out;
    int     infile;
    int     outfile;
    int     last_arg;
}           t_pipe;

//=========================LIBFT==========================

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char d);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

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

//=====================GET_NEXT_LINE=======================

char	*get_next_line(int fd);

//========================ERRORS===========================

void    handle_no_env(char **argv, char **env);

void    handle_infile_error(char **argv, t_pipe *p);

//=========================FREES===========================

void    free_double_ptr(char **split);


#endif