/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:13:28 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/13 21:16:50 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    Adding comprehensive error handling.

    Managing file descriptors carefully (closing all unused FD).

    Handling edge cases gracefully (nonexistent files, invalid command names, empty files).

	Here is a list of common edge cases you should protect against in the mandatory part of 42’s pipex project based on the project requirements, common pitfalls, and good practices:


    Input/Output file existence and access

        Input file (file1) does not exist or cannot be opened for reading.

        Output file (file2) cannot be created or opened for writing (permission denied, disk error).

        Output file already exists (should be truncated; verify truncation behavior).

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
			close(p->pipefd[1]);
			exit(1);
		}
		dup2(fd1, 0);
		dup2(p->pipefd[1], 1);
		close(fd1);
		close(p->pipefd[0]);
		close(p->pipefd[1]);
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
		dup2(p->pipefd[0], 0);
		dup2(fd2, 1);
		close(fd2);
		close(p->pipefd[0]);
		close(p->pipefd[1]);
		cmd2 = ft_split(argv[3], ' ');
		path = find_absolute_path(find_path(env, "PATH", 4), cmd2[0]);
		execve(path, cmd2, env);
	}
}

int main(int argc, char **argv, char **env)
{
	static t_pipe  p;

    if (argc != 5)
    {
    	write(2, "Error. Invalid number of arguments", 34);
    	exit(1);
    }
	pipe(p.pipefd);
	first_children(argv, env, &p);
	second_children(argv, env, &p);
	close(p.pipefd[0]);
	close(p.pipefd[1]);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	return (0);
}
*/


 	// printf("in: %i out: %i\n", p.pipefd[0], p.pipefd[1]);
	// write (p.pipefd[1], "OLA EZEQUIEL\n", 13);
	// close(p.pipefd[1]);
	// static char buff[20];
	// read(p.pipefd[0], buff, 15);
	// close(p.pipefd[0]);
	// printf("%s", buff);