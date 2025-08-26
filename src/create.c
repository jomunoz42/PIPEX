/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:45:41 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/26 23:21:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		pipefd[2];
	int		length;

	if (pipe(pipefd) == -1)
		handling_error("pipe");
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

static	void	infile_or_here_doc(char **argv, t_pipe *get)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		get->in = handling_here_doc(argv, get);
	else
	{
		get->in = open(argv[1], O_RDONLY);
		if (get->in == -1)
			handle_infile_error(argv);
	}
}

static void	wait_all_children(char **argv, t_pipe *get)
{
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

void	create_pipe(char **argv, char **env, t_pipe *get)
{
	int	pipefd[2];
	int	temp;

	infile_or_here_doc(argv, get);
	temp = get->in;
	while (get->index < get->last_arg)
	{
		// pipefd[0] = -1;
		// pipefd[1] = -1;
		if (argv[get->index + 2])
		{
			if (pipe(pipefd) == -1)
				handling_error("pipe");
			get->out = pipefd[1];
		}
		execute_command(argv, env, get, pipefd);
		get->in = pipefd[0];
		get->index++;
	}
	if (temp != -1)
		close(temp);
	wait_all_children(argv, get);
}
