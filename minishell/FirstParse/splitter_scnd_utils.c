/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_scnd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:32:38 by waziz             #+#    #+#             */
/*   Updated: 2024/04/21 12:03:59 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_character(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_quoted(char *str, int index)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

void	add_token(t_utils *p, char *start, int length)
{
	char	*token;

	if (p->size >= p->capacity)
	{
		p->capacity *= 2;
		p->tokens = ft_realloc_lib(p->tokens, p->capacity * sizeof(char *));
	}
	token = malloc(length + 1);
	ft_strncpy(token, start, length);
	token[length] = '\0';
	p->tokens[p->size++] = token;
}
