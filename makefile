NAME = minishell

FLAGS =  -Wall -Wextra
# FLAGS += -Werror 
# FLAGS += -g -fsanitize=address
SRC_DIR = src
OBJ_DIR = obj
MAKE_FILE = makefile
INC_DIR = includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_LIB = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
# READLINE_LIB = -lreadline
# -L $(HOME)/.brew/Cellar/readline/8.2.1/lib 

EXECUTE_FI	=	executor_dcs.c \
				executor_utils.c \
				envp.c \
				heredoc_dcs.c \
				single_command.c
				
# executor.c
# messages.c
# file.c
# paths.c
# errors.c
# redirect.c
# builtin.c
				
BUILTIN_FI  =	builtin.c \
				builtin_utils.c \
				echo.c \
				cd.c \
				exit.c \
				env.c \
				pwd.c \
				unset.c \
				export.c

MAIN_FILES =	main.c \
				line_input.c \
				argv_input.c

PARSER_FILES =	lexer.c \
				parser.c \
				parser_util.c \
				parser_util2.c \
				list.c \
				specialchar.c \
				grammer_checker.c \
				expander.c \
				signals.c \
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

lldb: $(NAME)
	lldb ./$(NAME) -- -p 'ls' 'exit'

tests:

TEST_DIR =	tests

TEST =	$(TEST_DIR)/simple.c 

TEST_BIN =	unit-tests

tests_run:
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(TEST_BIN) $(SRC) $(TEST) $(READLINE_LIB)--coverage -lcriterion $(LDFLAGS) -g
	./$(TEST_BIN)
# gcc -o tests simple.c -lcriterion -I /Users/dyeboa/.brew/include

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(OBJDIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

test: all
	bash testcmd.sh

run: all
	./minishell

exp: all
	mv minishell ../SH_tester