/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:35 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/22 23:29:51 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_path(char **env, char *cmd)
{
    char	**dirs;
    char 	*path;
    char 	*temp;
    char 	*str;
	int 	i;

    if (access(cmd, X_OK) == 0)
            return (cmd);
    i = -1;
    while (env[++i])
    {
        if (ft_strnstr(env[i], "PATH=", 5))
            str = env[i];
    }
	if (str == NULL)
		(write(2, "PATH not found\n", 15), exit(1));    //////////////////////
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

void 	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		length;
	int		pipefd[2];

	pipe(pipefd);
	if (pipefd[0] < 0)
		return ;           /////////
	length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !*line || (ft_strncmp(argv[2], line, length) == 0) && line[length] == '\n')
		{
			free(line);
			close(pipefd[1]);
			get->in = pipefd[0];
			get->index++;
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
}

void get_infile_and_outfile(char **argv, t_pipe *get)
{
    if (get->index == 2)
	{
		get->in = open(argv[1], O_RDONLY);
    	if (get->in == -1)
    		handle_infile_error(argv, get);
	}
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
        get_infile_and_outfile(argv, get);
		dup2(get->out, 1);
		close(get->out);
		dup2(get->in, 0);
		close(get->in);
		// if (pipefd[0] != -1)
    	// close(pipefd[0]);
		// if (pipefd[1] != -1)
   		// 	close(pipefd[1]);
        if (get->index < get->last_arg)
        {
		    cmd = ft_split(argv[get->index], ' ');
		    path = get_path(env, cmd[0]);
		    handle_path_not_found(path, cmd);
		    execve(path, cmd, env);
		    free_double_ptr(cmd);
		    free(path);
		    exit(127);
        }
	}
	close(get->in);
	close(get->out);
}

void exec(char **argv, char **env, t_pipe *get)
{
	int		pipefd[2];
	
	pipefd[0] = -1;
	pipefd[1] = -1;
	get->index = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		handling_here_doc(argv, get);
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
	get->index = 1;
	while (argv[get->index])
	{	
		wait(NULL);
		get->index++;
	}
}
