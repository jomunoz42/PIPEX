/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:06:47 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/11 20:07:03 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	b = 0;
	while (s2[b])
	{
		str[a + b] = s2[b];
		b++;
	}
	str[a + b] = '\0';
	return (str);
}
