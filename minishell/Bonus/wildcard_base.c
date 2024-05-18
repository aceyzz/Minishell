/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:49:48 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 20:25:00 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_count(DIR **opn)
{
	int	i;

	i = 0;
	*opn = opendir(".");
	if (!(*opn))
		return (-1);
	while (readdir(*opn) != NULL)
		i++;
	closedir(*opn);
	*opn = opendir(".");
	if (!(*opn))
		return (-1);
	return (i);
}

char	**cleandup(char **files_names)
{
	char	**skro;

	skro = ft_tabdup(files_names + 2);
	free_tab(files_names);
	return (skro);
}

char	**all_files(void)
{
	DIR				*opn;
	struct dirent	*files_found;
	char			**files_names;
	char			**skro;
	int				i;

	i = check_n_count(&opn);
	if (i < 0)
		return (NULL);
	files_names = malloc((i + 1) * sizeof(char *));
	if (!files_names)
		return (NULL);
	i = 0;
	files_found = readdir(opn);
	while (files_found != NULL)
	{
		files_names[i++] = ft_strdup(files_found->d_name);
		files_found = readdir(opn);
	}
	files_names[i] = NULL;
	closedir(opn);
	skro = cleandup(files_names);
	return (skro);
}
