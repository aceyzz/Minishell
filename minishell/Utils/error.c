/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:55:05 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 17:54:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui affiche le problème rencontré et retourne 0
int	error_zero(int num)
{
	if (num == 1)
		perror("mnsh : Error Opendir");
	if (num == 2)
		perror("mnsh : Allocated memory failed");
	if (num == 3)
		perror("mnsh : Openfile");
	if (num == 4)
		perror("mnsh : Redirecting Dup2");
	if (num == 5)
		perror("mnsh : Closing file");
	if (num == 6)
		perror("mnsh : Read Error");
	if (num == 7)
		printf("mnsh : Writing Error\n");
	if (num == 8)
		perror("mnsh : cd");
	if (num == 9)
		perror("mnsh : pwd");
	if (num == 10)
		perror("mnsh : fork");
	if (num == 11)
		perror("mnsh : pipe");
	if (num == 12)
		perror("mnsh : execve");
	return (0);
}

// Fonction qui affiche le problème rencontré et retourne -1
int	error_neg(int n)
{
	if (n == 1)
		printf("mnsh : Writing Error\n");
	return (-1);
}

// Fonction qui affiche le problème rencontré et retourne NULL
char	*error_null(int n)
{
	if (n == 1)
		perror("mnsh : Allocated memory failed");
	if (n == 2)
		printf("mnsh : Writing Error\n");
	return (NULL);
}

int	err_exit(int num)
{
	if (num == 1)
		perror("mnsh : execve");
	exit(1);
}
