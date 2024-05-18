/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:38:35 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:30:26 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*last_return(int status)
{
	char	*state;

	state = ft_itoa(status);
	if (!state)
		return (NULL);
	return (state);
}
