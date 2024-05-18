/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:46:07 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 21:19:49 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui gère l'appel de la commande unset tel que défini
// dans le vrai terminal
static int	make_unset(t_token *tokens, t_export *alloctrack)
{
	int	t;

	if (ft_strncmp(tokens->cmd, "unset", 5) == 0 && tokens->cmd[5] == '\0')
	{
		if (!tokens->argument[0])
		{
			printf("mnsh : unset : Not enough arguments\n");
			alloctrack->status = 1;
			return (0);
		}
		t = 0;
		while (tokens->argument[t])
		{
			if (!ft_unset(tokens->argument[t++], alloctrack))
			{
				alloctrack->status = -42;
				return (0);
			}
		}
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui gère l'appel de la commande env tel que défini
// dans le vrai terminal
static int	make_env(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->cmd, "env", 3) == 0 && tokens->cmd[3] == '\0')
	{
		if (tokens->argument[0] != NULL)
		{
			printf("mnsh : env -> %s : No such file or directory\n",
				tokens->argument[0]);
			alloctrack->status = 127;
			return (1);
		}
		if (!ft_env(alloctrack))
		{
			alloctrack->status = -42;
			return (0);
		}
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui gère l'appel de la commande exit tel que défini
// dans le vrai terminal
static int	make_exit(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->cmd, "exit", 4) == 0 && tokens->cmd[4] == '\0')
	{
		if (tokens->argument[0] != NULL)
		{
			if (tokens->argument[1] != NULL)
				printf("mnsh: exit: too many arguments\n");
			else if (ft_isnumeric(tokens->argument[0]))
				ft_exit(ft_atoi(tokens->argument[0]), alloctrack);
			else
			{
				printf("mnsh : exit : %s : numeric argument required\n",
					tokens->argument[0]);
				ft_exit(-1, alloctrack);
			}
		}
	}
	return (1);
}

// Fonction qui gère l'appel de l'execution d'executable tel que défini
// dans le vrai terminal
static int	make_exec(t_token *tokens, t_export *alloctrack)
{
	if (tokens->cmd[0] == '/' || (tokens->cmd[0] == '.'
			&& tokens->cmd[1] == '/'))
	{
		if (!exec(tokens->cmd, tokens->argument, alloctrack))
		{
			alloctrack->status = 127;
			return (0);
		}
	}
	return (1);
}

// Fonction maitresse pour les commandes.
// Si une d'entre elle s'execute elle retourne 1.
int	cmd(t_token *tokens, t_export *alloctrack)
{
	if (!tokens->cmd)
		return (1);
	if (!make_echo(tokens, alloctrack))
		return (0);
	if (!make_echon(tokens, alloctrack))
		return (0);
	if (!make_cd(tokens, alloctrack))
		return (0);
	if (!make_pwd(tokens, alloctrack))
		return (0);
	if (!make_export(tokens, alloctrack))
		return (0);
	if (!make_unset(tokens, alloctrack))
		return (0);
	if (!make_env(tokens, alloctrack))
		return (0);
	if (make_exit(tokens, alloctrack) == -42)
		return (-42);
	if (!make_exec(tokens, alloctrack))
		return (0);
	return (1);
}
