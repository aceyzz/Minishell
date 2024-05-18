/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:51:01 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 15:11:26 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_token *tokens)
{
	char	*tmp;

	if (!tokens->cmd)
		return (1);
	tmp = ft_strdup(tokens->cmd);
	tmp = erase_quote(tmp);
	if (ft_strncmp(tmp, "echo", 4) == 0 || ft_strncmp(tmp, "cd", 2) == 0
		|| ft_strncmp(tmp, "env", 3) == 0 || ft_strncmp(tmp, "unset", 5) == 0
		|| ft_strncmp(tmp, "export", 6) == 0 || ft_strncmp(tmp, "pwd", 3) == 0
		|| ft_strncmp(tmp, "exit", 4) == 0 || tmp[0] == '/' || (tmp[0] == '.'
			&& tmp[1] == '/') || tmp[0] == '$')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static void	complete_way(char **way, char *cmd, char **tmp, int t)
{
	int	i;
	int	j;

	i = -1;
	while (way[t][++i])
		(*tmp)[i] = way[t][i];
	j = -1;
	while (cmd[++j])
		(*tmp)[i++] = cmd[j];
	(*tmp)[i] = '\0';
}

static char	**add_cmd(char *cmd, char **way)
{
	char	**new_way;
	char	*tmp;
	char	*erase;
	int		t;

	t = 0;
	new_way = malloc((tablen(way) + 1) * sizeof(char *));
	if (!new_way)
		return (NULL);
	while (way[t])
	{
		tmp = malloc((ft_strlen(way[t]) + ft_strlen(cmd) + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		erase = ft_strdup(cmd);
		erase = erase_quote(erase);
		complete_way(way, erase, &tmp, t);
		new_way[t] = ft_strdup(tmp);
		free(tmp);
		free(erase);
		t++;
	}
	new_way[t] = NULL;
	return (new_way);
}

static int	exec_sys_child(t_token *tokens, t_export *alloctrack, char **way)
{
	pid_t	child;

	if (tokens->operator)
		if (ft_strncmp(tokens->operator, "<<", 2) == 0
			&& tokens->operator[2] == '\0')
			redirect_input(alloctrack->heredoc);
	child = fork();
	if (child == 0)
	{
		default_signals();
		ignore_sigquit();
		tokens->argument = argument_exec(tokens);
		if (execve(way[alloctrack->access], tokens->argument,
				alloctrack->environ) == -1)
			exit(EXIT_FAILURE);
	}
	else if (child > 0)
	{
		waitpid(child, &alloctrack->status, 0);
		if (WIFEXITED(alloctrack->status))
			alloctrack->status = WEXITSTATUS(alloctrack->status);
	}
	free_tab(way);
	return (0);
}
// Remonter info du child dans parent (perro ? )

int	exec_system(t_token *tokens, t_export *alloctrack)
{
	char	**way;

	if (is_builtin(tokens))
		return (1);
	alloctrack->way = init_way_path(alloctrack);
	if (!alloctrack->way)
	{
		alloctrack->status = 127;
		return (1);
	}
	way = add_cmd(tokens->cmd, alloctrack->way);
	free_tab(alloctrack->way);
	signal(SIGINT, SIG_IGN);
	if (is_access(way, alloctrack))
		return (exec_sys_child(tokens, alloctrack, way));
	free_tab(way);
	return (1);
}
