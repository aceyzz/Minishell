/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:53:30 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 13:01:19 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui gère l'erreur en cas de pipe en début de cmd
static int	first_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		printf("mnsh : parse error near '|'\n");
		free(input);
		return (0);
	}
	return (1);
}

char	*check_pipe(char *input)
{
	int	i;

	if (!input)
		return (NULL);
	if (!first_pipe(input))
		return (NULL);
	i = ft_strlen(input) - 1;
	while (input[i] == ' ')
		i--;
	if (input[i] == '|')
	{
		printf("mnsh : syntax error near unexpected token `|' \n");
		free(input);
		return (NULL);
	}
	return (input);
}
