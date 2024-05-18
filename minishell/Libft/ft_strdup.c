/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:27:43 by waziz             #+#    #+#             */
/*   Updated: 2024/03/28 10:10:21 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dynam;
	int		i;

	i = 0;
	dynam = malloc((fts_strlen(str) + 1) * sizeof(char));
	if (dynam)
	{
		while (str[i])
		{
			dynam[i] = (char)str[i];
			i++;
		}
		dynam[i] = '\0';
		return (dynam);
	}
	else
		return (0);
}
