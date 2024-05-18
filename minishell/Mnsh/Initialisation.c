/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:48:41 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 18:35:25 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup(char **env)
{
	int		t;
	char	**dup;

	dup = malloc((tablen(env) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	t = 0;
	while (env[t])
	{
		dup[t] = ft_strdup(env[t]);
		t++;
	}
	dup[t] = NULL;
	return (dup);
}

static void	increment_shlvl(char **env)
{
	int		i;
	char	*shlvl;
	char	*new_shlvl;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_strdup(env[i] + 6);
			new_shlvl = ft_itoa(ft_atoi(shlvl) + 1);
			tmp = ft_strjoin("SHLVL=", new_shlvl);
			free(env[i]);
			env[i] = tmp;
			free(shlvl);
			free(new_shlvl);
			break ;
		}
		i++;
	}
}

// Fonction qui gère l'initialisation de la structure t_export déclaré le .h
// Cette structure vise à pointé vers zones mémoires allouer dans le tableau env
// Environ étant un tableau systeme gere la mémoire de ce qu'il alloue,
// Tous les éléments pointeur du tableau pointe sur NULL par sécurité
// count_ptr sera notre index pour notre tableau
// not_environ identifie si nous avons du créer le tableau environ ou non
t_export	*init(char **env)
{
	t_export	*alloctrack;
	char		*reg;

	reg = "Register.\n";
	alloctrack = malloc(sizeof(t_export));
	if (!alloctrack)
		return (NULL);
	alloctrack->environ = ft_tabdup(env);
	increment_shlvl(alloctrack->environ);
	if (!alloctrack->environ)
		return (NULL);
	alloctrack->status = 0;
	alloctrack->way = NULL;
	alloctrack->heredoc = HRDC_FILE;
	redirect_output(alloctrack->heredoc);
	write(STDOUT_FILENO, reg, ft_strlen(reg));
	alloctrack->pipex = PIPE_FILE;
	redirect_output(alloctrack->pipex);
	write(STDOUT_FILENO, reg, ft_strlen(reg));
	alloctrack->pipe_x = PIPE_X_FILE;
	redirect_output(alloctrack->pipe_x);
	write(STDOUT_FILENO, reg, ft_strlen(reg));
	alloctrack->back = 42;
	alloctrack->access = 42;
	return (alloctrack);
}
