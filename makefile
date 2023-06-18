NAME = minishell

FLAGS = -Wall -Wextra
FLAGS += -Werror
# FLAGS += -g -fsanitize=address
SRC_DIR = src
OBJ_DIR = obj
MAKE_FILE = makefile
INC_DIR = includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_LIB = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline

EXECUTE_FI	=	executor_dcs.c \
				executor_utils.c \
				commands.c \
				daycare.c \
				execve_utils.c \
				envp.c \
				envp_utils.c \
				redirect.c \
				heredoc_dcs.c
				
				
BUILTIN_FI  =	builtin.c \
				builtin_utils.c \
				echo.c \
				cd.c \
				exit.c \
				env.c \
				pwd.c \
				unset.c \
				export.c \
				export_utils.c

MAIN_FILES =	main.c \
				line_input.c 

PARSER_FILES =	lexer.c \
				lexer_util.c \
				parser.c \
				parse_list.c \
				parser_util.c \
				parser_util2.c \
				parser_util3.c \
				list.c \
				list_util.c \
				specialchar.c \
				expander.c \
				expander_util.c \
				signals.c \
				signals_util.c \
				syntax.c \
				util.c

SRC_FILES =		$(addprefix main/, $(MAIN_FILES)) \
				$(addprefix executor/, $(EXECUTE_FI)) \
				$(addprefix builtin/, $(BUILTIN_FI)) \
				$(addprefix parser/, $(PARSER_FILES))

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

INC = -I $(INC_DIR)


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MAKE_FILE)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INC) $(READLINE_INC) -c -o $@ $<

#libft
$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(OBJDIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

run: all
	./minishell
