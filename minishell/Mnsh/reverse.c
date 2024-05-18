/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:16:00 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 13:01:54 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_stdin(t_token *tokens)
{
	char	**without;
	int		t;

	without = file_to_tab_wo();
	if (!without)
		return (0);
	t = -1;
	while (without[++t])
	{
		if (tokens->cmd)
		{
			if (ft_strncmp(tokens->cmd, without[t], ft_strlen(without[t])) == 0
				&& tokens->cmd[ft_strlen(without[t])] == '\0'
				&& !tokens->argument[0])
			{
				free_tab(without);
				return (1);
			}
		}
	}
	free_tab(without);
	return (0);
}

static t_token	*ft_init(t_token *tokens, t_token *new_tokens)
{
	new_tokens->input = NULL;
	if (!tokens->argument)
		new_tokens->argument = NULL;
	else
		new_tokens->argument = ft_tabdup(tokens->argument);
	if (!tokens->cmd)
		new_tokens->cmd = NULL;
	else
		new_tokens->cmd = ft_strdup(tokens->cmd);
	if (!tokens->operator)
		new_tokens->operator = NULL;
	else
		new_tokens->operator = ft_strdup(tokens->operator);
	if (!tokens->arg_operator)
		new_tokens->arg_operator = NULL;
	else
		new_tokens->arg_operator = ft_strdup(tokens->arg_operator);
	if (tokens->pipe == 1)
		new_tokens->pipe = 1;
	else
		new_tokens->pipe = 0;
	new_tokens->prev = NULL;
	new_tokens->next = NULL;
	return (new_tokens);
}

static t_token	*init_reverse(t_token *tokens)
{
	t_token	*new_tokens;

	new_tokens = malloc(sizeof(t_token));
	if (!new_tokens)
		return (NULL);
	new_tokens = ft_init(tokens, new_tokens);
	return (new_tokens);
}

t_token	*new_list(t_token *tokens)
{
	t_token	*header;
	t_token	*new_list;

	header = NULL;
	new_list = NULL;
	if (check_cmd_stdin(tokens) && tokens->next)
	{
		header = tokens;
		while (tokens->next)
			tokens = tokens->next;
		new_list = init_reverse(tokens);
		tokens = tokens->prev;
		if (tokens)
		{
			if (tokens->next)
			{
				free_single_token(tokens->next);
				tokens->next = NULL;
			}
		}
		new_list->next = header;
		return (new_list);
	}
	free(new_list);
	return (tokens);
}
