/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:25:07 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:33:41 by cedmulle         ###   ########.fr       */
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
		(*i)--;
	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	(*i) += 1;
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
		(*i)--;
	j = (*i);
	while ((*tmp)[j])
	{
		(*tmp)[j] = (*tmp)[j + 1];
		j++;
	}
	(*i) += 1;
}

char	*erase_quote_a(char *input)
{
	int		i;
	char	*tmp;

	i = ft_strlen(input);
	tmp = ft_strdup(input);
	while (tmp[i] != '*')
	{
		if (tmp[i] == 39)
			squote(&tmp, &i);
		if (tmp[i] == '"')
			dquote(&tmp, &i);
		i--;
	}
	return (tmp);
}

static int	init_skip_a(char *input, int i, int quote)
{
	int	skip_a;

	skip_a = 0;
	while (input[i++])
		skip_a++;
	skip_a -= quote;
	return (skip_a);
}

int	skip_quote_a(char *input)
{
	int	i;
	int	quote;
	int	skip_a;

	i = ft_strlen(input) + 1;
	quote = 0;
	while (input[--i] != '*' && i >= 0)
	{
		if (input[i] == 39)
		{
			i--;
			while (input[i] != 39)
				i--;
			quote += 2;
		}
		if (input[i] == '"')
		{
			i--;
			while (input[i] != '"')
				i--;
			quote += 2;
		}
	}
	skip_a = init_skip_a(input, i, quote) - 1;
	return (skip_a);
}
