/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:13:28 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/24 20:33:47 by jomunoz          ###   ########.fr       */
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
	get->index = 1;
	while (argv[get->index])
	{	
		wait(NULL);
		get->index++;
	} 
} */
