/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:13:34 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/12 19:35:15 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_path(char **env, char *str, int size)
{
    int a;

    a = -1;
    while (env[++a])
    {
        if (ft_strnstr(env[a], str, size))
            return (env[a] + size);
    }
    return (NULL);
}

char    *find_absolute_path(char *str, char *cmd)
{
    int a;
    char **dirs;
    char *path;

    a = -1;
    dirs = ft_split(str, ':');
    while (dirs[++a])
    {
        path = ft_strjoin(dirs[a], "/");
        path = ft_strjoin(path, cmd);
        if (access(path, X_OK) == 0)
            return (path);
    }
    return (free(path), NULL);
}
