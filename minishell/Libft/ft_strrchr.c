/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:37:16 by waziz             #+#    #+#             */
/*   Updated: 2024/03/28 10:11:43 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	char	occurence;
	int		i;

	occurence = (char)c;
	i = fts_strlen(str);
	s = (char *)str;
	while (i > 0)
	{
		if (s[i] == occurence)
			return (s + i);
		i--;
	}
	if (s[i] == occurence)
		return (s);
	return (0);
}
