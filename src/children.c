/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:57:22 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/13 23:23:57 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* 
void    first_children(char **argv, char **env, t_pipe *p)
{
    int fd1;
    char *path;
    char **cmd1;
    
    p->pid1 = fork();
	if (p->pid1 == 0)
	{
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 == -1)
		{
			ft_printf("bash: %s: No such file or directory\n", argv[1]);
			close(p->pipe1[1]);
			exit(1);
		}
		dup2(fd1, 0);
		dup2(p->pipe1[1], 1);
		close(fd1);
		close(p->pipe1[0]);
		close(p->pipe1[1]);
		cmd1 = ft_split(argv[2], ' ');
		path = find_absolute_path(find_path(env, "PATH=", 4), cmd1[0]);
		// if (!path)
		// 	ft_printf("Command %s not found", argv[2]);
		execve(path, cmd1, env);
	}
}

void    second_children(char **argv, char **env, t_pipe *p)
{
    int fd2;
    char *path;
    char **cmd2;
    
    p->pid2 = fork();
	if (p->pid2 == 0)
	{
		fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(p->pipe1[0], 0);
		dup2(fd2, 1);
		close(fd2);
		close(p->pipe1[0]);
		close(p->pipe1[1]);
		cmd2 = ft_split(argv[3], ' ');
		path = find_absolute_path(find_path(env, "PATH=", 4), cmd2[0]);
		execve(path, cmd2, env);
	}
} */

void    create_children(char **argv, char **env, t_pipe *p)
{
	char 	*path;
    char 	**cmd;
	int		a;
	pid_t   pid;
	
	pipe(p->pipe1);
	pipe(p->pipe2);
	a = 2;
    while(argv[a + 1])
	{
    	p->processes[p->count] = fork();
		if (p->processes[p->count] == 0)
		{
			if (a == 2)                   // first command
			{
				p->fd1 = open(argv[1], O_RDONLY);
				dup2(p->fd1, 0);
				dup2(p->pipe1[1], 1);
				close(p->fd1);
				close(p->pipe1[1]);
			}
			if (!argv[a + 2])
			{
				p->fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (a % 2 != 0)          //   last command
				{
					dup2(p->pipe1[0], 0);
					dup2(p->fd2, 1);
					close(p->pipe1[0]);
					close(p->fd2);
				}
				else                     //   last command
				{
					dup2(p->pipe2[0], 0);
					dup2(p->fd2, 1);
					close(p->pipe2[0]);
					close(p->fd2);
				}
			}
			else
			{
				if (a % 2 != 0)           //   comandos impares
				{
					dup2(p->pipe1[0], 0);
					dup2(p->pipe2[1], 1);
					close(p->pipe1[0]);
					close(p->pipe2[1]);
				}
				else                      //   commandos pares
				{
					dup2(p->pipe2[0], 0);
					dup2(p->pipe1[1], 1);
					close(p->pipe2[0]);
					close(p->pipe1[1]);
				}
			}
			cmd = ft_split(argv[a], ' ');
			path = find_absolute_path(find_path(env, "PATH=", 4), cmd[0]);
			execve(path, cmd, env);
			//  aqui fazer error manegement
		}
		else
		{
			if (a - 2 == p->cmds)
			{
				p->count = 1;
				while (p->count <= p->cmds)
				{
					waitpid(p->processes[p->count], NULL, 0);
					p->count++;
				}
				close(p->pipe1[0]);
				close(p->pipe1[1]);
				return ;
			}
			p->count++;
		}
		a++;
	}
}
