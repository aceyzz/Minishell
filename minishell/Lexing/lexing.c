/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:47:00 by waziz             #+#    #+#             */
/*   Updated: 2024/04/23 23:47:47 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction maitresse qui gere le déroulement de ce qu'il peut y avoir à exec
// dans une structure.
int	lexing(t_token *tokens, t_export *alloctrack)
{
	int	back;

	back = operators(tokens, alloctrack);
	if (back == 0)
		return (0);
	if (back == -42)
		return (-42);
	if (tokens->argument)
		if (tokens->argument[0] != NULL)
			tokens->argument = ft_parsing(tokens->argument, alloctrack);
	if (exec_system(tokens, alloctrack))
	{
		is_exec(tokens);
		if (!command_not_found(tokens, alloctrack))
			return (0);
		back = cmd(tokens, alloctrack);
		if (back == 0)
			return (0);
		if (back == -42)
			return (-42);
	}
	return (1);
}
