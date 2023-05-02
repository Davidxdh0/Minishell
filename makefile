NAME = minishell

FLAGS =  -Wall -Wextra
# FLAGS += -Werror 
# FLAGS += -g -fsanitize=address
SRC_DIR = src
OBJ_DIR = obj
MAKE_FILE = makefile
INC_DIR = includes
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_LIB = -lreadline

EXECUTE_FI	=	executor.c \
				file.c \
				paths.c \
				errors.c \
				redirect.c \
				builtin.c \
				messages.c \
				executor_dcs.c \
				builtin_dcs.c \
				heredoc_dcs.c \
				clean_exe.c
				
BUILTIN_FI  =	echo.c \
				cd.c \
				exit.c \
				export.c

MAIN_FILES =	main.c \
				line_input.c \
				argv_input.c

PARSER_FILES =	lexer.c \
				parser.c \
				list.c \
				specialchar.c \
				grammer_checker.c \
				expander.c

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
	lldb ./$(NAME) -- -p 'ls'

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