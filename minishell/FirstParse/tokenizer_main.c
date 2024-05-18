/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:30:20 by cedmulle          #+#    #+#             */
/*   Updated: 2024/05/17 20:33:24 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_command_line(t_token **head, char **tab, int *index)
{
	t_token	*token;
	int		count;

	token = init_token();
	token->cmd = ft_strdup(tab[*index]);
	token->argument = malloc(sizeof(char *));
	token->argument[0] = NULL;
	count = 0;
	(*index)++;
	while (tab[*index] && ft_strcmp(tab[*index], "|") != 0)
	{
		if (!ft_strcmp(tab[*index], ">") || !ft_strcmp(tab[*index], ">>")
			|| !ft_strcmp(tab[*index], "<<") || !ft_strcmp(tab[*index], "<"))
			return (handle_redirs_n_args(head, tab, index, token));
		else
		{
			token->argument = ft_realloc_lib(token->argument, sizeof(char *)
					* (count + 2));
			token->argument[count] = ft_strdup(tab[*index]);
			token->argument[count + 1] = NULL;
			count++;
			(*index)++;
		}
	}
	add_token_to_list(head, token);
}

void	handle_loop_content(t_token ***tokens, char **tab, int *i)
{
	t_token	*token;

	if (ft_strcmp(tab[*i], "|") == 0)
	{
		token = init_token();
		token->pipe = 1;
		add_token_to_list(*tokens, token);
		(*i)++;
	}
	else if ((!ft_strcmp(tab[*i], "<") || !ft_strcmp(tab[*i], "<<")
			|| !ft_strcmp(tab[*i], ">>") || !ft_strcmp(tab[*i], ">")))
	{
		handle_special_case(*tokens, tab, i);
		if (tab[*i] && !ft_strcmp(tab[*i], "|"))
		{
			token = init_token();
			token->pipe = 1;
			add_token_to_list(*tokens, token);
			(*i)++;
		}
	}
	else
		parse_command_line(*tokens, tab, i);
}

void	fill_list_from_tab(t_token **tokens, char **tab)
{
	int	i;

	i = 0;
	if ((i == 0 && (ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i],
					">>") == 0)) && (tab[i + 1] && (ft_strcmp(tab[i + 1],
					">") != 0 && ft_strcmp(tab[i + 1], ">>") != 0)))
		handle_initials_sucessive_redirs(tokens, tab, &i);
	while (tab[i])
		handle_loop_content(&tokens, tab, &i);
}

t_token	*tokenizer(char **raw_tab_tokens)
{
	t_token	*tokens;

	tokens = NULL;
	fill_list_from_tab(&tokens, raw_tab_tokens);
	return (tokens);
}
