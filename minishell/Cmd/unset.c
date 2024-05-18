/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:26:44 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 13:19:30 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_var(t_export *alloctrack, int *i)
{
	int	j;

	j = (*i);
	free(alloctrack->environ[j]);
	while (alloctrack->environ[j])
	{
		alloctrack->environ[j] = alloctrack->environ[j + 1];
		j++;
	}
	(*i) -= 1;
}

int	ft_unset(char *var_name, t_export *alloctrack)
{
	int	i;

	if (!alloctrack->environ[0])
	{
		printf("mnsh : unset : non-existent environment table\n");
		return (0);
	}
	i = 0;
	while (var_name[i] != '=' && var_name[i])
		i++;
	if (var_name[i] == '=')
	{
		printf("mnsh : unset: %s: invalid parameter name\n", var_name);
		return (0);
	}
	i = 0;
	while (alloctrack->environ[i])
	{
		if (ft_strncmp(alloctrack->environ[i], var_name, ft_strlen(var_name)) \
			== 0 && alloctrack->environ[i][ft_strlen(var_name)] == '=')
			delete_var(alloctrack, &i);
		i++;
	}
	return (1);
}
