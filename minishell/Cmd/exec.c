/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:24:01 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 17:56:48 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(char *exec, char **arg, t_export *alloctrack)
{
	pid_t	children;

	children = fork();
	if (children == -1)
		return (error_zero(10));
	signal(SIGINT, SIG_IGN);
	if (children == 0)
	{
		if (execve(exec, arg, alloctrack->environ) == -1)
			return (err_exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(children, &alloctrack->status, 0);
		if (WIFEXITED(alloctrack->status))
			alloctrack->status = WEXITSTATUS(alloctrack->status);
	}
	return (1);
}
