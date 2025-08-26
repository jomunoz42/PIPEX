/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/25 23:24:21 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	static t_pipe	get;

	if (argc < 5)
	{
		write(2, "Error. Invalid number of arguments\n", 35);
		exit(1);
	}
	get.index = 2;
	get.in = -1;
	get.out = -1;
	get.last_arg = argc - 1;
	create_pipe(argv, env, &get);
	return (0);
}
