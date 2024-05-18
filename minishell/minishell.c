/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:04:51 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 18:43:58 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*take_n_tokenize(t_export *alloctrack)
{
	t_token	*tokens;
	char	*input;

	input = take_input(alloctrack);
	if (!check_pipe(input))
		return (NULL);
	if (!input)
		return (NULL);
	if (input && input[0] == '\0')
	{
		free(input);
		tokens = create_void_token();
		return (tokens);
	}
	tokens = parse_and_tokenize(input);
	init_prev(&tokens);
	tokens = new_list(tokens);
	if (!tokens)
	{
		free(input);
		return (NULL);
	}
	tokens->input = ft_strdup(input);
	free(input);
	return (tokens);
}

static void	ft_pipeline(t_export *alloctrack, t_token **tokens, int *in_out)
{
	t_token	*tmp;

	if ((*tokens)->pipe == 1)
	{
		ft_pipe_in(alloctrack, &(*in_out));
		if ((*tokens)->next)
		{
			tmp = (*tokens);
			(*tokens) = (*tokens)->next;
			free_single_token(tmp);
		}
	}
	if ((*tokens)->next)
		if ((*tokens)->next->pipe == 1)
			ft_pipe_out(alloctrack, &(*in_out));
}

static int	execute(t_token **tokens, t_export *alloctrack, int fd[2],
		int in_out)
{
	t_token	*tmp;

	*tokens = take_n_tokenize(alloctrack);
	if (!(*tokens))
		return (0);
	if ((*tokens)->pipe == 42)
		return (-42);
	while ((*tokens))
	{
		ft_pipeline(alloctrack, &(*tokens), &in_out);
		alloctrack->back = lexing((*tokens), alloctrack);
		if (alloctrack->back == 0)
			return (0);
		if (alloctrack->back == -42)
			return (-42);
		redirect_std(fd);
		tmp = (*tokens);
		(*tokens) = (*tokens)->next;
		free_single_token(tmp);
	}
	return (1);
}

static int	minishell(t_export *alloctrack, int fd[2])
{
	t_token				*tokens;
	struct sigaction	sa;
	int					status;
	int					in_out;

	tokens = NULL;
	while (1)
	{
		in_out = 0;
		setup_signal(&sa);
		status = execute(&tokens, alloctrack, fd, in_out);
		if (status == -42)
		{
			free_token_list(&tokens);
			rl_clear_history();
			ft_exit(-42, alloctrack);
		}
		free_token_list(&tokens);
	}
	free_token_list(&tokens);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_export	*alloctrack;
	int			fd[2];

	(void)argc;
	(void)argv;
	ft_header();
	save_std(fd);
	alloctrack = init(env);
	redirect_std(fd);
	alloctrack->std[0] = dup(0);
	alloctrack->std[1] = dup(1);
	minishell(alloctrack, fd);
	return (0);
}
