/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:39:16 by waziz             #+#    #+#             */
/*   Updated: 2024/04/21 12:21:02 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui écrase les ' voulu.
static void	erase_squote(char **erase, int *i)
{
	int	mem;

	mem = (*i);
	while ((*erase)[(*i)])
	{
		(*erase)[(*i)] = (*erase)[(*i) + 1];
		(*i)++;
	}
	(*i) = mem;
	while ((*erase)[(*i)] != 39)
		(*i)++;
	mem = (*i);
	while ((*erase)[(*i)])
	{
		(*erase)[(*i)] = (*erase)[(*i) + 1];
		(*i)++;
	}
	(*i) = mem;
}

// Fonction qui écrase les " voulu.
static void	erase_dquote(char **erase, int *i)
{
	int	mem;

	mem = (*i);
	while ((*erase)[(*i)])
	{
		(*erase)[(*i)] = (*erase)[(*i) + 1];
		(*i)++;
	}
	(*i) = mem;
	while ((*erase)[(*i)] != '"')
		(*i)++;
	mem = (*i);
	while ((*erase)[(*i)])
	{
		(*erase)[(*i)] = (*erase)[(*i) + 1];
		(*i)++;
	}
	(*i) = mem;
}

// Fonction qui écrase les " et les ' si nécéssaire.
// on libère la mémoire de l'ancienne
// pour la refaire pointé sur la nouvelle sans créée de fuite de mémoire.
char	*erase_quote(char *s)
{
	char	*erase;
	int		i;

	erase = ft_strdup(s);
	if (!erase)
		return (NULL);
	i = 0;
	while (erase[i])
	{
		if (erase[i] == 39)
			erase_squote(&erase, &i);
		if (erase[i] == '"')
			erase_dquote(&erase, &i);
		i++;
	}
	erase[i] = '\0';
	free(s);
	return (erase);
}
