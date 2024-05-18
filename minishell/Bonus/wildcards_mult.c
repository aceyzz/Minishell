/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:27:02 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 15:28:44 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**which_start_filter(char *input)
{
	int		i;
	int		j;
	int		k;
	char	**filter_mult;

	i = 0;
	j = 0;
	while (input[i] != '*')
		i++;
	k = ft_strlen(input) - 1;
	while (input[k] != '*')
	{
		k--;
		j++;
	}
	if (i > 0 && j == 0)
		filter_mult = filter_b(input);
	if (i == 0 && j > 0)
		filter_mult = filter_a(input);
	if (i == 0 && j == 0)
		filter_mult = all_files();
	if (i > 0 && j > 0)
		filter_mult = filter_ab(input);
	return (filter_mult);
}

static char	**crushed(char **filter_mult, int i)
{
	char	*tmp;

	tmp = filter_mult[i];
	while (filter_mult[i])
	{
		filter_mult[i] = filter_mult[i + 1];
		i++;
	}
	free(tmp);
	return (filter_mult);
}

static void	check_similute(char **search, char **tmp, int j, int *not)
{
	if (search_occurence((*tmp), search[j]) == 1)
		(*not)++;
	if (search_occurence((*tmp), search[j]) == 0)
	{
		(*tmp) = ft_strstr((*tmp), search[j]);
		(*tmp) = (*tmp) + ft_strlen(search[j]);
	}
}

static char	**filtering_mult(char **filter_mult, char **search,
				int skip_a, int skip_b)
{
	int		i;
	int		j;
	int		not;
	char	*tmp;
	char	*buf;

	i = 0;
	while (filter_mult && filter_mult[i])
	{
		j = -1;
		not = 0;
		tmp = ft_strdup(filter_mult[i] + skip_b);
		buf = tmp;
		tmp[ft_strlen(tmp) - skip_a] = '\0';
		while (search && search[++j])
			check_similute(search, &tmp, j, &not);
		if (not > 0)
			filter_mult = crushed(filter_mult, i);
		else
			i++;
		free(buf);
	}
	free_tab(search);
	return (filter_mult);
}

char	**filter_more(char *input)
{
	char	**filter_mult;
	char	**search;
	char	*tmp;
	int		skip_a;
	int		skip_b;

	skip_a = skip_quote_a(input);
	skip_b = skip_quote_b(input) - quote_count_b(input);
	filter_mult = which_start_filter(input);
	tmp = ft_strdup(input + (skip_b + quote_count_b(input)));
	tmp[ft_strlen(tmp) - (skip_a + quote_count_a(input))] = '\0';
	tmp = erase_quote(tmp);
	search = init_search(tmp);
	free(tmp);
	filter_mult = filtering_mult(filter_mult, search, skip_a, skip_b);
	return (filter_mult);
}
