/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:09:12 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/24 22:41:57 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_infile_error(char **argv, t_pipe *get)
{
	write(2, "bash: ", 6);
	perror(argv[1]);
	get->out = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (get->out != -1)
		close(get->out);
	exit(1);
}

void	handle_outfile_error(char **argv, t_pipe *get)
{
	write(2, "bash: ", 6);
	perror(argv[get->last_arg]);
	if (get->outfile != -1)
		close(get->out);
	if (get->outfile != -1)
		close(get->in);
	exit(1);
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (ft_strncmp(path, "", 1) == 0)
		write(2, "''", 2);
	else
		write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	if (path && path != cmd[0] && path[0] != '\0')    // UNDERSTAND THIS
        free(path);
    free_double_ptr(cmd);
	exit(127);
}

void	free_double_ptr(char **split)
{
	int	a;

	a = 0;
	if (!split)
		return ;
	while (split[a])
		free(split[a++]);
	free(split);
}
