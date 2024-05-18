/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:37:19 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:39:35 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count_a(char *input)
{
	int	i;
	int	quote;

	i = ft_strlen(input) - 1;
	quote = 0;
	while (input[i] != '*' && i >= 0)
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
		i--;
	}
	return (quote);
}

int	quote_count_b(char *input)
{
	int	skip_b;
	int	quote;

	skip_b = 0;
	quote = 0;
	while (input[skip_b] != '*' && input[skip_b])
	{
		if (input[skip_b] == 39)
		{
			skip_b++;
			while (input[skip_b] != 39)
				skip_b++;
			quote += 2;
		}
		if (input[skip_b] == '"')
		{
			skip_b++;
			while (input[skip_b] != '"')
				skip_b++;
			quote += 2;
		}
		skip_b++;
	}
	return (quote);
}

void	count_w(char *tmp, int *w)
{
	int	i;

	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '*')
			(*w)++;
	}
}
