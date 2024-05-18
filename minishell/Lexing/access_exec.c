/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:28:05 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 01:19:42 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**argument_exec(t_token *tokens)
{
	char	**arg_sys;
	char	*tmp;
	int		i;
	int		t;

	arg_sys = malloc((tablen(tokens->argument) + 2) * sizeof(char *));
	if (!arg_sys)
		return (NULL);
	i = 0;
	tmp = ft_strdup(tokens->cmd);
	tmp = erase_quote(tmp);
	arg_sys[i++] = ft_strdup(tmp);
	free(tmp);
	t = 0;
	while (tokens->argument[t])
		arg_sys[i++] = ft_strdup(tokens->argument[t++]);
	arg_sys[i] = NULL;
	free_tab(tokens->argument);
	return (arg_sys);
}

int	is_exec(t_token *tokens)
{
	if (tokens->cmd)
		if (tokens->cmd[0] == '/' || (tokens->cmd[0] == '.'
				&& tokens->cmd[1] == '/'))
			tokens->argument = argument_exec(tokens);
	return (1);
}
