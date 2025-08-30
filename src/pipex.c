/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/30 23:10:31 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ctrl_d_pressed(char **argv, t_pipe *get, int *pipefd, char *line)
{
	if (!line)
	{
		write(2, "bash: warning: here-document delimited by end-of-file (wanted `", 63);
		write(2, argv[2], get->length);
		write(2, "')\n", 3);
		close(pipefd[1]);
	    get->infile = pipefd[0];
		get->eof_no_limiter = 1;
	}
}

static void	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		handling_error("pipe", get);
	get->length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		ctrl_d_pressed(argv, get, pipefd, line);
		if (get->eof_no_limiter == 1)
			break ;
		if (!*line || ((ft_strncmp(argv[2], line, get->length) == 0)
				&& line[get->length] == '\n'))
		{
			free(line);
			close(pipefd[1]);
			get->infile = pipefd[0];
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
}

void	only_child_edge_case(t_pipe *get) // does here_doc return -1????????????
{
	if (get->child == get->cmd_number && get->child == 1)
	{
		get->here_doc_exists = 1;
		if (get->outfile == -1)
		{
			close(get->pipefd[0]);
			close(get->pipefd[1]);
			// if (get->infile != -1)
			// 	close(get->infile);                  can it be -1?
			exit(126);
		}
		dup2(get->infile, 0);
		close(get->infile);
		dup2(get->outfile, 1);
		close(get->outfile);
		close(get->outfile);
		// if (get->infile != -1)
		// 	close(get->infile);                  can it be -1?
	}
}

static void	get_infile_and_outfile(int argc, char **argv, t_pipe *get)
{
	if (argc < 5)
		(write(2, "Error. Invalid number of arguments\n", 35), exit(1));
	get->child = 1;
	get->last_arg = argc - 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		handling_here_doc(argv, get);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_APPEND,  0644);
		if (get->outfile == -1)
			handle_outfile_error(argv, get);
		get->cmd_number = argc - 4;
		get->index = 3;
	}
	else
	{
		get->infile = open(argv[1], O_RDONLY);
		if (get->infile == -1)
			handle_infile_error(argv);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (get->outfile == -1)
		 	handle_outfile_error(argv, get);
		get->cmd_number = argc - 3;
		get->index = 2;
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_pipe	get;

	get_infile_and_outfile(argc, argv, &get);
	create_pipe(argv, env, &get);
	close_everything(&get);
	return (0);
}
