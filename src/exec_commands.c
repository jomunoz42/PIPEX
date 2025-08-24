/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/24 22:02:22 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int 	handling_here_doc(char **argv, t_pipe *get, int temp)
{
	char	*line;
	int		length;
	int		pipefd[2];

	pipe(pipefd);
	if (pipefd[0] < 0)
		return (-1);           /////////
	length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !*line || (ft_strncmp(argv[2], line, length) == 0) && line[length] == '\n')
		{
			free(line);
			close(pipefd[1]);
			get->in = pipefd[0];
			temp = pipefd[0];
			get->index++;
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	return (temp);
}

void get_outfile(char **argv, t_pipe *get)
{
	if (!argv[get->index + 2])
	{
		close(get->out);
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (get->out == -1)
                handle_outfile_error(argv, get);
	}
}

void create_command(char **argv, char **env, t_pipe *get, int *pipefd)
{
	int	 	pid;
	char 	*path;
    char 	**cmd;

	pid = fork();
	if (pid == 0)
	{
        get_outfile(argv, get);
		dup2(get->out, 1);
		close(get->out);
		dup2(get->in, 0);
		close(get->in);
		close(pipefd[0]);
        if (get->index < get->last_arg)
        {
		    cmd = ft_split(argv[get->index], ' ');
		    path = get_absolute_path(env, cmd[0]);
		    execve(path, cmd, env);
		    handle_path_not_found(path, cmd);
        }
	}
	close(get->in);
	close(get->out);
}

void exec(char **argv, char **env, t_pipe *get)
{
	int		pipefd[2];
	int		temp;
	
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		temp = handling_here_doc(argv, get, temp);
	else
	{
		get->in = open(argv[1], O_RDONLY);
		temp = get->in;
    	if (get->in == -1)
    		handle_infile_error(argv, get);
	}
	while (argv[get->index])
	{
		if (argv[get->index + 2])
		{
			pipe(pipefd);
			get->out = pipefd[1];
		}
		create_command(argv, env, get, pipefd);
		get->in = pipefd[0];
		get->index++;
	}
	close(temp);
	wait(NULL);
}
