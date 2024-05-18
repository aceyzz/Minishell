/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:12:34 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:23:54 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;
	ssize_t	len;
	ssize_t	w;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (error_zero(9));
	len = ft_strlen(cwd);
	w = write(STDOUT_FILENO, cwd, len);
	if (w < len)
	{
		free(cwd);
		return (error_zero(7));
	}
	write (STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (1);
}
