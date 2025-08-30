/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/30 23:08:10 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipe *get)
{
	if (get->here_doc_exists == 1)
		return ;
	if (get->child == 1)
	{
		if (get->infile == -1)
		{
			close(get->pipefd[0]);
			close(get->pipefd[1]);
			if (get->outfile != -1)
				close(get->outfile);
			exit(126);
		}
		dup2(get->out, 1);
		close(get->out);
		dup2(get->infile, 0);
		close(get->infile);
		close(get->pipefd[0]);
		if (get->outfile != -1)
			close(get->outfile);
	}
}

static void	middle_children(t_pipe *get)
{
	if (get->child > 1 && get->child < get->cmd_number)
	{
		dup2(get->in, 0);
		close(get->in);
		dup2(get->out, 1);
		close(get->out);
		if (get->infile != -1)
			close(get->infile);
		if (get->outfile != -1)
			close(get->outfile);
	}
}

static void	last_child(t_pipe *get)
{
	if (get->here_doc_exists == 1)
		return ;
	if (get->child == get->cmd_number)
	{
		if (get->outfile == -1)
		{
			close(get->pipefd[0]);
			close(get->pipefd[1]);
			if (get->infile != -1)
				close(get->infile);
			exit(126);
		}
		dup2(get->in, 0);
		close(get->in);
		dup2(get->outfile, 1);
		close(get->outfile);
		close(get->out);
		if (get->infile != -1)
			close(get->infile);
	}
}

static void	execute_children(char **argv, char **env, t_pipe *get)
{
	int		pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		handling_error("Error fork", get);
	if (pid == 0)
	{
		only_child_edge_case(get);
		first_child(get);
		middle_children(get);
		last_child(get);
		cmd = ft_split(argv[get->index], ' ');
		path = get_absolute_path(env, cmd[0]);
		if (path)
			execve(path, cmd, env);
		handle_path_not_found(path, cmd);
	}
	if (!(get->child == 1))
		close(get->in);
	close(get->out);
	get->child++;
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
