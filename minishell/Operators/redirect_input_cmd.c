/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:50:02 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 20:25:20 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui lit l'entrée,
// Gestion des différentes erreurs possiblement rencontré.
// Libération de la mémoire quand nécéssaire.
static int	add_n_print(char **entries, char *input, t_token *tokens, int *t)
{
	if ((*t) == 0)
		entries[(*t)++] = ft_strdup(tokens->input);
	input = readline("heredoc> ");
	if (input && input[0] == '\0')
	{
		entries[(*t)] = ft_strdup("");
		return (1);
	}
	if (input == NULL)
		return (-42);
	if (ft_strncmp(input, tokens->arg_operator,
			ft_strlen(tokens->arg_operator)) == 0
		&& input[ft_strlen(tokens->arg_operator)] == '\0')
	{
		free(input);
		entries[(*t)] = NULL;
		return (0);
	}
	entries[(*t)] = ft_strdup(input);
	if (input)
		free(input);
	return (1);
}

// Boucle "infini",
static int	while_one(char **entries, char *input, t_token *tokens)
{
	int	check_error;
	int	t;

	t = 0;
	while (1)
	{
		check_error = add_n_print(entries, input, tokens, &t);
		if (check_error == -42)
			return (-42);
		if (check_error == 0)
			break ;
		t++;
	}
	return (1);
}

static void	writing_heredoc(char **entries)
{
	int	t;

	t = 1;
	while (entries[t])
	{
		if (!entries[t])
			break ;
		write(STDOUT_FILENO, entries[t], ft_strlen(entries[t]));
		write(STDOUT_FILENO, "\n", 1);
		t++;
	}
}

// (<<)
// Fonction qui retourne le tableau contenant toute les entrées users.
int	redirect_input_command(t_token *tokens, t_export *alloctrack)
{
	char	*input;
	char	**entries;
	int		value;

	dup2(alloctrack->std[1], STDOUT_FILENO);
	input = NULL;
	entries = malloc(200 * sizeof(char *));
	value = while_one(entries, input, tokens);
	if (value == -42)
		return (value);
	if (value == -1)
		return (0);
	redirect_output(alloctrack->heredoc);
	writing_heredoc(entries);
	dup2(alloctrack->std[1], STDOUT_FILENO);
	free_tab(entries);
	return (1);
}
