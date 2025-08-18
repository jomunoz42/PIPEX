/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:09:12 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/18 22:45:50 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_infile_error(char **argv, t_pipe *get)
{
    perror(argv[1]);
    get->outfile = open(argv[get->last_arg], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (get->outfile != -1)
        close(get->outfile);
    exit(1);
}
