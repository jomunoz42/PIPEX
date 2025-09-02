/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:32:21 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/31 23:08:56 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **env)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			str = env[i];
	}
	if (!*env)
		str = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	return (str);
}

static char	*get_absolute_path(char **env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*temp;
	char	*str;
	int		i;

	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_strdup(""));
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	str = get_path(env);
	if (str == NULL)
		return (NULL);
	i = -1;
	dirs = ft_split(str, ':');
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (free_double_ptr(dirs), path);
		free(path);
	}
	return (free_double_ptr(dirs), NULL);
}

static void	child1(char **env, char **argv, t_pipe *get)
{
	char	**cmd1;
	char	*path1;

	if (get->infile == -1)
	{
		close(get->pipefd[0]);
		close(get->pipefd[1]);
		if (get->outfile != -1)
			close(get->outfile);
		exit(126);
	}
	dup2(get->pipefd[1], 1);
	close(get->pipefd[1]);
	dup2(get->infile, 0);
	close(get->infile);
	close(get->pipefd[0]);
	if (get->outfile != -1)
		close(get->outfile);
	cmd1 = ft_split(argv[2], ' ');
	path1 = get_absolute_path(env, cmd1[0]);
	if (path1)
		execve(path1, cmd1, env);
	handle_path_not_found(path1, cmd1);
}

static void	child2(char **env, char **argv, t_pipe *get)
{
	char	**cmd2;
	char	*path2;

	if (get->outfile == -1)
	{
		close(get->pipefd[0]);
		close(get->pipefd[1]);
		if (get->infile != -1)
			close(get->infile);
		exit(126);
	}
	dup2(get->pipefd[0], 0);
	close(get->pipefd[0]);
	dup2(get->outfile, 1);
	close(get->outfile);
	close(get->pipefd[1]);
	if (get->infile != -1)
		close(get->infile);
	cmd2 = ft_split(argv[3], ' ');
	path2 = get_absolute_path(env, cmd2[0]);
	if (path2)
		execve(path2, cmd2, env);
	handle_path_not_found(path2, cmd2);
}

int	main(int argc, char **argv, char **env)
{
	static t_pipe	get;
	int				status;

	handle_args_infile_outfile(argc, argv, &get);
	if (pipe(get.pipefd) == -1)
		handling_errors(argv, &get, 3);
	get.pid1 = fork();
	if (get.pid1 == -1)
		handling_errors(argv, &get, 4);
	if (get.pid1 == 0)
		child1(env, argv, &get);
	get.pid2 = fork();
	if (get.pid2 == -1)
		handling_errors(argv, &get, 4);
	if (get.pid2 == 0)
		child2(env, argv, &get);
	close_everything(&get);
	waitpid(get.pid1, NULL, 0);
	waitpid(get.pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
