/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:58:56 by cedmulle          #+#    #+#             */
/*   Updated: 2024/04/21 11:31:44 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quotes(char *input)
{
	int		i;
	int		quote;
	int		dquote;

	i = -1;
	quote = 0;
	dquote = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
	}
	return (!(quote == 1 || dquote == 1));
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->input = NULL;
	token->argument = NULL;
	token->cmd = NULL;
	token->operator = NULL;
	token->arg_operator = NULL;
	token->pipe = 0;
	token->quotes = 0;
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	copy_arguments(t_token *dest, t_token *src)
{
	int	arg_count;
	int	i;

	arg_count = 0;
	while (src->argument && src->argument[arg_count])
		arg_count++;
	dest->argument = malloc(sizeof(char *) * (arg_count + 1));
	i = 0;
	while (i < arg_count)
	{
		dest->argument[i] = ft_strdup(src->argument[i]);
		i++;
	}
	dest->argument[arg_count] = NULL;
}

void	init_prev(t_token **token)
{
	t_token	*current;
	t_token	*prev;

	current = *token;
	prev = NULL;
	while (current)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}
