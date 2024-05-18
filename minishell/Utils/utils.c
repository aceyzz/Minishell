/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:02:35 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 13:11:19 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui mesure la taille d'un tableau à deux dimensions.
int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// Fonction qui compte les nombres total de caractères présente dans toutes
// les str du tableau.
int	tab_slen(char **tab)
{
	int	i;
	int	t;
	int	slen;

	t = 0;
	slen = 0;
	if (tab)
	{
		while (tab[t])
		{
			i = 0;
			while (tab[t][i++])
				slen++;
			t++;
		}
	}
	return (slen);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

// Fonction qui renvoi un pointeur à partir de l'occurence chercher dans la str
// Donc si on cherche "on" dans str blablaonblabla,
// il renverra un pointeur sur 'o'
// Pour qu'il ne soit lisible plus que "onblabla"
char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && s1[i + j] != '\0')
		{
			if (s2[j + 1] == '\0')
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

int	search_occurence(char *str1, char *str2)
{
	int	i;
	int	j;
	int	mem;

	i = 0;
	while (str1[i])
	{
		j = 0;
		mem = i;
		while (str1[mem] == str2[j])
		{
			mem++;
			j++;
		}
		if (str2[j] == '\0')
			return (0);
		i++;
	}
	return (1);
}
