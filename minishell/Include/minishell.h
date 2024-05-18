/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:02 by waziz             #+#    #+#             */
/*   Updated: 2024/05/17 21:21:08 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Constants
# define HRDC_FILE "/tmp/.heredoc"
# define PIPE_FILE "/tmp/.pipex"
# define PIPE_X_FILE "/tmp/.pipe_x"
# define WHITESPACE " \t\n\r\f\v"

// Colors
# define RED "\x1b[31m"
# define ANSI_COLOR_WHITE "\x1b[37m"
# define ANSI_COLOR_RESET "\x1b[0m"

// Create with our hands
# include "../Libft/libft.h"

// System libraries
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// Local libraries
# include "readline/history.h"
# include "readline/readline.h"

typedef struct s_export
{
	char			**environ;
	char			**way;
	char			*heredoc;
	char			*pipex;
	char			*pipe_x;
	int				std[2];
	int				status;
	int				back;
	int				access;
}					t_export;

typedef struct s_token
{
	char			*input;
	char			**argument;
	char			*cmd;
	char			*operator;
	char			*arg_operator;
	int				pipe;
	int				quotes;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_utils
{
	char			**tokens;
	int				capacity;
	int				size;
}					t_utils;

// header.c
void				ft_header(void);

// -- PARSING --

// convert_utils.c
char				*choose_convert(char *dollars, t_export *alloctrack);
char				*dollars_lex(char *var_name, t_export *alloctrack);
char				*ft_strcat(char *dst, char *src);

// convert.c
char				*convert_n_concat(char **arg_more, t_export *alloctrack);

// new_arg_utils.c
char				**quote_parse(char *arg);

// new_arg.c
char				**replace_argument(char **argument, t_export *alloctrack);

// erase_quote.c
char				*erase_quote(char *s);

// pid_utils.c
char				**expand_pid(char **arg_more);

// parsing.c
int					check_wildcard(char *s);
char				**ft_parsing(char **argument, t_export *alloctrack);

// -- OPERATORS -- All Operators

// cmd_redirect.c
int					redirect_input(char *filename);
int					redirect_output(char *filename);

// redirect_input_cmd.c
int					redirect_input_command(t_token *tokens,
						t_export *alloctrack);

// redirect_stdout.c
int					redirect_stdout_append(char *fichier);

// -- CMD -- All commands

// cd.c
int					cd(char *path);

// echo.c
int					echo(char *input);
int					echon(char *input);

// env.c
int					ft_env(t_export *alloctrack);

// exec.c
int					exec(char *exec, char **arg, t_export *alloctrack);

// exit.c
void				ft_exit(int num, t_export *alloctrack);

// export.c
int					ft_export(char *v_env, t_export *alloctrack);

// pwd.c
int					pwd(void);

// unset.c
int					ft_unset(char *var_name, t_export *alloctrack);

// value_return.c
char				*last_return(int status);

// -- BONUS --

// skip_quote_a.c
char				*erase_quote_a(char *input);
int					skip_quote_a(char *input);

// skip_quote_b.c
char				*erase_quote_b(char *input);
int					skip_quote_b(char *input);

// skip_utils.c
int					quote_count_b(char *input);
int					quote_count_a(char *input);
void				count_w(char *tmp, int *w);

// skip_quote_middle.c
char				**init_search(char *tmp);

// all_files.c
char				**all_files(void);

// wildcards_ab.c
char				**filter_b(char *input);
char				**filter_a(char *input);

// wildcards_utils.c
void				deleter(char **filter_a, char **f, int *mem, int *t);

// wildcards_mult.c
char				**filter_more(char *input);

// wildcards.c
char				**filter_ab(char *input);
char				**wildcards(char *input);

// -- UTILS --

// initialisation.c
char				**ft_tabdup(char **env);
t_export			*init(char **env);

// error.c
int					error_zero(int num);
int					error_neg(int n);
char				*error_null(int n);
int					err_exit(int num);

// free.c
void				free_tab(char **entries);
void				free_alloctrack(t_export *alloctrack);
void				free_token_list(t_token **tokens);
void				free_single_token(t_token *token);

// utils.c
int					tablen(char **tab);
int					tab_slen(char **tab);
int					ft_strlen(char *str);
char				*ft_strstr(const char *s1, const char *s2);
int					search_occurence(char *str1, char *str2);

// -- LEXING --

// access_exec.c
char				**argument_exec(t_token *tokens);
int					is_exec(t_token *tokens);

// access_utils.c
char				**init_way_path(t_export *alloctrack);
int					is_access(char **way, t_export *alloctrack);

// access.c
int					exec_system(t_token *tokens, t_export *alloctrack);

// operator.c
int					operators(t_token *tokens, t_export *alloctrack);

// cmd_utils.c
int					make_echo(t_token *tokens, t_export *alloctrack);
int					make_echon(t_token *tokens, t_export *alloctrack);
int					make_cd(t_token *tokens, t_export *alloctrack);
int					make_pwd(t_token *tokens, t_export *alloctrack);
int					make_export(t_token *tokens, t_export *alloctrack);

// exit_code_utils.c
bool				ft_isnumeric(char *str);

// cmd.c
int					cmd(t_token *tokens, t_export *alloctrack);

// cnf_utils.c
int					error_echo(char *cmd, t_export *alloctrack);
int					error_cd(char *cmd, t_export *alloctrack);
int					error_pwd(char *cmd, t_export *alloctrack);
int					error_export_unset_env(char *cmd, t_export *alloctrack);
int					error_exit(char *cmd, t_export *alloctrack);

// cnf.c
int					command_not_found(t_token *tokens, t_export *alloctrack);

// lexing.c
int					lexing(t_token *tokens, t_export *alloctrack);

// -- MINISHELL --
// take_input.c
char				*take_input(t_export *alloctrack);

// input_pipe.c
char				*check_pipe(char *input);

// signaux.c
void				signal_print_newline(int signal);
void				default_signals(void);
void				setup_signal(struct sigaction *sa);
void				ignore_sigquit(void);

// mnsh_utils.c
t_token				*create_void_token(void);
void				save_std(int fd[2]);
void				redirect_std(int fd[2]);
void				ft_pipe_in(t_export *alloctrack, int *in_out);
void				ft_pipe_out(t_export *alloctrack, int *in_out);

// added cat cat ls
t_token				*new_list(t_token *tokens);
char				**file_to_tab_wo(void);

// -- DEBUG --

// Mnsh/Debug.c
void				printer_tokens(t_token *tokens);
void				print_argument(char **argument);
void				print_tok(t_token *tokens);
void				print_tab(char **tab);

/*//////////////////////////////////////////////////////////////////////////*/
/* 									PARSING
/*//////////////////////////////////////////////////////////////////////////*/

