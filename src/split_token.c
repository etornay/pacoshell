/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:01:04 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/15 15:18:54 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini_split(char **s, int j)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (i < j)
		{
			if (s[i])
				free(s[i]);
			i++;
		}
		free(s);
	}
}

static int	word_len(char *s, char d)
{
	size_t	len;
	int		fq_simple;
	int		fq_double;

	len = 0;
	fq_simple = 0;
	fq_double = 0;
	while ((s[len] != d || (fq_double || fq_simple)) && s[len] != '\0')
	{
		if (s[len] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[len] == '\"' && !fq_simple)
			fq_double = !fq_double;
		len++;
	}
	return (len);
}

static char	**split_loop(char *s, char limit, char **str)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == limit && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		len = word_len(s, limit);
		str[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!str[i])
		{
			free_mini_split(str, i);
			return (NULL);
		}
		ft_strlcpy(str[i], s, len + 1);
		s += len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

static int	count_words(char *s, char d)
{
	size_t	count;
	int		fq_simple;
	int		fq_double;

	count = 0;
	fq_simple = 0;
	fq_double = 0;
	while (*s != '\0')
	{
		while (*s == d && *s != '\0')
			s++;
		if (*s != '\0')
			count++;
		while ((*s != d || (*s == d && (fq_double || fq_simple))) && *s != '\0')
		{
			if (*s == '\'' && !fq_double)
				fq_simple = !fq_simple;
			else if (*s == '\"' && !fq_simple)
				fq_double = !fq_double;
			s++;
		}
	}
	return (count);
}

char	**split_line(char **s, char limit, t_paco *p)
{
	char	**str;

	if (!s)
		return (NULL);
	p->i = 0;
	str = malloc((count_words(s, limit) + 1) * sizeof(char **));
	if (!str)
		return (NULL);
	str = split_loop(s, limit, str);
	if (!str)
	{
		free_mini_split(str, count_words(s, limit));
		return (NULL);
	}
	return (str);
}
