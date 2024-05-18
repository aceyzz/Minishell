/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:51:28 by cedmulle          #+#    #+#             */
/*   Updated: 2024/05/17 19:12:46 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_pid_in_str(char *str)
{
	char	*pid;
	char	*start;
	char	*end;
	char	*new_str;
	char	*result;

	pid = ft_itoa(getpid());
	start = ft_substr(str, 0, ft_strstr(str, "$$") - str);
	end = ft_substr(str, (ft_strstr(str, "$$") - str) + 2, ft_strlen(str));
	new_str = ft_strjoin(start, pid);
	result = ft_strjoin(new_str, end);
	free(start);
	free(end);
	free(new_str);
	free(pid);
	return (result);
}

static void	replace_pid_in_input(char **input, int i)
{
	char	*tmp;

	while (ft_strstr(input[i], "$$"))
	{
		tmp = replace_pid_in_str(input[i]);
		free(input[i]);
		input[i] = tmp;
	}
}

char	**expand_pid(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		replace_pid_in_input(input, i);
		i++;
	}
	return (input);
}
