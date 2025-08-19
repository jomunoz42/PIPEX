/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:53:18 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/19 21:09:35 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_double_ptr(char **split)
{
    int a;
    
    a = 0;
    if (!split)
        return ;
    while (split[a])
        free(split[a++]);
    free(split);
}
