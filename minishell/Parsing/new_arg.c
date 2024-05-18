/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:12 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 12:57:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui refait un tableau en divisant les arguments  par $
// Gère aussi le cas pour $?
static char	**make_new_tab(char *arg, char **new, int *m)
{
	int		i;
	char	*tmp;
	char	*origin_tmp;

	free(new[(*m)]);
	tmp = ft_strdup(arg);
	origin_tmp = tmp;
	i = 0;
	while (tmp[i])
	{
		i = 0;
		if (tmp[i] == '$')
			i++;
		while (tmp[i] != '$' && tmp[i] != '?' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '?')
			i++;
		if (i > 0)
			new[(*m)++] = ft_substr(tmp, 0, i);
		if (tmp[i])
			tmp = tmp + i;
	}
	free(origin_tmp);
	return (new);
}

// Fonction qui check la présence de dollars dans une string.
static int	check_sdollars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

// Fonction qui compte le nombre de dollars présent dans chaque str du char**
static int	check_tabdollars(char **arg_more)
{
	int	i;
	int	t;
	int	dollars;

	dollars = 0;
	t = 0;
	while (arg_more[t])
	{
		if (arg_more[t][0] != 39)
		{
			i = 0;
			while (arg_more[t][i])
			{
				if (arg_more[t][i] == '$')
					dollars++;
				i++;
			}
		}
		t++;
	}
	return (dollars);
}

// Fonction qui gere l'allocation de mémoire nécéssaire pour le nouveau tableau
// Free l'ancien tableau et le fait pointer vers le nouveau.
// Conserve les arguments tels qu'ils sont si pas ils commencent par '
static char	**dollars_parse(char **arg_more)
{
	int		t;
	int		m;
	char	**new;

	m = check_tabdollars(arg_more) + tablen(arg_more) + 5;
	new = malloc(m * sizeof(char *));
	if (!new)
		return (NULL);
	t = 0;
	while (t < m)
		new[t++] = NULL;
	t = -1;
	m = 0;
	while (arg_more[++t])
	{
		new[m] = ft_strdup(arg_more[t]);
		if (arg_more[t][0] != 39 && check_sdollars(arg_more[t]))
			new = make_new_tab(arg_more[t], new, &m);
		if (arg_more[t][0] == 39 || (arg_more[t][0] != 39
				&& !check_sdollars(arg_more[t])))
			m++;
	}
	free_tab(arg_more);
	new[m] = NULL;
	return (new);
}

// Fonction maîtresse pour convertir l'arg si nécéssaire..
// ..et de concat les resultat pour retrouver un seul et même argument.
char	**replace_argument(char **argument, t_export *alloctrack)
{
	int		t;
	int		erase;
	char	**arg_more;

	t = 0;
	while (argument[t])
	{
		arg_more = quote_parse(argument[t]);
		if (!arg_more)
			return (NULL);
		arg_more = expand_pid(arg_more);
		arg_more = dollars_parse(arg_more);
		free(argument[t]);
		argument[t] = convert_n_concat(arg_more, alloctrack);
		if (!argument[t])
		{
			t -= 1;
			erase = t;
			while (++t <= tablen(argument))
				argument[t] = argument[t + 1];
			t = erase;
		}
		t++;
	}
	return (argument);
}
