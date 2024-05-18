/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:20:36 by cedmulle          #+#    #+#             */
/*   Updated: 2024/04/22 01:02:32 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sucessive_redirs(t_token **head, char **tab, int *index,
		t_token **current_token)
{
	while (tab[*index] && (ft_strcmp(tab[*index], ">") == 0
			|| ft_strcmp(tab[*index], ">>") == 0 || ft_strcmp(tab[*index],
				"<<") == 0 || ft_strcmp(tab[*index], "<") == 0))
	{
		add_token_to_list(head, *current_token);
		*current_token = init_token();
		(*current_token)->cmd = ft_strdup((*head)->cmd);
		copy_arguments(*current_token, *head);
		(*current_token)->operator = ft_strdup(tab[*index]);
		(*index)++;
		if (tab[*index] && (ft_strcmp(tab[*index], ">") != 0
				&& ft_strcmp(tab[*index], ">>") != 0
				&& ft_strcmp(tab[*index], "<<") != 0
				&& ft_strcmp(tab[*index], "<") != 0))
		{
			(*current_token)->arg_operator = ft_strdup(tab[*index]);
			(*index)++;
		}
	}
}

void	handle_redirs_n_args(t_token **head, char **tab, int *index,
		t_token *current_token)
{
	int	arg_count;

	arg_count = 0;
	current_token->operator = ft_strdup(tab[*index]);
	(*index)++;
	if (tab[*index] && (ft_strcmp(tab[*index], ">") != 0
			&& ft_strcmp(tab[*index], ">>") != 0 && ft_strcmp(tab[*index],
				"<<") != 0 && ft_strcmp(tab[*index], "<") != 0))
	{
		current_token->arg_operator = ft_strdup(tab[*index]);
		(*index)++;
	}
	handle_sucessive_redirs(head, tab, index, &current_token);
	while (tab[*index] && ft_strcmp(tab[*index], "|") != 0)
	{
		while (current_token->argument && current_token->argument[arg_count])
			arg_count++;
		current_token->argument = ft_realloc_lib(current_token->argument,
				sizeof(char *) * (arg_count + 2));
		current_token->argument[arg_count] = ft_strdup(tab[*index]);
		current_token->argument[arg_count + 1] = NULL;
		(*index)++;
	}
	add_token_to_list(head, current_token);
}

void	handle_args_n_cmd(t_token *token, char **tab, int *index)
{
	if (tab[*index] && (ft_strcmp(tab[*index], "|") != 0))
	{
		token->arg_operator = ft_strdup(tab[*index]);
		(*index)++;
	}
	if (tab[*index] && (ft_strcmp(tab[*index], "|") != 0))
	{
		token->cmd = ft_strdup(tab[*index]);
		(*index)++;
	}
}

void	handle_special_case(t_token **head, char **tab, int *index)
{
	t_token	*token;
	int		count;

	token = init_token();
	token->operator = ft_strdup(tab[*index]);
	(*index)++;
	handle_args_n_cmd(token, tab, index);
	token->argument = malloc(sizeof(char *));
	token->argument[0] = NULL;
	count = 0;
	while (tab[*index] && ft_strcmp(tab[*index], "|") != 0)
	{
		token->argument = ft_realloc_lib(token->argument, sizeof(char *)
				* (count + 2));
		token->argument[count] = ft_strdup(tab[*index]);
		token->argument[count + 1] = NULL;
		count++;
		(*index)++;
	}
	add_token_to_list(head, token);
}

void	handle_initials_sucessive_redirs(t_token **head, char **tab,
		int *index)
{
	t_token	*new_token;

	while (tab[*index] && (ft_strcmp(tab[*index], ">") == 0
			|| ft_strcmp(tab[*index], ">>") == 0 || ft_strcmp(tab[*index],
				"<<") == 0 || ft_strcmp(tab[*index], "<") == 0))
	{
		new_token = init_token();
		new_token->operator = ft_strdup(tab[*index]);
		(*index)++;
		if (tab[*index] && (ft_strcmp(tab[*index], ">") != 0
				&& ft_strcmp(tab[*index], ">>") != 0
				&& ft_strcmp(tab[*index], "<<") != 0
				&& ft_strcmp(tab[*index], "<") != 0) && ft_strcmp(tab[*index],
				"|") != 0)
		{
			new_token->arg_operator = ft_strdup(tab[*index]);
			(*index)++;
		}
		add_token_to_list(head, new_token);
	}
}
