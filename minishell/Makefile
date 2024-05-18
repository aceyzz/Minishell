# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 17:05:45 by cedmulle          #+#    #+#              #
#    Updated: 2024/05/17 21:24:08 by cedmulle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
EXECUTABLE 		= minishell

# Compiler and flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

# A adapter selon chemin de la lib Readline
READLINE_DIR	:= /Users/cedmulle/.brew/opt/readline

# Readline
CFLAGS			+= -I$(READLINE_DIR)/include
LDFLAGS			+= -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses

# Directories
SRC_DIR 		= .
OBJ_DIR 		= ./obj
INC_DIR 		= ./Include
LIBFT_DIR 		= ./Libft

# Libraries
LIBFT 			= $(LIBFT_DIR)/libft.a

# Source files
SRC_MAIN 		= $(SRC_DIR)/header.c $(SRC_DIR)/minishell.c
SRC_FIRSTPARSE 	= $(SRC_DIR)/FirstParse/splitter_first_inits.c $(SRC_DIR)/FirstParse/splitter_first_spaces.c $(SRC_DIR)/FirstParse/splitter_scnd_main.c $(SRC_DIR)/FirstParse/splitter_scnd_utils.c $(SRC_DIR)/FirstParse/tokenizer_handlers.c $(SRC_DIR)/FirstParse/tokenizer_main.c $(SRC_DIR)/FirstParse/tokenizer_utils.c
SRC_PARSING 	= $(SRC_DIR)/Parsing/convert.c $(SRC_DIR)/Parsing/convert_utils.c $(SRC_DIR)/Parsing/erase_quote.c $(SRC_DIR)/Parsing/new_arg.c $(SRC_DIR)/Parsing/new_arg_utils.c $(SRC_DIR)/Parsing/parsing.c $(SRC_DIR)/Parsing/pid_utils.c
SRC_OPERATORS 	= $(SRC_DIR)/Operators/cmd_redirect.c $(SRC_DIR)/Operators/redirect_input_cmd.c $(SRC_DIR)/Operators/redirect_stdout.c
SRC_CMD 		= $(SRC_DIR)/Cmd/cd.c $(SRC_DIR)/Cmd/echo.c $(SRC_DIR)/Cmd/env.c $(SRC_DIR)/Cmd/exec.c $(SRC_DIR)/Cmd/exit.c $(SRC_DIR)/Cmd/export.c $(SRC_DIR)/Cmd/pwd.c $(SRC_DIR)/Cmd/unset.c $(SRC_DIR)/Cmd/value_return.c
SRC_BONUS 		= $(SRC_DIR)/Bonus/skip_quote_a.c $(SRC_DIR)/Bonus/skip_quote_b.c $(SRC_DIR)/Bonus/skip_quote_middle.c $(SRC_DIR)/Bonus/skip_utils.c $(SRC_DIR)/Bonus/wilcard_ab_utils.c $(SRC_DIR)/Bonus/wildcard_base.c $(SRC_DIR)/Bonus/wildcards.c $(SRC_DIR)/Bonus/wildcards_ab.c $(SRC_DIR)/Bonus/wildcards_mult.c
SRC_LEXING 		= $(SRC_DIR)/Lexing/access.c $(SRC_DIR)/Lexing/access_exec.c $(SRC_DIR)/Lexing/access_utils.c $(SRC_DIR)/Lexing/cmd.c $(SRC_DIR)/Lexing/cmd_utils.c $(SRC_DIR)/Lexing/cnf.c $(SRC_DIR)/Lexing/cnf_utils.c $(SRC_DIR)/Lexing/lexing.c $(SRC_DIR)/Lexing/operator.c $(SRC_DIR)/Lexing/exit_code_utils.c
SRC_MNSH 		= $(SRC_DIR)/Mnsh/Initialisation.c $(SRC_DIR)/Mnsh/cmd_without.c $(SRC_DIR)/Mnsh/debug.c $(SRC_DIR)/Mnsh/input_pipe.c $(SRC_DIR)/Mnsh/mnsh_utils.c $(SRC_DIR)/Mnsh/reverse.c $(SRC_DIR)/Mnsh/signaux.c $(SRC_DIR)/Mnsh/take_input.c
SRC_UTILS 		= $(SRC_DIR)/Utils/error.c $(SRC_DIR)/Utils/free.c $(SRC_DIR)/Utils/utils.c

