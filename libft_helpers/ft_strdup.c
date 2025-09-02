/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:47:36 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/27 22:28:54 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char	*ft_strdup(const char *s)
{
	char	*str;
	int		a;
	int		size;

	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (a < size)
	{
		str[a] = s[a];
		a++;
	}
	str[a] = '\0';
	return (str);
}
/* 
int	main(void)
{
	char	*str1;

	str1 = "Escola 42";
	printf("%s", ft_strdup(str1));
} */
