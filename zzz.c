/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:13:28 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/21 21:00:16 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    Adding comprehensive error handling.

    Managing file descriptors carefully (closing all unused FD).

    Handling edge cases gracefully (nonexistent files, invalid command names, empty files).

	
	
	Here is a list of common edge cases you should protect against in the mandatory 
	
part of 42 s pipex project based on the project requirements, common pitfalls, 

and good practices:


    Input/Output file existence and access

        Input file (file1) does not exist or cannot be opened for reading.

        Output file (file2) cannot be created or opened for writing (permission denied, disk error).

    W    Output file already exists (should be truncated; verify truncation behavior).

        Input or output file is a directory or otherwise inaccessible.

    Command validity and execution

        Command executable not found in any of the directories of $PATH.

        Command executable exists but is not accessible or lacks execute permission.

        Command string is empty or malformed.

        Arguments to commands are empty or incorrectly parsed (e.g., splitting command string).

    System call failures

        Failure of pipe() (e.g., reaching the system limit for open file descriptors).

        Failure of fork() (OS resource limits).

        Failure of dup2() or open().

        Failure of execve() due to any reason.

    File descriptor management

        Not closing unused pipe file descriptors in parent and children, causing deadlocks.

        Not closing file descriptors after use leading to resource leaks.

    Waiting for child processes

        Forgetting to call waitpid() to avoid zombie processes.

    Memory management

        Allocated memory (e.g., returned by ft_split, ft_strjoin, find_absolute_path) is properly freed to avoid leaks.

    Command-line argument checks

        Number of arguments is not 5, proper error message handling.

        Invalid or missing command line arguments.

    Handling of empty input files

        Input file is empty, commands should still execute correctly (e.g., output file created but empty).

    Robust parsing

        Commands with multiple arguments, quotes, or special characters handled properly by splitting and passing to execve.

    Signal handling (basic)

        Program should not crash or behave unexpectedly with signals like SIGPIPE when writing to a closed pipe.

    Edge cases on standard behavior

        Matching the shell behavior precisely, such as creating/truncating output file even if input file does not exist.

        Proper exit status propagation from child processes.


                         EZE BONE STRUCTURE HELP

		/* 
int main(int argc, char **argv, char **env)
{
	exec(++argv);
	return (0);
}

void tes(char **cmd, int in, int out)
{
	int pid;
	
	pid = fork();
	if (pid == 0)
	{
		dup2(out, 1);
		close(out);
		dup2(in, 0);
		close(in);
		execve(*cmd, cmd, NULL);
		exit(127);
	}
	ft_printf("%s - in: %i out: %i\n\r", *cmd, in, out);
	close(in);
	close(out);
}

void exec(char **argv)
{
	int	a;
	int in;
	int out;
	int pipefd[2];

	a = 0;
	in = dup(0);
	while (argv[a])
	{
		out = dup(1);
		if (argv[a + 1])
		{
			pipe(pipefd);
			close(out);
			out = pipefd[1];
		}
		char *ag[2];
		ag[0] = argv[a];
		ag[1] = NULL;
		tes(ag, in, out);
		in = pipefd[0];
		a++;
	}
	a = 0;
	while (argv[a])
	{	
		wait(NULL);
		a++;
	}
} */
                                    OLD CODE BACK UP
									
/* int main(int argc, char **argv, char **env)
{
	static t_pipe  p;

    if (argc < 5)
    {
    	write(2, "Error. Invalid number of arguments", 34);
    	exit(1);
    }
	p.cmds = argc - 3;
	p.processes = malloc(sizeof(pid_t) * p.cmds);
	if (!p.processes)
	{
		write(2, "Error. Allocation of processes failed", 37);
    	exit(1);
	}
	create_children(argv, env, &p);
	return (0);
} */


char    *find_path(char **env, char *str, int size)
{
    int a;

    a = -1;
    while (env[++a])
    {
        if (ft_strnstr(env[a], str, size))
            return (env[a] + size);
    }
    return (NULL);
}

