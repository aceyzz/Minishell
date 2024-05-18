/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_scnd_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:48:18 by cedmulle          #+#    #+#             */
/*   Updated: 2024/04/22 00:27:10 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_special_cases(t_utils *p, char **current, char **segment_start)
{
	int	length;

	if (*current > *segment_start)
	{
		length = *current - *segment_start;
		add_token(p, *segment_start, length);
	}
	*segment_start = *current;
	if (*(*current + 1) == **current && (**current == '<' || **current == '>'))
		(*current)++;
	length = *current - *segment_start + 1;
	add_token(p, *segment_start, length);
	*segment_start = *current + 1;
}

void	split_string(t_utils *p, char *str)
{
	char	*segment_start;
	char	*current;
	int		length;

	segment_start = str;
	current = str;
	while (*current)
	{
		if (is_special_character(*current) && !is_quoted(str, current - str))
			handle_special_cases(p, &current, &segment_start);
		current++;
	}
	if (current > segment_start)
	{
		length = current - segment_start;
		add_token(p, segment_start, length);
	}
}

char	**split_into_tokens(char **input)
{
	t_utils	p;
	int		i;

	i = -1;
	p.capacity = 10;
	p.size = 0;
	p.tokens = malloc(p.capacity * sizeof(char *));
	while (input[++i] != NULL)
		split_string(&p, input[i]);
	p.tokens[p.size] = NULL;
	return (p.tokens);
}

t_token	*parse_and_tokenize(char *input)
{
	char	**tab;
	char	**tab_tokens;
	t_token	*result;

	if (check_quotes(input) == false)
	{
		ft_putstr_fd("error : quotes not closed\n", 2);
		return (NULL);
	}
	tab = split_space(input);
	if (!tab)
		return (NULL);
	tab_tokens = split_into_tokens(tab);
	free_tab(tab);
	if (!tab_tokens)
		return (NULL);
	result = tokenizer(tab_tokens);
	free_tab(tab_tokens);
	return (result);
}
