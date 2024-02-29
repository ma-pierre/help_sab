NAME = minishell

SRC = main.c\
	end_program.c\
	Env/dup_env_data.c\
	Utils/ft_split.c\
	Utils/ft_strchr.c\
	Utils/ft_strcmp.c\
	Utils/ft_strdup.c\
	Utils/ft_strjoin.c\
	Utils/ft_strlen.c\
	Cmd_table/fill_cmd_list.c\
	#Cmd_table/cmd_per_node.c\
	Signals/signals.c\
	Exec/check_cmd.c\
	Exec/executor.c\
	Exec/find_path.c\
	Builtins/cd.c\
	Builtins/echo.c\
	Builtins/env.c\
	Builtins/exit.c\
	Builtins/export.c\
	Builtins/pwd.c\
	Builtins/unset.c\
	error_handler.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -c $< -o $@

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
