/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:28:46 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 12:58:26 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *input)
{
	ssize_t	len;
	ssize_t	w;

	len = ft_strlen(input);
	w = write(STDOUT_FILENO, input, len);
	if (w < len)
		return (error_zero(7));
	return (1);
}

int	echon(char *input)
{
	ssize_t	len;
	ssize_t	w;

	len = ft_strlen(input);
	w = write(STDOUT_FILENO, input, len);
	if (w < len)
		return (error_zero(7));
	return (1);
}