// splitter_first_inits.c
char				**is_echo_n(char **ss);
void				skip_quotes_fp(char *input, int *i);
void				handle_space_or_null(char **tmp, int *i, char ***ss,
						int *t);
char				**init_ss(char *input, char **ss);

// splitter_first_spaces.c
char				**delete_space(char **ss);
int					no_space(char *input);
int					count_split_space(char *input);
void				notspace_notnull(char *input, int *i);
char				**split_space(char *input);

// splitter_scnd_main.c
void				handle_special_cases(t_utils *p, char **current,
						char **segment_start);
void				split_string(t_utils *p, char *str);
char				**split_into_tokens(char **input);
t_token				*parse_and_tokenize(char *input);

// splitter_scnd_utils.c
bool				is_special_character(char c);
bool				is_quoted(char *str, int index);
void				add_token(t_utils *p, char *start, int length);

/*//////////////////////////////////////////////////////////////////////////*/
/*									TOKENIZATION
/*//////////////////////////////////////////////////////////////////////////*/
// tokenizer_utils.c
bool				check_quotes(char *input);
t_token				*init_token(void);
void				add_token_to_list(t_token **head, t_token *new_token);
void				copy_arguments(t_token *dest, t_token *src);
void				init_prev(t_token **token);

// tokenizer_handlers.c
void				handle_sucessive_redirs(t_token **head, char **tab,
						int *index, t_token **current_token);
void				handle_redirs_n_args(t_token **head, char **tab, int *index,
						t_token *current_token);
void				handle_args_n_cmd(t_token *token, char **tab, int *index);
void				handle_special_case(t_token **head, char **tab, int *index);
void				handle_initials_sucessive_redirs(t_token **head, char **tab,
						int *index);

// tokenizer.c
void				parse_command_line(t_token **head, char **tab, int *index);
void				handle_loop_content(t_token ***tokens, char **tab, int *i);
void				fill_list_from_tab(t_token **tokens, char **tab);
t_token				*tokenizer(char **raw_tab_tokens);

// split_space.c
t_token				*parse_and_tokenize(char *input);

#endif
