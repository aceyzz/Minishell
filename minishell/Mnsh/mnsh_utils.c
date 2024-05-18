/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnsh_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waziz <waziz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:39:22 by waziz             #+#    #+#             */
/*   Updated: 2024/04/22 23:32:48 by waziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_void_token(void)
{
	t_token	*token_void;

	token_void = malloc(sizeof(t_token));
	if (!token_void)
		return (NULL);
	token_void->input = ft_strdup("");
	token_void->argument = NULL;
	token_void->cmd = NULL;
	token_void->operator = NULL;
	token_void->arg_operator = NULL;
	token_void->pipe = 42;
	token_void->next = NULL;
	return (token_void);
}

void	save_std(int fd[2])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

void	redirect_std(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

void	ft_pipe_out(t_export *alloctrack, int *in_out)
{
	if ((*in_out) == 0)
		redirect_output(alloctrack->pipex);
	if ((*in_out) == 1)
		redirect_output(alloctrack->pipe_x);
}

void	ft_pipe_in(t_export *alloctrack, int *in_out)
{
	if ((*in_out) == 0)
	{
		redirect_input(alloctrack->pipex);
		(*in_out) = 1;
	}
	else
	{
		redirect_input(alloctrack->pipe_x);
		(*in_out) = 0;
	}
}
