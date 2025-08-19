/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/19 23:28:23 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char    *get_path(char **env, char *cmd)
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

static	void 	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;
	int		length;
	int		pipefd[2];

	pipe(pipefd);
	if (pipefd[0] < 0)
		return ;
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

void create_command(char **argv, char **env, t_pipe *get)
{
	int	 	pid;
	char 	*path;
    char 	**cmd;
	
	pid = fork();
	if (pid == 0)
	{
		if (get->index == 2)
		{
			close(get->in);
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
		}
		dup2(get->out, 1);
		close(get->out);
		dup2(get->in, 0);
		close(get->in);
		cmd = ft_split(argv[get->index], ' ');
		path = get_path(env, cmd[0]);
		// if (!path)
		// {
		// 	write(2, cmd, ft_strlen(cmd[0]));
		// 	write(2, ": command not found\n", 20);
		// }
		execve(path, cmd, env);
		free_double_ptr(cmd);
		free(path);
		exit(127);
	}
	close(get->in);
	close(get->out);
}

void exec(char **argv, char **env, t_pipe *get)
{
	int pipefd[2];

	get->index = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		handling_here_doc(argv, get);
	else
	 	get->in = dup(0);
	while (argv[get->index])
	{
		get->out = dup(1);
		if (argv[get->index + 2])
		{
			pipe(pipefd);
			close(get->out);
			get->out = pipefd[1];
		}
		create_command(argv, env, get);
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

int main(int argc, char **argv, char **env)
{
	static	t_pipe	get;
	
    if (argc < 5)
    {
    	write(2, "Error. Invalid number of arguments", 34);
    	exit(1);
    }
	handle_no_env(argv, env); //////
	get.last_arg = argc - 1;
	exec(argv, env, &get);
	return (0);
}

//     Freeing all allocated memory.

//     Execute with absolute path.

//     Handle no environment case (comand not found)

//     (comand not found)

//     "" para o grep

//     o caso da empty string, ver se faz sentido o que ele disse

//     ver os casos das permissoes

//     ver o caso do ls caso o file1 nao exista

