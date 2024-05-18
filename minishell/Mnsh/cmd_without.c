/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_without.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 01:00:00 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 22:22:41 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_file_without(void)
{
	int		fd;
	int		size;
	char	c[1];

	fd = open("./Libft/.cmd_without", O_RDONLY);
	if (fd == -1)
		return (0);
	size = 0;
	while (read(fd, c, 1))
		size++;
	close(fd);
	return (size);
}

static char	*file_to_str(void)
{
	int		fd;
	char	*str;
	int		i;
	char	c[1];

	fd = open("./Libft/.cmd_without", O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = malloc(sizeof(char) * (size_file_without() + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (read(fd, c, 1))
	{
		str[i] = c[0];
		i++;
	}
	str[i] = '\0';
	close(fd);
	return (str);
}

char	**file_to_tab_wo(void)
{
	char	**tab;
	char	*str;

	str = file_to_str();
	if (!str)
		return (NULL);
	tab = ft_split(str, '\n');
	free(str);
	return (tab);
}
