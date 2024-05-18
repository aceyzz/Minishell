/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:04:31 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 00:25:59 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	conv_d(char **am, t_export *alloctrack)
{
	char	*dollars;
	char	*tmp;
	char	*f;
	int		i;

	i = 0;
	while ((*am)[i] != ' ' && (*am)[i] != 39 && (*am)[i] != '"'
		&& (*am)[i] != '*' && (*am)[i] != '?' && (*am)[i] != '/'
		&& (*am)[i] != '\0')
		i++;
	if ((*am)[i] == '?')
		i++;
	dollars = ft_substr((*am), 0, i);
	dollars = choose_convert(dollars, alloctrack);
	tmp = ft_substr((*am), i, ft_strlen((*am)));
	f = (*am);
	(*am) = ft_strjoin(dollars, tmp);
	free(dollars);
	if (f != NULL)
		free(f);
	if (tmp != NULL)
		free(tmp);
}

// Fonction qui convertit les argument divisé qui comprenne un '$'
// Puis reconcatène s'il y avait quelque chose après la valeur demandé.
static char	*convert_dollars(char *arg_m, t_export *alloctrack)
{
	char	*am;

	am = ft_strdup(arg_m);
	free(arg_m);
	if (!am)
		return (NULL);
	if (am[0] == '$' && am[1] != '\0')
		conv_d(&am, alloctrack);
	return (am);
}

// Fonction qui concatène toutes les chaines d'un char** en une seule chaine
// Cela nous sert a retrouvé l'arg comme il etait de base avec les $ convertit.
static char	*concat(char **arg_more)
{
	int		t;
	int		i;
	int		j;
	int		total_len;
	char	*cc;

	total_len = tab_slen(arg_more) + 1;
	cc = malloc(total_len * sizeof(char));
	if (!cc)
		return (error_null(1));
	t = 0;
	i = 0;
	while (arg_more[t])
	{
		j = 0;
		while (arg_more[t][j])
			cc[i++] = arg_more[t][j++];
		t++;
	}
	cc[i] = '\0';
	return (cc);
}

// Fonction qui ecrase la chaine demandé dans le cas ou $ aurait renvoyé null
// Cela se produit lorsque la variable rechercher n'est pas trouvé.
static char	**erase_convert(char **arg_more, int *t)
{
	int	mem;

	mem = (*t);
	while (arg_more[(*t)])
	{
		free(arg_more[(*t)]);
		arg_more[(*t)] = arg_more[(*t) + 1];
		(*t)++;
	}
	(*t) = mem - 1;
	return (arg_more);
}

// Fonction qui convertit tous les $ par leur valeur et concat ttes les chaines
// ..pour retrouver notre argument de base convertit
char	*convert_n_concat(char **arg_more, t_export *alloctrack)
{
	int		t;
	char	*cc;

	t = 0;
	while (arg_more[t])
	{
		arg_more[t] = convert_dollars(arg_more[t], alloctrack);
		if (!arg_more[t])
			arg_more = erase_convert(arg_more, &t);
		t++;
	}
	if (!arg_more)
		return (NULL);
	if (!arg_more[0])
	{
		free(arg_more);
		return (NULL);
	}
	cc = concat(arg_more);
	free_tab(arg_more);
	return (cc);
}
