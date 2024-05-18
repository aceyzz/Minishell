/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard_ab_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:24 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:39:53 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deleter(char **filter_a, char **f, int *mem, int *t)
{
	(*mem) = (*t);
	(*f) = filter_a[(*t)];
	(*t) -= 1;
	while (filter_a[++(*t)])
		filter_a[(*t)] = filter_a[(*t) + 1];
	filter_a[(*t)] = NULL;
	free((*f));
	(*t) = (*mem) - 1;
}
