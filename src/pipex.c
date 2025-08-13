/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/13 21:18:12 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	static t_pipe  p;

    if (argc < 5)
    {
    	write(2, "Error. Invalid number of arguments", 34);
    	exit(1);
    }
	p.count = 1;
	p.cmds = argc - 3;
	p.processes = malloc(sizeof(pid_t) * p.cmds);
	if (!p.processes)
	{
		write(2, "Error. Allocation of processes failed", 37);
    	exit(1);
	}
	create_children(argv, env, &p);
	return (0);
}

//     Freeing all allocated memory.

//     Execute with absolute path.

//     Handle no environment case
