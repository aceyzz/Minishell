/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:20 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 13:28:13 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// "<"
// Redirection de l'entrée du terminal (STDIN) vers un fichier
// Gestion des errerus si le fichier n'existe pas
// Gestion de l'erreur si la mutation de l'entrée échoue
// Gestion de l'erreur si la fermeture du fichier échoue
int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_zero(3));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (error_zero(4));
	if (close(fd) == -1)
		return (error_zero(5));
	return (1);
}

// ">"
// Redirection de la sortie du terminal (STDOUT) vers un fichier
// Le fichier est créé si il n'existe pas
// Le fichier est totalement tronqué si il existe deja
// Autorisation à different users ou groupe.
// Gestion des errerus si le fichier n'existe pas
// Gestion de l'erreur si la mutation de l'entrée échoue
// Gestion de l'erreur si la fermeture du fichier échoue
int	redirect_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (error_zero(3));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (error_zero(4));
	if (close(fd) == -1)
		return (error_zero(5));
	return (1);
}
