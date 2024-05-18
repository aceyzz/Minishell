/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:00:23 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:35:23 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dquote(char **tmp, int *i)
{
	int	j;

	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	while ((*tmp)[(*i)] != '"')
		(*i)++;
	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	(*i) -= 1;
}

static void	squote(char **tmp, int *i)
{
	int	j;

	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	while ((*tmp)[(*i)] != 39)
		(*i)++;
	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	(*i) -= 1;
}

char	*erase_quote_b(char *input)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(input);
	i = 0;
	while (tmp[i] != '*')
	{
		if (tmp[i] == '"')
			dquote(&tmp, &i);
		if (tmp[i] == 39)
			squote(&tmp, &i);
		i++;
	}
	return (tmp);
}

int	skip_quote_b(char *input)
{
	int	skip_b;

	skip_b = 0;
	while (input[skip_b] != '*' && input[skip_b])
	{
		if (input[skip_b] == 39)
		{
			skip_b++;
			while (input[skip_b] != 39)
				skip_b++;
		}
		if (input[skip_b] == '"')
		{
			skip_b++;
			while (input[skip_b] != '"')
				skip_b++;
		}
		skip_b++;
	}
	return (skip_b);
}
