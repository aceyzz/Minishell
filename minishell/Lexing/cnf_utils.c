/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:33:16 by waziz             #+#    #+#             */
/*   Updated: 2024/04/24 13:00:39 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Condition parsing echo et echo -n
int	error_echo(char *cmd, t_export *alloctrack)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] != '\0')
	{
		if (ft_strncmp(cmd, "echo -n", 7) == 0 && cmd[7] == '\0')
			return (1);
		else
		{
			dup2(alloctrack->std[0], STDIN_FILENO);
			dup2(alloctrack->std[1], STDOUT_FILENO);
			printf("mnsh : command not found : %s\n", cmd);
			alloctrack->status = 127;
			return (0);
		}
	}
	return (1);
}

// Condition parsing cd
int	error_cd(char *cmd, t_export *alloctrack)
{
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	return (1);
}

// Condition parsing pwd
int	error_pwd(char *cmd, t_export *alloctrack)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	return (1);
}

int	error_export_unset_env(char *cmd, t_export *alloctrack)
{
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	return (1);
}

// Condition parsing exit
int	error_exit(char *cmd, t_export *alloctrack)
{
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] != '\0')
	{
		dup2(alloctrack->std[0], STDIN_FILENO);
		dup2(alloctrack->std[1], STDOUT_FILENO);
		printf("mnsh : command not found : %s\n", cmd);
		alloctrack->status = 127;
		return (0);
	}
	return (1);
}
