NAME = minishell

FLAGS = -Wall -Werror -Wextra -g -MMD
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_LIB = -lreadline

SRCFILES =	main.c \
			lexer.c

SRC = $(addprefix $(SRC_DIR)/, $(SRCFILES))

OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

INC = -I $(INC_DIR)

DEP = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INC) $(READLINE_INC) -c -o $@ $<

-include $(DEP)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
