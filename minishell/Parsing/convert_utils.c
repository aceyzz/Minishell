/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:18:05 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 12:57:19 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui rend soit la valeur du tableau d'environnement soit
// la derniere valeur retourné par la programme.
char	*choose_convert(char *dollars, t_export *alloctrack)
{
	char	*d;

	if (dollars[1] == '?')
		d = last_return(alloctrack->status);
	else
		d = dollars_lex(dollars + 1, alloctrack);
	free(dollars);
	if (d)
		if (d[0] == '\0')
			return (NULL);
	return (d);
}

// Fonction qui cherche une variable dans le tableau d'environnement et..
// ..renvoi un pointeur sur sa valeur si elle est trouvée sinon return NULL.
char	*dollars_lex(char *var_name, t_export *alloctrack)
{
	char	*value;
	char	*tmp;
	int		found;
	int		t;

	t = 0;
	found = 0;
	while (alloctrack->environ[t])
	{
		if (ft_strncmp(var_name, alloctrack->environ[t],
				ft_strlen(var_name)) == 0
			&& alloctrack->environ[t][ft_strlen(var_name)] == '=')
		{
			value = ft_strdup(ft_strchr(alloctrack->environ[t], '='));
			found = 1;
		}
		t++;
	}
	if (found == 0)
		return (NULL);
	tmp = ft_strdup(value + 1);
	free(value);
	return (tmp);
}

static int	is_valid(char *dst, char *src)
{
	if (!dst)
	{
		if (!src)
			return (0);
		if (src[0] == '\0')
			return (0);
		return (1);
	}
	else if (!src)
	{
		if (dst[0] == '\0')
			return (0);
		return (1);
	}
	else
		return (1);
}

// Fonction qui concatène src à la fin de dst.
char	*ft_strcat(char *dst, char *src)
{
	int		i;
	int		j;
	char	*cat;

	if (!is_valid(dst, src))
		return (NULL);
	if (!dst)
		return (ft_strdup(src));
	if (!src)
		return (ft_strdup(dst));
	i = ft_strlen(dst) + ft_strlen(src) + 1;
	cat = malloc(i * sizeof(char));
	if (!cat)
		return (error_null(1));
	i = 0;
	while (dst[i])
	{
		cat[i] = dst[i];
		i++;
	}
	j = 0;
	while (src[j])
		cat[i++] = src[j++];
	cat[i] = '\0';
	return (cat);
}
