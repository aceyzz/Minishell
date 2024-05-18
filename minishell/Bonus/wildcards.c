/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:33:12 by waziz             #+#    #+#             */
/*   Updated: 2024/04/28 08:49:23 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	crushing(char **filter_ab, int *t)
{
	int	mem;

	free(filter_ab[(*t)]);
	mem = (*t);
	while (filter_ab[(*t)])
		filter_ab[(*t)] = filter_ab[(*t) + 1];
	(*t) = mem;
}

char	**filter_ab(char *input)
{
	char	**filter_ab;
	char	**fb;
	int		skip_b;
	int		t;

	skip_b = skip_quote_b(input) - quote_count_b(input);
	fb = filter_b(input);
	filter_ab = filter_a(input);
	t = -1;
	while (filter_ab[++t])
	{
		if (fb && fb[0])
		{
			if (ft_strncmp(fb[0], filter_ab[t], skip_b) == 0)
				t++;
			else
				crushing(filter_ab, &t);
		}
	}
	free_tab(fb);
	return (filter_ab);
}

static char	**filter_simple(char *input)
{
	char	**filter;
	int		i;
	int		j;
	int		k;

	i = skip_quote_b(input);
	k = i + 1;
	while (input[k] == '*')
		k++;
	j = 0;
	while (input[k + j])
		j++;
	if (i > 0 && j == 0)
		filter = filter_b(input);
	if (i == 0 && j > 0)
		filter = filter_a(input);
	if (i == 0 && j == 0)
		filter = all_files();
	if (i > 0 && j > 0)
		filter = filter_ab(input);
	return (filter);
}

static int	init_check(char *input)
{
	int	skip_b;
	int	skip_a;
	int	check;

	skip_b = skip_quote_b(input);
	while (input[skip_b + 1] == '*')
		skip_b++;
	skip_a = skip_quote_a(input) + quote_count_a(input);
	check = (ft_strlen(input) - 1) - (skip_b + skip_a);
	return (check);
}

char	**wildcards(char *input)
{
	char	**filter;
	int		check;

	check = init_check(input);
	if (check > 0)
		filter = filter_more(input);
	else
		filter = filter_simple(input);
	if (!filter[0])
	{
		input = erase_quote(input);
		printf("mnsh : No matches found : %s\n", input);
		return (NULL);
	}
	return (filter);
}
