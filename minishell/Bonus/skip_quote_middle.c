/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:28:39 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:38:03 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**squote(char **parse, char **tmp, int i, int *t)
{
	int	j;

	if ((*t) == 0)
		free(parse[(*t)]);
	j = i;
	if (j > 0)
		parse[(*t)++] = ft_substr((*tmp), 0, j);
	while ((*tmp)[j] != 39)
		j++;
	parse[(*t)++] = ft_substr((*tmp), i, j);
	i++;
	(*tmp) = (*tmp) + i;
	return (parse);
}

static char	**dquote(char **parse, char **tmp, int i, int *t)
{
	int	j;

	if ((*t) == 0)
		free(parse[(*t)]);
	j = i;
	if (j > 0)
		parse[(*t)++] = ft_substr((*tmp), 0, j);
	while ((*tmp)[j] != '"')
		j++;
	parse[(*t)++] = ft_substr((*tmp), i, j + 1);
	i++;
	(*tmp) = (*tmp) + i;
	return (parse);
}

static char	**spliter(char **parse, int i, int j, int *t)
{
	char	**spliter;
	char	**new_parse;

	spliter = ft_split(parse[(*t)], '*');
	j = tablen(spliter) + 1;
	new_parse = malloc((tablen(parse) + j) * sizeof(char *));
	if (!new_parse)
		return (NULL);
	i = -1;
	while (++i < (*t))
		new_parse[i] = ft_strdup(parse[i]);
	i = -1;
	j = (*t);
	while (spliter[++i])
		new_parse[(*t)++] = ft_strdup(spliter[i]);
	new_parse[(*t)] = NULL;
	i = (*t);
	while (parse[j + 1])
		new_parse[(*t)++] = parse[j++];
	new_parse[(*t)] = NULL;
	free_tab(spliter);
	free_tab(parse);
	(*t) = i;
	return (new_parse);
}

static char	**split_wildcard(char **parse)
{
	int	t;
	int	i;
	int	j;

	t = 0;
	j = 0;
	while (parse[t])
	{
		i = 0;
		if (parse[t][0] == 39 || parse[t][0] == '"')
		{
			while (parse[t][i])
			{
				parse[t][i] = parse[t][i + 1];
				i++;
			}
			parse[t][i - 1] = '\0';
			t++;
		}
		else
			parse = spliter(parse, 0, j, &t);
	}
	return (parse);
}

char	**init_search(char *tmp)
{
	int		i;
	int		w;
	int		t;
	char	**parse;

	w = 0;
	t = 0;
	count_w(tmp, &w);
	parse = malloc((w + 2) * sizeof(char *));
	if (!parse)
		return (NULL);
	while (t < (w + 2))
		parse[t++] = NULL;
	t = 0;
	parse[t] = ft_strdup(tmp);
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == 39)
			parse = squote(parse, &tmp, i, &t);
		if (tmp[i] == '"')
			parse = dquote(parse, &tmp, i, &t);
	}
	parse = split_wildcard(parse);
	return (parse);
}
