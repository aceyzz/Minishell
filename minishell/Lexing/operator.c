/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:44:59 by waziz             #+#    #+#             */
/*   Updated: 2024/04/20 13:02:36 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui met le char * dans un char ** pour le convertir via la fonction
// de parsing qui nous sert à traiter tous les cas entre et en dehors des quotes
static int	parsing_argop(t_token *tokens, t_export *alloctrack)
{
	char	**tmp;

	tmp = malloc(2 * sizeof(char *));
	if (!tmp)
		return (error_zero(2));
	tmp[0] = ft_strdup(tokens->arg_operator);
	tmp[1] = NULL;
	free(tokens->arg_operator);
	if (ft_strncmp(tokens->operator, "<<", 2) == 0
		&& tokens->operator[2] == '\0')
		tmp[0] = erase_quote(tmp[0]);
	else
		tmp = ft_parsing(tmp, alloctrack);
	if (tmp[0] && tmp[0][0] != '\0')
		tokens->arg_operator = ft_strdup(tmp[0]);
	else
		tokens->arg_operator = NULL;
	free_tab(tmp);
	return (1);
}

// Fonction qui gère les cas d'erreur si l'argument n'est pas valide.
static int	traduct(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->arg_operator, "<", 1) == 0)
	{
		if (ft_strncmp(tokens->arg_operator, "<<", 2) == 0)
			printf("mnsh: parse error near '<<'\n");
		else
			printf("mnsh : parse error near '<'\n");
		alloctrack->status = 1;
		return (0);
	}
	if (ft_strncmp(tokens->arg_operator, ">", 1) == 0)
	{
		if (ft_strncmp(tokens->arg_operator, ">>", 2) == 0)
			printf("mnsh: parse error near '>>'\n");
		else
			printf("mnsh : parse error near '>'\n");
		alloctrack->status = 1;
		return (0);
	}
	parsing_argop(tokens, alloctrack);
	return (1);
}

// Fonction qui appel les fonction qui simule comportement des singles operators
static int	single_operator(t_token *tokens, t_export *alloctrack)
{
	if (ft_strncmp(tokens->operator, "<", 1) == 0
		&& tokens->operator[1] == '\0')
	{
		if (!redirect_input(tokens->arg_operator))
		{
			alloctrack->status = -42;
			return (0);
		}
		alloctrack->status = 0;
		return (1);
	}
	if (ft_strncmp(tokens->operator, ">", 1) == 0
		&& tokens->operator[1] == '\0')
	{
		if (!redirect_output(tokens->arg_operator))
		{
			alloctrack->status = -42;
			return (0);
		}
		alloctrack->status = 0;
		return (1);
	}
	return (1);
}

// Fonction d'appel les fonctions qui simule le comportement doubles operators
static int	double_operator(t_token *tokens, t_export *alloctrack)
{
	int	back;

	if (!ft_strncmp(tokens->operator, ">>", 2) && tokens->operator[2] == '\0')
	{
		if (!redirect_stdout_append(tokens->arg_operator))
		{
			alloctrack->status = -42;
			return (0);
		}
		alloctrack->status = 0;
	}
	if (ft_strncmp(tokens->operator, "<<", 2) == 0
		&& tokens->operator[2] == '\0')
	{
		back = redirect_input_command(tokens, alloctrack);
		if (back == 0)
		{
			alloctrack->status = -42;
			return (0);
		}
		if (back == -42)
			return (-42);
		alloctrack->status = 0;
	}
	return (1);
}

// Fonction qui appel toutes les fonctions au dessus dans l'ordre logique
int	operators(t_token *tokens, t_export *alloctrack)
{
	int	back;

	if (!tokens->operator)
		return (1);
	if (tokens->operator && !tokens->arg_operator)
	{
		printf("mnsh : parse error near : void argument\n");
		return (0);
	}
	if (!traduct(tokens, alloctrack))
		return (0);
	if (!single_operator(tokens, alloctrack))
		return (0);
	back = double_operator(tokens, alloctrack);
	if (back == 0)
		return (0);
	if (back == -42)
		return (-42);
	return (1);
}
