/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:08:10 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 20:25:41 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui compte le nombre de '
// et qui renvoi le resultat divisé par 2 car il vont en paire.
// Donc s'il yen à qu'un il renverra 0 car 1 / 2 = 0 en int.
static int	yesquotes(char *arg)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (arg)
	{
		while (arg[i])
		{
			if (arg[i] == 39 || arg[i] == '"')
				quotes++;
			i++;
		}
	}
	return (quotes);
}

// Fonction qui alloue de la mémoire pour le nouveau tableau
// Se nouveau tableau au soit des chaines commencant par un ' et finissant pas
// ..premier ' et pour la chaine NULL de fin.
static char	**alloc_tab(char *arg)
{
	int		i;
	int		quotes;
	char	**arg_more;

	i = -1;
	quotes = yesquotes(arg) + 2;
	arg_more = malloc(quotes * sizeof(char *));
	if (!arg_more)
	{
		perror("mnsh : Allocated memory failed");
		return (NULL);
	}
	i = 0;
	while (i < quotes)
		arg_more[i++] = NULL;
	return (arg_more);
}

// Fonction qui détermine si on prend la chaine en double ou en single quote.
// Sinon l'index est renvoyé juste avant le ' ou le " et s'il yen a pas alors
// jusqu'au caractère nul.
static int	quote_increment(char *tmp)
{
	int	i;

	i = 0;
	if (tmp[i] == 39 || tmp[i] == '"')
		i++;
	if (tmp[0] == 39)
		while (tmp[i] != 39)
			i++;
	else if (tmp[0] == '"')
		while (tmp[i] != '"')
			i++;
	else
	{
		while (tmp[i] != 39 && tmp[i] != '"' && tmp[i] != '\0')
			i++;
	}
	if ((tmp[i] == 39 || tmp[i] == '"') && (tmp[0] == 39 || tmp[0] == '"'))
		i++;
	return (i);
}

// Fonction qui divise la chaine en plusieur si présence de ' ou de ".
// Le tout est stocker dans arg_more.
char	**quote_parse(char *arg)
{
	char	**arg_more;
	char	*tmp;
	char	*origin_tmp;
	int		i;
	int		t;

	arg_more = alloc_tab(arg);
	tmp = ft_strdup(arg);
	origin_tmp = tmp;
	if (!tmp)
		return (NULL);
	i = 0;
	t = 0;
	while (tmp[i])
	{
		i = quote_increment(tmp);
		if (i > 0)
			arg_more[t++] = ft_substr(tmp, 0, i);
		if (tmp[i] == '\0')
			break ;
		tmp = tmp + i;
		i = 0;
	}
	free(origin_tmp);
	return (arg_more);
}
