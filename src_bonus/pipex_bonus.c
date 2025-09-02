/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/09/01 19:04:45 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ctrl_d_pressed(char **argv, t_pipe *get, char *line)
{
	if (!line)
	{
		write(2,
			"bash: warning: here-document delimited by end-of-file (wanted `",
			63);
		write(2, argv[2], get->length);
		write(2, "')\n", 3);
		close(get->hdoc_pipe[1]);
		get->infile = get->hdoc_pipe[0];
		get->eof_no_limiter = 1;
	}
}

static void	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;

	if (pipe(get->hdoc_pipe) == -1)
		handling_errors(argv, get, 3);
	get->length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		ctrl_d_pressed(argv, get, line);
		if (get->eof_no_limiter == 1)
			break ;
		if (!*line || ((ft_strncmp(argv[2], line, get->length) == 0)
				&& line[get->length] == '\n'))
		{
			free(line);
			close(get->hdoc_pipe[1]);
			get->infile = get->hdoc_pipe[0];
			break ;
		}
		write(get->hdoc_pipe[1], line, ft_strlen(line));
		free(line);
	}
}

static void	get_infile_and_outfile(int argc, char **argv, t_pipe *get)
{
	if (argc < 5)
		(write(2, "Error. Invalid number of arguments\n", 35), exit(1));
	get->child = 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		handling_here_doc(argv, get);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if (get->outfile == -1)
			handling_errors(argv, get, 2);
		get->cmd_number = argc - 4;
		get->index = 3;
	}
	else
	{
		get->infile = open(argv[1], O_RDONLY);
		if (get->infile == -1)
			handling_errors(argv, get, 1);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		if (get->outfile == -1)
			handling_errors(argv, get, 2);
		get->cmd_number = argc - 3;
		get->index = 2;
	}
}

static void	create_pipe(char **argv, char **env, t_pipe *get)
{
	while (get->index < get->last_arg)
	{
		if (argv[get->index + 2])
		{
			if (pipe(get->pipefd) == -1)
				handling_errors(argv, get, 3);
			get->out = get->pipefd[1];
		}
		execute_children(argv, env, get);
		get->in = get->pipefd[0];
		get->index++;
	}
	get->child = 1;
	while (get->child <= get->cmd_number)
	{
		wait(NULL);
		get->child++;
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_pipe	get;

	get.last_arg = argc - 1;
	get_infile_and_outfile(argc, argv, &get);
	create_pipe(argv, env, &get);
	close_everything(&get);
	return (0);
}
