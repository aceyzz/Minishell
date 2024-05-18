/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_first_inits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:38:24 by cedmulle          #+#    #+#             */
/*   Updated: 2024/04/24 12:56:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char **ss)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (ss)
	{
		if (ss[0])
		{
			tmp1 = ft_strdup(ss[0]);
			tmp1 = erase_quote(tmp1);
		}
		if (ss[1])
		{
			tmp2 = ft_strdup(ss[1]);
			tmp2 = erase_quote(tmp2);
		}
		if (tmp1 && tmp2)
		{
			if (ft_strncmp(tmp1, "echo", 4) == 0 && tmp1[4] == '\0'
				&& ft_strncmp(tmp2, "-n", 2) == 0 && tmp2[2] == '\0')
				return (1);
		}
	}
	return (0);
}

char	**is_echo_n(char **ss)
{
	char	**new_ss;
	char	*echo_n;
	int		i;
	int		t;

	if (!is_n(ss))
		return (ss);
	echo_n = "echo -n";
	new_ss = malloc(tablen(ss) * sizeof(char *));
	if (!new_ss)
		return (NULL);
	new_ss[0] = ft_strdup(echo_n);
	i = 1;
	t = 2;
	while (ss[t])
	{
		new_ss[i++] = ft_strdup(ss[t]);
		t++;
	}
	new_ss[i] = NULL;
	free_tab(ss);
	return (new_ss);
}

void	skip_quotes_fp(char *input, int *i)
{
	while (input[(*i)])
	{
		if (input[(*i)] == 39)
		{
			(*i)++;
			while (input[(*i)] != 39)
				(*i)++;
			(*i)++;
		}
		if (input[(*i)] == '"')
		{
			(*i)++;
			while (input[(*i)] != '"')
				(*i)++;
			(*i)++;
		}
		if (input[(*i)] != 39 && input[(*i)] != '"')
			break ;
	}
}

void	handle_space_or_null(char **tmp, int *i, char ***ss, int *t)
{
	if ((*tmp)[*i] == ' ' || (*tmp)[*i] == '\0')
	{
		(*ss)[(*t)++] = ft_substr(*tmp, 0, *i);
		*tmp = *tmp + *i;
		*i = 0;
	}
}

char	**init_ss(char *input, char **ss)
{
	char	*tmp;
	char	*to_free;
	int		i;
	int		t;

	tmp = ft_strdup(input);
	to_free = tmp;
	i = 0;
	t = 0;
	while (tmp[i])
	{
		while (tmp[i] == ' ' && tmp[i])
			i++;
		if (tmp[i] == 39 || tmp[i] == '"')
			skip_quotes_fp(tmp, &i);
		notspace_notnull(tmp, &i);
		handle_space_or_null(&tmp, &i, &ss, &t);
	}
	ss[t] = NULL;
	free(to_free);
	return (ss);
}