# Object files
OBJ_MAIN 		= $(OBJ_DIR)/header.o $(OBJ_DIR)/minishell.o
OBJ_FIRSTPARSE 	= $(OBJ_DIR)/FirstParse/splitter_first_inits.o $(OBJ_DIR)/FirstParse/splitter_first_spaces.o $(OBJ_DIR)/FirstParse/splitter_scnd_main.o $(OBJ_DIR)/FirstParse/splitter_scnd_utils.o $(OBJ_DIR)/FirstParse/tokenizer_handlers.o $(OBJ_DIR)/FirstParse/tokenizer_main.o $(OBJ_DIR)/FirstParse/tokenizer_utils.o
OBJ_PARSING 	= $(OBJ_DIR)/Parsing/convert.o $(OBJ_DIR)/Parsing/convert_utils.o $(OBJ_DIR)/Parsing/erase_quote.o $(OBJ_DIR)/Parsing/new_arg.o $(OBJ_DIR)/Parsing/new_arg_utils.o $(OBJ_DIR)/Parsing/parsing.o $(OBJ_DIR)/Parsing/pid_utils.o
OBJ_OPERATORS	= $(OBJ_DIR)/Operators/cmd_redirect.o $(OBJ_DIR)/Operators/redirect_input_cmd.o $(OBJ_DIR)/Operators/redirect_stdout.o
OBJ_CMD 		= $(OBJ_DIR)/Cmd/cd.o $(OBJ_DIR)/Cmd/echo.o $(OBJ_DIR)/Cmd/env.o $(OBJ_DIR)/Cmd/exec.o $(OBJ_DIR)/Cmd/exit.o $(OBJ_DIR)/Cmd/export.o $(OBJ_DIR)/Cmd/pwd.o $(OBJ_DIR)/Cmd/unset.o $(OBJ_DIR)/Cmd/value_return.o
OBJ_BONUS 		= $(OBJ_DIR)/Bonus/skip_quote_a.o $(OBJ_DIR)/Bonus/skip_quote_b.o $(OBJ_DIR)/Bonus/skip_quote_middle.o $(OBJ_DIR)/Bonus/skip_utils.o $(OBJ_DIR)/Bonus/wilcard_ab_utils.o $(OBJ_DIR)/Bonus/wildcard_base.o $(OBJ_DIR)/Bonus/wildcards.o $(OBJ_DIR)/Bonus/wildcards_ab.o $(OBJ_DIR)/Bonus/wildcards_mult.o
OBJ_LEXING 		= $(OBJ_DIR)/Lexing/access.o $(OBJ_DIR)/Lexing/access_exec.o $(OBJ_DIR)/Lexing/access_utils.o $(OBJ_DIR)/Lexing/cmd.o $(OBJ_DIR)/Lexing/cmd_utils.o $(OBJ_DIR)/Lexing/cnf.o $(OBJ_DIR)/Lexing/cnf_utils.o $(OBJ_DIR)/Lexing/lexing.o $(OBJ_DIR)/Lexing/operator.o $(OBJ_DIR)/Lexing/exit_code_utils.o
OBJ_MNSH 		= $(OBJ_DIR)/Mnsh/Initialisation.o $(OBJ_DIR)/Mnsh/cmd_without.o $(OBJ_DIR)/Mnsh/debug.o $(OBJ_DIR)/Mnsh/input_pipe.o $(OBJ_DIR)/Mnsh/mnsh_utils.o $(OBJ_DIR)/Mnsh/reverse.o $(OBJ_DIR)/Mnsh/signaux.o $(OBJ_DIR)/Mnsh/take_input.o
OBJ_UTILS 		= $(OBJ_DIR)/Utils/error.o $(OBJ_DIR)/Utils/free.o $(OBJ_DIR)/Utils/utils.o

