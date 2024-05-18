/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:27:01 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:23:08 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_realloc(char *v_env, t_export *alloctrack)
{
	char	**new_environ;
	int		i;

	i = tablen(alloctrack->environ) + 2;
	new_environ = malloc(i * sizeof(char *));
	if (!new_environ)
		return (NULL);
	i = 0;
	while (alloctrack->environ[i])
	{
		new_environ[i] = ft_strdup(alloctrack->environ[i]);
		i++;
	}
	new_environ[i++] = ft_strdup(v_env);
	new_environ[i] = NULL;
	free_tab(alloctrack->environ);
	return (new_environ);
}

static void	check_environ(char *v_env, t_export *alloctrack, int *i, int *found)
{
	char	*name;
	int		t;

	name = ft_substr(v_env, 0, (*i));
	t = 0;
	while (alloctrack->environ[t])
	{
		if ((ft_strncmp(alloctrack->environ[t], name, ft_strlen(name)) == 0)
			&& alloctrack->environ[t][ft_strlen(name)] == '=')
		{
			free(alloctrack->environ[t]);
			alloctrack->environ[t] = ft_strdup(v_env);
			(*found) = 1;
		}
		t++;
	}
	free(name);
}

int	ft_export(char *v_env, t_export *alloctrack)
{
	int	i;
	int	found;

	i = 0;
	while (v_env[i] != '=' && v_env[i])
		i++;
	if (v_env[i] == '\0')
		return (0);
	if (i == 0)
	{
		printf("mnsh : %s not found\n", v_env + 1);
		return (0);
	}
	found = 0;
	if (!alloctrack->environ[0])
		alloctrack->environ[0] = ft_strdup(v_env);
	else
	{
		check_environ(v_env, alloctrack, &i, &found);
		if (found == 0)
			alloctrack->environ = ft_realloc(v_env, alloctrack);
	}
	return (1);
}
