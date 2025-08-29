/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/29 23:25:41 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dups_and_closes(t_pipe *get)
{
	if (get->cmd_number == 0)
	{
		if (get->infile == -1)
		{
			close(get->pipefd[0]);
			close(get->pipefd[1]);
			if (get->outfile != -1)
				close(get->outfile);
			exit(126);
		}
		get->in = get->infile;
		dup2(get->pipefd[1], 1);
		close(get->pipefd[1]);
		dup2(get->in, 0);
		close(get->in);
		close(get->pipefd[0]);
		if (get->outfile != -1)
			close(get->outfile);
	}
}

void	execute_command(char **argv, char **env, t_pipe *get, int *pipefd)
{
	int		pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		handling_error("Error fork", get);
	else if (pid == 0)
	{


		
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
