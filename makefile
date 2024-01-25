NAME = minishell

MINISHELL = minishell.a

FILES = src/minishell.c\
src/prompt.c\
src/builtins/builtins.c\
src/builtins/env_utils/get_path.c\

OBJECTS = $(FILES:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./Libft/libft.a

LIB_SYS = -Iinclude -lglfw -L "/Users/etornay-/.brew/opt/glfw/lib/"

$(NAME):			$(OBJECTS) $(LIBFT)
						ar rcs $(MINISHELL) $(OBJECTS)
						gcc $(FLAGS) $(MINISHELL) $(LIBFT) $(LIB_SYS) -o $(NAME) -lreadline

$(OBJECTS):			src/%.o : src/%.c
						gcc $(FLAGS) -c $< -o $@

$(LIBFT):
					make -s -C ./Libft

all:				$(NAME)

clean:
					@ rm -f $(OBJECTS)
					@ make clean -s -C ./Libft

fclean:
					@ rm -f $(NAME) $(OBJECTS) $(MINISHELL) $(LIBFT)
					@ make fclean -s -C ./Libft

re:					fclean all

.PHONY: all re clean fclean