/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:51:21 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 13:00:12 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui libère la mémoire de chaque chaine de caractere d'un char **
// Puis libère la mémoire du tableau.
void	free_tab(char **entries)
{
	int	i;

	if (entries)
	{
		i = 0;
		while (entries[i])
			free(entries[i++]);
		free(entries);
	}
}

// Free la mémoire alloué pour la structue t_export et ses variables
void	free_alloctrack(t_export *alloctrack)
{
	if (alloctrack)
	{
		if (alloctrack->environ)
			free_tab(alloctrack->environ);
		free(alloctrack);
	}
}

void	free_token_list(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free_single_token(tmp);
	}
}

void	free_single_token(t_token *token)
{
	if (token)
	{
		if (token->input)
			free(token->input);
		if (token->argument)
			free_tab(token->argument);
		if (token->cmd)
			if (token->cmd[0])
				free(token->cmd);
		if (token->operator)
			free(token->operator);
		if (token->arg_operator)
			free(token->arg_operator);
		free(token);
	}
}
