/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:09:12 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/30 21:41:13 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_infile_error(char **argv)
{
	write(2, "bash: ", 6);
	perror(argv[1]);
}

void	handle_outfile_error(char **argv, t_pipe *get)
{
	write(2, "bash: ", 6);
	perror(argv[get->last_arg]);
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (path && ft_strncmp(path, "", 1) == 0)
		write(2, "''", 2);
	else
		write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	if (path && path != cmd[0] && path[0] != '\0')
		free(path);
	free_double_ptr(cmd);
	exit(127);
}

void	handling_error(char *message, t_pipe *get)
{
	perror(message);
	close_everything(get);
	exit(1);
}
