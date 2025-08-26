/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:32:01 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/26 22:49:37 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static	void	control_d_message(char **argv, t_pipe *get)
{
	if (get->eof_no_limiter == 1)
    {
        write(2, "bash: warning: here-document delimited by end-of-file (wanted `", 62);
        write(2, argv[2], get->length);
        write(2, "')\n", 3);
    }
}

int handling_here_doc(char **argv, t_pipe *get)
{
    char *line;
    int pipefd[2];

    if (pipe(pipefd) == -1)
        handling_error("pipe");
    get->length = ft_strlen(argv[2]);
    while (1)
    {
        line = get_next_line(0);
        if (!line) // EOF (Ctrl+D)
        {
            get->eof_no_limiter = 1;
            free(line);
            break;
        }
        if (!*line || (ft_strncmp(argv[2], line, get->length) == 0 && line[get->length] == '\n'))
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        free(line);
    }
    close(pipefd[1]);
    get->in = pipefd[0];
    get->index++;
    control_d_message(argv, get);
    return (get->in);
}
 */
/* 
int	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		handling_error("pipe");
	get->length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		if (control_d_pressed(line, pipefd, get) == 1)
			break;
		if (!line || !*line || ((ft_strncmp(argv[2], line, get->length) == 0)
				&& line[get->length] == '\n'))
		{
			free(line);
			close(pipefd[1]);
			get->in = pipefd[0];
			get->index++;
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	control_d_message(argv, get);
	return (get->in);
} */
