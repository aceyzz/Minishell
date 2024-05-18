/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 07:47:03 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 12:17:07 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// "cd avec uniquement un chemin relatif ou absolu"
// chdir: only chemins relatif ou absolu
// gestion de l'erreur si le chemin donné n'est pas valide.
int	cd(char *path)
{
	if (chdir(path) == -1)
		return (error_zero(8));
	return (1);
}
