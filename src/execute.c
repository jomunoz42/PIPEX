/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/26 23:21:23 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_outfile(char **argv, t_pipe *get)
{
	if (!argv[get->index + 2])
	{
		if (get->out != -1)
            close(get->out);
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (get->out == -1)
			handle_outfile_error(argv, get);
	}
}

static void	copy_and_close(t_pipe *get, int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (get->out != -1)
	{
		if (dup2(get->out, 1) == -1)
        	handling_error("dup2 stdout");
		close(get->out);
	}
	if (get->in == -1)
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		exit(1);
	}
	else if (get->in != -1)
	{
		if (dup2(get->in, 0) == -1)
        	handling_error("dup2 stdin");
		close(get->in);
	}
	// if (pipefd[0] != -1)
	// 	close(pipefd[0]);
}

void	execute_command(char **argv, char **env, t_pipe *get, int *pipefd)
{
	int		pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		handling_error("fork");
	else if (pid == 0)
	{
		get_outfile(argv, get);
		copy_and_close(get, pipefd);
		cmd = ft_split(argv[get->index], ' ');
		path = get_absolute_path(env, cmd[0]);
		if (path)
			execve(path, cmd, env);
		handle_path_not_found(path, cmd);
	}
	if (get->in != -1)
		close(get->in);
	if (get->out != -1)
		close(get->out);
}
