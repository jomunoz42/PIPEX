/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/29 23:02:16 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_infile_and_outfile(char **argv, t_pipe *get)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		get->infile = handling_here_doc(argv, get);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_APPEND,  0644);
		if (get->outfile == -1)
			handle_outfile_error(argv, get);
	}
	else
	{
		get->infile = open(argv[1], O_RDONLY);
		if (get->infile == -1)
			handle_infile_error(argv);
		get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (get->outfile == -1)
			handle_outfile_error(argv, get);
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_pipe	get;

	if (argc < 5)
	{
		write(2, "Error. Invalid number of arguments\n", 35);
		exit(1);
	}
	get_infile_and_outfile(argv, &get);
	get.in = -1;
	get.out = -1;
	get.index = 2;
	get.last_arg = argc - 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		get.cmd_number = argc - 4;
	else
		get.cmd_number = argc - 3;
	create_pipe(argv, env, &get);
	return (0);
}
