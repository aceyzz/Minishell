/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:07:25 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 21:17:05 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int num, t_export *alloctrack)
{
	if (num == 0)
		exit(EXIT_SUCCESS);
	if (num == -42)
	{
		free_alloctrack(alloctrack);
		printf("\n\033[1;36mExit requested. Goodbye ! 💙 \n\n\033[0m");
		exit(num);
	}
	exit(num);
}
