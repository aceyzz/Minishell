/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:49:43 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:20:30 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_export *alloctrack)
{
	int		i;
	ssize_t	len;
	ssize_t	w;

	if (!alloctrack->environ[0])
	{
		printf("mnsh : No environment variables detected.\n");
		return (0);
	}
	i = 0;
	while (alloctrack->environ[i])
	{
		len = ft_strlen(alloctrack->environ[i]);
		w = write(STDOUT_FILENO, alloctrack->environ[i], len);
		if (w < len)
			return (error_zero(7));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (1);
}
