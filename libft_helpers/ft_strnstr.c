/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:06:20 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/11 20:06:39 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[a] != '\0' && a < len)
	{
		b = 0;
		while (big[a + b] == little[b] && (a + b) < len)
		{
			if (little[b + 1] == '\0')
			{
				return ((char *)&big[a]);
			}
			b++;
		}
		a++;
	}
	return (NULL);
}
