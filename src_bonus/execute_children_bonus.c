/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/09/01 19:20:47 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	only_child_edge_case(t_pipe *get)
{
	if (get->child == get->cmd_number && get->child == 1)
	{
		get->only_one_cmd_exists = 1;
		if (get->outfile == -1)
		{
			close(get->hdoc_pipe[0]);
			exit(126);
		}
		dup2(get->infile, 0);
		close(get->infile);
		dup2(get->outfile, 1);
		close(get->outfile);
	}
}

static void	first_child(t_pipe *get)
{
	if (get->only_one_cmd_exists == 1)
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
		close(get->pipefd[0]);
		if (get->infile != -1)
			close(get->infile);
		if (get->outfile != -1)
			close(get->outfile);
	}
}

static void	last_child(t_pipe *get)
{
	if (get->only_one_cmd_exists == 1)
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

void	execute_children(char **argv, char **env, t_pipe *get)
{
	int		pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		handling_errors(argv, get, 4);
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
