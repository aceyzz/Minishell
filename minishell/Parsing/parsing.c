/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:26:12 by waziz             #+#    #+#             */
/*   Updated: 2024/04/28 08:50:19 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui vérifie la présence de wildcard à traiter non compris..
// ..entre " et '.
int	check_wildcard(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			return (1);
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
				i++;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
		}
		i++;
	}
	return (0);
}

// Fonction créée car + de 25 lignes
// on free l'ancien tableau argument et ses chaines de caracteres.
// puis nous lui attribuons un nouveau tableau en le faisant pointé dessus.
static char	**final_step_cw(char **new_argument, int *i)
{
	new_argument[(*i)] = NULL;
	return (new_argument);
}

// Fonction qui fais un nouveau tableau en mettant les noms de fichiers désiré
// s'ils sont trouvé dans le tableau argument à l'endroit ou ils doivent être.
static char	**convert_wildcard(char **argument, int *t)
{
	char	**w;
	char	**new_argument;
	int		i;
	int		j;

	w = wildcards(argument[(*t)]);
	if (!w)
		return (NULL);
	new_argument = malloc((tablen(argument) + tablen(w) + 1) * sizeof(char *));
	if (!new_argument)
		return (NULL);
	i = -1;
	while (++i < (*t))
		new_argument[i] = ft_strdup(argument[i]);
	i = (*t);
	j = -1;
	while (w[++j])
		new_argument[i++] = ft_strdup(w[j]);
	free_tab(w);
	j = (*t) + 1;
	(*t) = i - 1;
	while (argument[j])
		new_argument[i++] = ft_strdup(argument[j++]);
	new_argument = final_step_cw(new_argument, &i);
	return (new_argument);
}

// Fonction qui traduis les * si nécéssaire.
// Ou qui écrase les " et les ' s'il n'ya pas de * à traiter.
char	**ft_parsing(char **argument, t_export *alloctrack)
{
	char	**cw;
	int		t;

	argument = replace_argument(argument, alloctrack);
	t = -1;
	while (argument[++t] != NULL)
	{
		if (argument[t] == NULL)
			break ;
		if (check_wildcard(argument[t]))
		{
			cw = convert_wildcard(argument, &t);
			if (!cw)
				return (NULL);
			free_tab(argument);
			argument = cw;
		}
		else
		{
			argument[t] = erase_quote(argument[t]);
			if (!argument[t])
				return (NULL);
		}
	}
	return (argument);
}
