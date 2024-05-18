/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:19:12 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 20:24:50 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**final_filter_b(char **filter_b, char *tmp, int skip_b)
{
	char	*f;
	int		i;
	int		t;

	i = 0;
	while (filter_b[i])
	{
		if (ft_strncmp(filter_b[i], tmp, skip_b) == 0)
			i++;
		else
		{
			t = i;
			f = filter_b[i];
			while (filter_b[t])
			{
				filter_b[t] = filter_b[t + 1];
				t++;
			}
			filter_b[t] = NULL;
			free(f);
		}
	}
	return (filter_b);
}

char	**filter_b(char *input)
{
	char	**filter_b;
	char	*tmp;
	int		skip_b;

	filter_b = all_files();
	if (!filter_b)
		return (NULL);
	skip_b = skip_quote_b(input) - quote_count_b(input);
	if (quote_count_b(input) > 0)
		tmp = erase_quote_b(input);
	else
		tmp = ft_strdup(input);
	filter_b = final_filter_b(filter_b, tmp, skip_b);
	free(tmp);
	return (filter_b);
}

static char	**final_filter_a(char **filter_a, char *tmp, int *skip_a)
{
	int		i;
	int		t;
	int		mem;
	char	*f;

	t = -1;
	while (filter_a[++t])
	{
		i = (*skip_a);
		if ((*skip_a) <= (ft_strlen(filter_a[t]) - 1)
			&& ft_strlen(tmp) >= (*skip_a))
		{
			while ((*skip_a) >= 0 && ft_strlen(filter_a[t]) - (*skip_a) >= 0
				&& tmp[ft_strlen(tmp) - (*skip_a)] == filter_a[t] \
				[ft_strlen(filter_a[t]) - (*skip_a)])
				(*skip_a)--;
		}
		if ((*skip_a) > -1 || (*skip_a) > (ft_strlen(filter_a[t]) - 1))
			deleter(filter_a, &f, &mem, &t);
		(*skip_a) = i;
	}
	return (filter_a);
}

char	**filter_a(char *input)
{
	char	**filter_a;
	char	*tmp;
	int		skip_a;

	filter_a = all_files();
	if (!filter_a)
		return (NULL);
	skip_a = skip_quote_a(input);
	if (quote_count_a(input) > 0)
		tmp = erase_quote_a(input);
	else
		tmp = ft_strdup(input);
	filter_a = final_filter_a(filter_a, tmp, &skip_a);
	free(tmp);
	return (filter_a);
}