# Colors
REDD			= \033[1;31m
GRNN			= \033[1;32m
YELL			= \033[1;33m
BLUE			= \033[1;34m
PURP			= \033[1;35m
CYAN			= \033[1;36m
RST				= \033[0m
CLR 			= \033c
D_REDD			= \033[0;31m
D_GRNN			= \033[0;32m
D_YELL			= \033[0;33m
D_BLUE			= \033[0;34m
D_PURP			= \033[0;35m
D_CYAN			= \033[0;36m

# ---------------------------------------------------------------------------- #
# 									MAKE RULES								   #
# ---------------------------------------------------------------------------- #

# Rule to make the executable
$(EXECUTABLE): $(OBJ_MAIN) $(OBJ_FIRSTPARSE) $(OBJ_PARSING) $(OBJ_OPERATORS) $(OBJ_CMD) $(OBJ_BONUS) $(OBJ_LEXING) $(OBJ_MNSH) $(OBJ_UTILS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(CLR)\n\n$(YELL)----------------------------------------\n\n"
	@echo "    Executable $(EXECUTABLE) created !\n\n"
	@echo "----------------------------------------$(RST)\n\n"

# Rule to make object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | directories
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(CLR)-> $(D_CYAN)Compiling $<$(RST)"

directories:
	@mkdir -p $(OBJ_DIR)/FirstParse $(OBJ_DIR)/Parsing $(OBJ_DIR)/Operators $(OBJ_DIR)/Cmd $(OBJ_DIR)/Bonus $(OBJ_DIR)/Lexing $(OBJ_DIR)/Mnsh $(OBJ_DIR)/Utils

# Rule to compile libft
$(LIBFT):
	@echo "\n$(GRNN)Compiling Libft...$(RST)"
	@make -C $(LIBFT_DIR)
	@echo "$(GRNN)Libft ready √$(RST)\n"

# Rule for cleaning object files
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@clear
	@echo "$(REDD)Object files removed!$(RST)"

# Rule for cleaning the executable
fclean: clean
	@rm -f $(EXECUTABLE)
	@rm -f $(LIBFT)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@echo "$(REDD)Executable $(EXECUTABLE) removed!$(RST)"

# Rule for re-making everything
re: fclean all

# Default rule to build the executable
all:
	@echo "\n$(CYAN)Building $(EXECUTABLE)...$(RST)\n"
	@make $(EXECUTABLE)

.PHONY: all clean fclean re readline

# Norminette (readline exclue!)
norme:
	@/usr/local/bin/norminette -R CheckDefine $(INC_DIR) $(LIBFT_DIR) ./minishell.c $(SRC_FIRSTPARSE) $(SRC_PARSING) $(SRC_OPERATORS) $(SRC_CMD) $(SRC_BONUS) $(SRC_LEXING) $(SRC_MNSH) $(SRC_UTILS) | sed "s/Error/[1;31m&/; s/line:/[0m&/; s/$$/[0m/; s/OK!/[1;32m&/; s/KO/[1;31m&/; s/(/[0m&/"
	@echo "\n\033[1;32m---------------------------------\033[0m\n"
	@/usr/local/bin/norminette -R CheckDefine $(INC_DIR) $(LIBFT_DIR) ./minishell.c $(SRC_FIRSTPARSE) $(SRC_PARSING) $(SRC_OPERATORS) $(SRC_CMD) $(SRC_BONUS) $(SRC_LEXING) $(SRC_MNSH) $(SRC_UTILS) | awk '/^Error:/ {errorCount++} /OK/ {count++} END {total = NR - errorCount; if (count == total) {print "\033[1;32m\tOK: " count " / " total " total\033[0m"} else {print "\033[1;31m\tKO: " count " / " total " total\033[0m"}}'
	@echo "\n\033[1;32m---------------------------------\033[0m\n"
