NAME		= minishell
SRCFILES	= main.c lexer.c
OBJDIR		= obj
VPATH		= src
LIBFT		= lib/libft
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
OBJ			= $(addprefix obj/, $(SRCFILES:.c=.o))
INC			= $(addprefix -I , \
			  lib/libft)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	$(CC) -g -fsanitize=address -o $@ $^

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(INC) -o $@ $^

$(LIBFT)/libft.a: 
	make bonus -C $(LIBFT)

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT)

fclean:
	make clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)

re:
	make fclean
	make
