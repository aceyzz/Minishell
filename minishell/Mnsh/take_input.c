/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:51:25 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 12:07:11 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getcwd(void)
{
	char	*result;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	result = ft_strdup(ft_strrchr(tmp, '/'));
	free(tmp);
	return (result);
}

static char	*getprompt(void)
{
	char	*s1;
	char	*pwd;
	char	*concat;
	int		i;
	int		c;

	s1 = RED "[m" ANSI_COLOR_WHITE "ns" RED "h] ☀️ 😎 ☀️  " ANSI_COLOR_RESET;
	pwd = ft_getcwd();
	if (!pwd)
		return (NULL);
	concat = malloc((ft_strlen(s1) + ft_strlen(pwd) + 6) * sizeof(char));
	i = 0;
	c = 0;
	while (s1[i])
		concat[c++] = s1[i++];
	concat[c++] = '/';
	i = 0;
	while (pwd[i])
		concat[c++] = pwd[i++];
	concat[c++] = ' ';
	concat[c++] = ':';
	concat[c++] = ' ';
	concat[c] = '\0';
	free(pwd);
	return (concat);
}

static char	*trim_n_free(char *input)
{
	char	*result;

	if (input == NULL)
		return (NULL);
	if (input[0] == '\0')
		return (input);
	result = ft_strtrim(input, WHITESPACE);
	free(input);
	if (check_quotes(result) == false)
	{
		free(result);
		result = malloc(1);
		result[0] = '\0';
		ft_putstr_fd("mnsh: unclosed quotes\n", 2);
	}
	return (result);
}

// Fonction qui prend l'input.
// READLINE A DES LEAKS !
char	*take_input(t_export *alloctrack)
{
	char	*input;
	char	*prompt;
	int		take;

	take = 0;
	while (take == 0)
	{
		prompt = getprompt();
		input = readline(prompt);
		input = trim_n_free(input);
		free(prompt);
		if (input)
		{
			if (input[0] == '\0')
			{
				free(input);
				return (NULL);
			}
			add_history(input);
			take = 1;
		}
		if (input == NULL)
			ft_exit(-42, alloctrack);
	}
	return (input);
}
