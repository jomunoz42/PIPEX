/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:12 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/09 21:22:44 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_count_words(char const *s, char d)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (s[a])
	{
		if ((s[a] != d && (a == 0 || s[a - 1] == d)))
			count++;
		a++;
	}
	return (count);
}

static char	*word_allocate(const char *start, int len)
{
	char	*word;
	int		a;

	a = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (a < len)
	{
		word[a] = start[a];
		a++;
	}
	word[len] = '\0';
	return (word);
}

static void	*free_all(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
	return (NULL);
}

static char	**split_words(char **result, const char *s, char c, size_t i)
{
	const char	*start;
	int			len;

	while (*s != '\0')
	{
		start = s;
		len = 0;
		if (*s != c)
		{
			while (*s != c && *s != '\0')
			{
				len++;
				s++;
			}
			result[i] = word_allocate(start, len);
			if (result[i] == NULL)
				return (free_all(result, i));
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char d)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_count_words(s, d) + 1));
	if (result == NULL)
		return (NULL);
	return (split_words(result, s, d, 0));
}
