/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:07:30 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/18 22:08:13 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char    *get_path(char **env, char *cmd)
{
    int 	a;
    char	**dirs;
    char 	*path;
    char 	*str;

    if (access(cmd, X_OK) == 0)
            return (cmd);
    a = -1;
    while (env[++a])
    {
        if (ft_strnstr(env[a], "PATH=", 5))
            str = env[a];
    }
	if (str == NULL)
		(write(2, "PATH not found\n", 15), exit(1));
    a = -1;
    dirs = ft_split(str, ':');
    while (dirs[++a])
    {
        path = ft_strjoin(dirs[a], "/");
        path = ft_strjoin(path, cmd);
        if (access(path, X_OK) == 0)
            return (path);
    }
    return (free(path), NULL);
}

void create_command(char **argv, char **env, t_pipe *p)
{
	int	 	pid;
	char 	*path;
    char 	**cmd;
	
	pid = fork();
	if (pid == 0)
	{
		if (p->a == 2)
		{
			close(p->in);
			p->in = open(argv[1], O_RDONLY);
    		if (p->in == -1)
        		handle_infile_error(argv, p);
		}
		if (!argv[p->a + 2])
		{
			close(p->out);
			p->out = open(argv[p->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		dup2(p->out, 1);
		close(p->out);
		dup2(p->in, 0);
		close(p->in);
		cmd = ft_split(argv[p->a], ' ');
		path = get_path(env, cmd[0]);
		execve(path, cmd, env);
		exit(127);
	}
	(close(p->in), close(p->out));
}

void exec(char **argv, char **env, t_pipe *p)
{
	int pipefd[2];

	p->a = 2;
	p->in = dup(0);
	while (argv[p->a])
	{
		p->out = dup(1);
		if (argv[p->a + 2])
		{
			pipe(pipefd);
			close(p->out);
			p->out = pipefd[1];
		}
		create_command(argv, env, p);
		p->in = pipefd[0];
		p->a++;
	}
	p->a = 1;
	while (argv[p->a])
	{	
		wait(NULL);
		p->a++;
	}
}
