/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 23:20:04 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/30 22:55:29 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	close_everything(t_pipe *get)
{
	if (get->infile != -1)
		close(get->infile);
	if (get->outfile != -1)
		close(get->outfile);
	if (get->pipefd[0] != -1)
		close(get->pipefd[0]);
	if (get->pipefd[1] != -1)
		close(get->pipefd[1]);
}
