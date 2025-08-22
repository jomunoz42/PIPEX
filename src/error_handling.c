/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:09:12 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/22 22:54:51 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_infile_error(char **argv, t_pipe *get)
{
	write(2, "bash: ", 6);
    perror(argv[1]);
    get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (get->out != -1) // ver situacao de here doc ou nao
        close(get->out);
    exit(1);
}

void handle_outfile_error(char **argv, t_pipe *get)
{
	write(2, "bash: ", 6);
    perror(argv[get->last_arg]);
	if (get->out != -1)
        close(get->out);
	exit(1);
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (!path)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		free_double_ptr(cmd);
		exit(127);
	}
}

void    handle_no_env(char **argv, char **env)
{
    if (env == NULL)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		{
			write(2, argv[3], ft_strlen(argv[3]));
			write(2, ": command not found\n", 20);
		}
		else
		{
			write(2, argv[2], ft_strlen(argv[2]));
			write(2, ": command not found\n", 20);
		}
	}
}
