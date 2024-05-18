/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:46:58 by waziz             #+#    #+#             */
/*   Updated: 2024/04/21 12:16:03 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token_info(t_token *tokens)
{
	int	i;

	printf("Pipe is :\t\t%d\n", tokens->pipe);
	printf("Input is :\t\t%s\n", tokens->input);
	if (tokens->argument)
	{
		i = -1;
		while (tokens->argument[++i])
			printf("Argument[%d] is :\t%s\n", i, tokens->argument[i]);
		printf("Argument[%d] is :\t%s\n", i, tokens->argument[i]);
	}
	else
		printf("Argument is :\t\t(null)\n");
}

void	printer_tokens(t_token *tokens)
{
	if (tokens)
	{
		while (tokens)
		{
			printf("prev struct :\t\t%p\n", tokens->prev);
			printf("this struct :\t\t%p\n", tokens);
			printf("next struct :\t\t%p\n", tokens->next);
			print_token_info(tokens);
			printf("Cmd is : \t\t%s\n", tokens->cmd);
			printf("Operator is :\t\t%s\n", tokens->operator);
			printf("Arg_opérator is :\t%s\n", tokens->arg_operator);
			if (!tokens->next)
				printf("\n-- LAST TOKEN --\n");
			else
				printf("\n-- NEXT TOKEN --\n");
			tokens = tokens->next;
		}
	}
}

void	print_argument(char **argument)
{
	int	i;

	if (!argument)
		printf("Argument is :\t\t(null)\n");
	if (argument)
	{
		i = -1;
		while (argument[++i])
			printf("Argument[%d] is :\t%s\n", i, argument[i]);
		printf("Argument[%d] is :\t%s\n", i, argument[i]);
	}
}

void	print_tok(t_token *tokens)
{
	int	i;

	printf("Pipe is : %d\n", tokens->pipe);
	printf("Input is : %s\n", tokens->input);
	if (tokens->argument)
	{
		i = 0;
		while (tokens->argument[i])
		{
			printf("Argument[%d] is : %s\n", i, tokens->argument[i]);
			i++;
		}
		printf("Argument[%d] is : %s\n", i, tokens->argument[i]);
	}
	printf("Cmd is : %s\n", tokens->cmd);
	printf("Operator is : %s\n", tokens->operator);
	printf("Arg_opérator is : %s\n", tokens->arg_operator);
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		printf("Tab is : (null)\n");
	while (tab[++i])
		printf("tab[%d] : %s\n", i, tab[i]);
	printf("tab[%d] : %s\n", i, tab[i]);
}
