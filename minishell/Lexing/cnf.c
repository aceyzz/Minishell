/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:35:10 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 12:59:09 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction qui met le char * dans un char ** pour le convertir via la fonction
// de parsing qui nous sert à traiter tous les cas entre et en dehors des quotes
static int	traduct_cmd(t_token *tokens, t_export *alloctrack)
{
	char	**tmp;

	tmp = malloc(2 * sizeof(char *));
	if (!tmp)
		return (error_zero(2));
	tmp[0] = ft_strdup(tokens->cmd);
	tmp[1] = NULL;
	free(tokens->cmd);
	tmp = ft_parsing(tmp, alloctrack);
	if (tmp)
	{
		if (tmp[0] || tmp[0][0] == '\0')
			tokens->cmd = ft_strdup(tmp[0]);
	}
	else
		tokens->cmd = NULL;
	free_tab(tmp);
	return (1);
}

// Fonction qui check si dans commande il y a "bonjour" par exemple
// Renvoi une erreur si c'est le cas.
static int	other_parse(char *cmd, t_export *alloctrack)
{
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		return (1);
	if (ft_strncmp(cmd, "echo", 4) != 0 && ft_strncmp(cmd, "cd", 2) != 0
		&& ft_strncmp(cmd, "pwd", 3) != 0 && ft_strncmp(cmd, "export", 6) != 0
		&& ft_strncmp(cmd, "unset", 5) != 0 && ft_strncmp(cmd, "env", 3) != 0
		&& ft_strncmp(cmd, "exit", 4) != 0 && cmd)
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	return (1);
}

// Fonction qui check si la cmd comporte une erreur
// Via les fonctions appelé
// Affiche un message dans le terminal via celle ci
// Return 0 pour indiquer l'erreur ou 1 si la cmd est ok.
int	command_not_found(t_token *tokens, t_export *alloctrack)
{
	if (!tokens->cmd)
		return (1);
	if (!traduct_cmd(tokens, alloctrack))
		return (0);
	if (!tokens->cmd)
		return (0);
	else if (!error_echo(tokens->cmd, alloctrack))
		return (0);
	else if (!error_cd(tokens->cmd, alloctrack))
		return (0);
	else if (!error_pwd(tokens->cmd, alloctrack))
		return (0);
	else if (!error_export_unset_env(tokens->cmd, alloctrack))
		return (0);
	else if (!error_exit(tokens->cmd, alloctrack))
		return (0);
	else if (!other_parse(tokens->cmd, alloctrack))
		return (0);
	else
		return (1);
}
