/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_first_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:36:54 by cedmulle          #+#    #+#             */
/*   Updated: 2024/04/24 12:57:08 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_space(char **ss)
{
	char	*tmp;
	int		i;
	int		t;

	t = 0;
	while (ss[t])
	{
		tmp = ft_strdup(ss[t]);
		i = 0;
		while (tmp[i] == ' ')
			i++;
		free(ss[t]);
		ss[t] = ft_substr(tmp, i, ft_strlen(tmp));
		free(tmp);
		t++;
	}
	return (ss);
}

int	no_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 39)
		{
			i++;
			while (input[i] != 39 && input[i])
				i++;
		}
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i])
				i++;
		}
		if (input[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int	count_split_space(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (input[i] == 39 || input[i] == '"')
			skip_quotes_fp(input, &i);
		if (input[i] != ' ' && input[i])
		{
			while (input[i] != ' ' && input[i] != 39 && input[i] != '"'
				&& input[i])
				i++;
		}
		if (input[i] == ' ' || input[i] == '\0')
			count++;
	}
	return (count);
}

void	notspace_notnull(char *input, int *i)
{
	if (input[(*i)] != ' ' && input[(*i)])
	{
		while (input[(*i)] != ' ' && input[(*i)] != 39 && input[(*i)] != '"'
			&& input[(*i)])
			(*i)++;
	}
}

char	**split_space(char *input)
{
	char	**ss;
	int		count;

	count = count_split_space(input) + 1;
	ss = malloc(count * sizeof(char *));
	if (!ss)
		return (NULL);
	ss = init_ss(input, ss);
	if (!ss)
		return (NULL);
	ss = delete_space(ss);
	ss = is_echo_n(ss);
	return (ss);
}
