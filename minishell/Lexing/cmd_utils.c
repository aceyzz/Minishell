/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:10:45 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 14:24:31 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_echo(t_token *tokens, t_export *alloctrack)
{
	int	t;

	if (ft_strncmp(tokens->cmd, "echo", 4) == 0 && tokens->cmd[4] == '\0')
	{
		t = 0;
		if (!tokens->argument || !tokens->argument[0])
		{
			alloctrack->status = 0;
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		while (tokens->argument[t] != NULL)
		{
			if (!echo(tokens->argument[t]))
			{
				alloctrack->status = 127;
				return (0);
			}
			write(STDOUT_FILENO, " ", 1);
			t++;
		}
		alloctrack->status = 0;
		write(1, "\n", 1);
	}
	return (1);
}

// Fonction qui gère l'appel de la commande echo -n tel que défini
// dans le vrai terminal
int	make_echon(t_token *tokens, t_export *alloctrack)
{
	int	t;

	if (ft_strncmp(tokens->cmd, "echo -n", 7) == 0 && tokens->cmd[7] == '\0')
	{
		t = 0;
		if (!tokens->argument || !tokens->argument[0])
		{
			alloctrack->status = 0;
			return (0);
		}
		while (tokens->argument[t] != NULL)
		{
			if (!echon(tokens->argument[t]))
			{
				alloctrack->status = 127;
				return (0);
			}
			if (tokens->argument[t + 1])
				write(STDOUT_FILENO, " ", 1);
			t++;
		}
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui gère l'appel de la commande cd tel que défini
// dans le vrai terminal
int	make_cd(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->cmd, "cd", 2) == 0 && tokens->cmd[2] == '\0')
	{
		if (!tokens->argument[0])
		{
			printf("mnsh : cd : Only with relative or absolute path\n");
			alloctrack->status = 42;
			return (1);
		}
		if (tokens->argument[1])
		{
			printf("mnsh : cd : String not in pwd : %s\n", tokens->argument[0]);
			alloctrack->status = 1;
			return (1);
		}
		if (!cd(tokens->argument[0]))
		{
			alloctrack->status = 127;
			return (0);
		}
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui gère l'appel de la commande pwd tel que défini
// dans le vrai terminal
int	make_pwd(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->cmd, "pwd", 3) == 0 && tokens->cmd[3] == '\0')
	{
		if (tokens->argument[0])
		{
			printf("mnsh : pwd : Too many argument\n");
			alloctrack->status = 1;
			return (1);
		}
		if (!pwd())
		{
			alloctrack->status = -42;
			return (0);
		}
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui gère l'appel de la commande export tel que défini
// dans le vrai terminal
int	make_export(t_token *tokens, t_export *alloctrack)
{
	int	t;

	if (ft_strncmp(tokens->cmd, "export", 6) == 0 && tokens->cmd[6] == '\0')
	{
		if (!tokens->argument[0])
		{
			if (!ft_env(alloctrack))
			{
				alloctrack->status = -42;
				return (0);
			}
		}
		t = 0;
		while (tokens->argument[t] != NULL)
		{
			if (!ft_export(tokens->argument[t], alloctrack))
			{
				alloctrack->status = -42;
				return (0);
			}
			t++;
		}
	}
	alloctrack->status = 0;
	return (1);
}