char    *find_absolute_path(char *str, char *cmd)
{
    int     a;
    char    **dirs;
    char    *path;

    if (access(str, X_OK) == 0)
            return (str);
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



typedef struct s_pipe
{
    int     a;
    int     cmds;
    int     count;
    pid_t   *processes;
    int     pipe1[2];
    int     pipe2[2];
    int     fd1;
    int     fd2;
}           t_pipe;

static void init_pipes_and_infile(char **argv, t_pipe *p)
{
    p->pipe1[0] = -1;
    p->pipe1[1] = -1;
    p->pipe2[0] = -1;
    p->pipe2[1] = -1;
    p->fd1 = open(argv[1], O_RDONLY);
    if (p->fd1 == -1)
        handle_infile_error(argv, p);
}

static void execute_command(char **argv, char **env, int a)
{
    char 	*path;
    char 	**cmd;

    cmd = ft_split(argv[a], ' ');
	path = find_absolute_path(find_path(env, "PATH=", 5), cmd[0]);
	execve(path, cmd, env);
	(perror("Error on execve:"), exit(1));
}

static void create_pipe(char **argv, t_pipe *p, int a)
{
    if (argv[a + 2])
    {
	    if (a % 2 == 0)
	    	pipe(p->pipe1);
	    else
	    	pipe(p->pipe2);
    }
}

static void wait_all_children(t_pipe *p)
{
    p->count = 0;
	while (p->count < p->cmds)
	{
		waitpid(p->processes[p->count], NULL, 0);
		p->count++;
	}
}

void    create_children(char **argv, char **env, t_pipe *p)
{
	int		a;
	
    init_pipes_and_infile(argv, p);
	a = 2;
    while(argv[a + 1])
	{
        create_pipe(argv, p, a);
    	p->processes[p->count] = fork();
		if (p->processes[p->count] == -1)
			(perror("Error on fork:"), exit (1));
		if (p->processes[p->count] == 0)
		{
			if (a == 2)
				clone_close_1_cmd(p, argv, a);
			if (!argv[a + 2])
				clone_close_last_cmd(p, argv, a);
			if (!(a == 2) && argv[a + 2])
				clone_close_even_or_odd_cmds(p, argv, a);
			execute_command(argv, env, a);
		}
		else
        {
			p->count++;
			if (a == 2)
            {
                close_and_set(&p->pipe1[1]);
                close(p->fd1);
            }
			if (!argv[a + 2])
			{
                close_and_set(&p->pipe1[0]);
		        close_and_set(&p->pipe1[1]);
		        close(p->fd2);
            }
			if (!(a == 2) && argv[a + 2])
			{
                if (a % 2 != 0)
                {
                    close_and_set(&p->pipe1[0]);
                    close_and_set(&p->pipe2[1]);
                }
                if (a % 2 == 0)
                {
                    close_and_set(&p->pipe2[0]);
		            close_and_set(&p->pipe1[1]);
                }
            }
        }
		a++;
	}
    wait_all_children(p);
}

/* 
void close_and_set(int *fd)
{
    if (*fd >= 3)
    {
        close(*fd);
        *fd = -1;
    }
}

void    clone_close_1_cmd(t_pipe *p, char **argv, int a)
{    
	dup2(p->fd1, 0);
	dup2(p->pipe1[1], 1);
	close(p->fd1);
	close(p->pipe1[1]);
}

void    clone_close_last_cmd(t_pipe *p, char **argv, int a)
{
    p->fd2 = open(argv[a], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (a % 2 != 0)
	{
		dup2(p->pipe1[0], 0);
		dup2(p->fd2, 1);
		close(p->pipe1[0]);
		close(p->pipe1[1]);
		close(p->fd2);
	}
	else
	{
		dup2(p->pipe2[0], 0);
		dup2(p->fd2, 1);
		close(p->pipe2[0]);
		close(p->pipe2[1]);
		close(p->fd2);
	}
}

void    clone_close_even_or_odd_cmds(t_pipe *p, char **argv, int a)
{
    if (a % 2 != 0)
	{
		dup2(p->pipe1[0], 0);
		dup2(p->pipe2[1], 1);
		close(p->pipe1[0]);
		close(p->pipe2[1]);
	}
	else
	{
		dup2(p->pipe2[0], 0);
		dup2(p->pipe1[1], 1);
		close(p->pipe2[0]);
		close(p->pipe1[1]);
	}
} */

                                     NO BONUS PROJECT

/* 
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
} */
