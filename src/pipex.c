/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:33:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/22 23:10:34 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	static	t_pipe	get;
	
    if (argc < 5)
    {
    	write(2, "Error. Invalid number of arguments", 34);
    	exit(1);
    }
	handle_no_env(argv, env); //////
	get.last_arg = argc - 1;
	exec(argv, env, &get);
	return (0);
}

// env -i ./pipex                if (!*env) env = ...

// if file 1 doesn t exist create file2 

//     Freeing all allocated memory.

//     Execute with absolute path.

//     Handle no environment case (comand not found)

//     (comand not found)

//     "" para o grep

//     o caso da empty string, ver se faz sentido o que ele disse

//     ver os casos das permissoes

//     ver o caso do ls caso o file1 nao exista

