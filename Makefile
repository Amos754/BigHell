NAME 		= minishell
CC 			= gcc
CFLAGS 		= -g3 -g -fsanitize=address #-Wall -Wextra -Werror
RDLN_FLAG	= -L/Users/olmarech/.brew/opt/readline/lib -I/Users/olmarech/.brew/opt/readline/include -lreadline


RED			= \033[1;31m
BLUE		= \033[1;34m
PURPLE		= \033[0;95m
GREEN		= \033[0;32m
RESET		= \033[0m
CYAN		= \033[0;96m
YELLOW		= \033[0;93m

SRC			= execution/builtins/cd.c	\
			  execution/builtins/cd_utils.c	\
			  execution/builtins/echo.c	\
			  execution/builtins/env.c	\
			  execution/builtins/exit.c	\
			  execution/builtins/export.c	\
			  execution/builtins/export_utils.c	\
			  execution/builtins/export_utils2.c	\
			  execution/builtins/export_utils3.c	\
			  execution/builtins/ft_strncmp.c	\
			  execution/builtins/ft_strnstr.c	\
			  execution/builtins/pwd.c	\
			  execution/builtins/unset.c	\
			  execution/utils/ft_strjoin.c	\
			  execution/utils/pipe_utils.c	\
			  execution/utils/pipe_utils2.c	\
			  execution/utils/exit_utils.c	\
			  execution/utils/utils_simple_cmd.c	\
			  execution/utils/utils_simple_cmd2.c	\
			  execution/utils/utils_simple_cmd3.c	\
			  execution/utils/utils_simple_cmd4.c	\
			  execution/env_init.c	\
			  execution/main_executor.c	\
			  execution/pipe_exec.c	\
			  execution/redirection_handler.c	\
			  execution/simple_cmd.c	\
			  lexycal_analysis/lexer.c	\
			  lexycal_analysis/list.c	\
			  lexycal_analysis/quote_utils.c	\
			  lexycal_analysis/replace_quote.c	\
			  lexycal_analysis/utils1.c	\
			  lexycal_analysis/utils2.c	\
			  lexycal_analysis/utils3.c	\
			  lexycal_analysis/utils7.c	\
			  syntax_analysis/get_next_line.c	\
			  syntax_analysis/get_next_line_utils.c	\
			  syntax_analysis/parsing_table.c	\
			  syntax_analysis/stack1.c	\
			  syntax_analysis/stack2.c	\
			  syntax_analysis/syntax.c	\
			  syntax_analysis/tree.c	\
			  syntax_analysis/utils4.c	\
			  syntax_analysis/utils5.c	\
			  syntax_analysis/utils6.c	\
			  signals.c	\
			  main.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@echo "$(YELLOW)Generating minishell objects$(RESET)"
	@${CC} ${CFLAGS} -c $< -o $@


all: cute ${NAME}

${NAME}: $(OBJ)
		@echo "$(CYAN)███████████████████████$(PURPLE) Making minishell $(CYAN)███████████████████████$(RESET)"
		@$(CC) $(CFLAGS) $(RDLN_FLAG) -lm $(SRC) -o $(NAME)
		@echo "$(CYAN)███████████████████████$(GREEN) Compiling is DONE $(CYAN)██████████████████████$(RESET)"

clean:
		@echo "$(RED)deleting$(RESET) object files"
		@rm -rf $(OBJ)

fclean: clean
		@echo "$(RED)deleting$(RESET) MINIHELL"
		@rm -rf $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re

cute:
	@echo "███╗   ███╗██╗███╗   ██╗██╗   $(RED)██╗  ██╗███████╗██╗     ██╗     $(RESET)"
	@echo "████╗ ████║██║████╗  ██║██║   $(RED)██║  ██║██╔════╝██║     ██║     $(RESET)"
	@echo "██╔████╔██║██║██╔██╗ ██║██║   $(RED)███████║█████╗  ██║     ██║     $(RESET)"
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║   $(RED)██╔══██║██╔══╝  ██║     ██║     $(RESET)"
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║   $(RED)██║  ██║███████╗███████╗███████╗$(RESET)"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   $(RED)╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(RESET)"
	@echo "         Made by : \033[1;91mabolor-e\033[m and \033[1;91molmarech\033[m"