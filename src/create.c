/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:45:41 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/29 23:19:01 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		pipefd[2];
	int		length;

	if (pipe(pipefd) == -1)
		handling_error("pipe", get);
	length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !*line || ((ft_strncmp(argv[2], line, length) == 0)
				&& line[length] == '\n'))
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
	return (get->in);
}

void	create_pipe(char **argv, char **env, t_pipe *get)
{
	while (get->index < get->last_arg)
	{
		if (argv[get->index + 2])
		{
			if (pipe(get->pipefd) == -1)
				handling_error("pipe", get);
			get->out = get->pipefd[1];
		}
		execute_command(argv, env, get, get->pipefd);
		get->in = get->pipefd[0];
		get->index++;
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		get->index = 3;
	else
		get->index = 2;
	while (get->index < get->last_arg)
	{
		wait(NULL);
		get->index++;
	}
}
