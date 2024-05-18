/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:50:47 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 11:04:14 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_access(char **way, t_export *alloctrack)
{
	int	t;

	t = 0;
	while (way[t])
	{
		if (access(way[t], X_OK) == 0)
		{
			alloctrack->access = t;
			return (1);
		}
		t++;
	}
	return (0);
}

static char	*take_path(char **env)
{
	char	*tmp;
	char	*result;
	int		t;

	t = 0;
	tmp = NULL;
	while (env[t])
	{
		if (env[t][0] == 'P' && env[t][1] == 'A' && env[t][2] == 'T'
			&& env[t][3] == 'H' && env[t][4] == '=')
			tmp = ft_strdup(env[t]);
		t++;
	}
	if (!tmp)
		return (NULL);
	result = ft_strdup(ft_strchr(tmp, '=') + 1);
	free(tmp);
	return (result);
}

static char	**put_slash(char **way)
{
	char	*tmp;
	int		t;
	int		i;

	t = 0;
	while (way[t])
	{
		i = -1;
		tmp = malloc((ft_strlen(way[t]) + 2) * sizeof(char *));
		if (!tmp)
			return (NULL);
		while (way[t][++i])
			tmp[i] = way[t][i];
		tmp[i++] = '/';
		tmp[i] = '\0';
		if (way[t])
			free(way[t]);
		way[t] = ft_strdup(tmp);
		if (tmp)
			free(tmp);
		t++;
	}
	return (way);
}

char	**init_way_path(t_export *alloctrack)
{
	char	*path;

	path = take_path(alloctrack->environ);
	if (!path)
		return (NULL);
	alloctrack->way = ft_split(path, ':');
	if (!alloctrack->way)
		return (NULL);
	free(path);
	alloctrack->way = put_slash(alloctrack->way);
	return (alloctrack->way);
}
