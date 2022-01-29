NAME = minishell
SRCS = 	./builtins/builtin_cd.c 	\
		./builtins/builtin_env.c 	\
		./builtins/builtin_env_utils.c \
		./builtins/builtin_pwd.c 	\
		./builtins/builtin_unset.c 	\
		./builtins/builtin_export.c \
		./builtins/builtin_export_utils.c \
		./builtins/builtin_export_utils2.c \
		./builtins/builtin_echo.c 	\
		./exec/exec_cmd.c			\
		./exec/exec_cmd2.c			\
		./exec/exec_cmd3.c			\
		./exec/exec_utils.c			\
		./exec/redir.c				\
		./exec/pipe.c				\
		./signal_handler/signal.c 	\
		./parsing/parsing.c			\
		./parsing/parsing2.c			\
		./parsing/quote.c			\
		./parsing/split_spaces.c 	\
		./parsing/replace_arg.c 	\
		./parsing/add_list.c		\
		./parsing/clear_parsing.c	\
		./parsing/utils_parse.c		\
		./parsing/utils_parse2.c	\
		./parsing/remove_empty.c	\
		./bonus/wildcard.c			\
		./bonus/wildcard_utils.c	\
		./main/main.c						\
		./main/main2.c						\
		./main/main3.c						\
		./utils/utils.c						\
		./utils/utils2.c					\
		./utils/utils3.c					\

OBJS = ${SRCS:.c=.o}
COMP = gcc #-g #-g3 -fsanitize=address
FLGS = -Wall -Wextra -Werror
INCL = -I . -I./libft
LIBR = -L ./libft -lft -lreadline
HEAD = minishell.h
LIBS = ./libft

all: libft ${NAME}

libft:
	make -C libft

${NAME}: ${OBJS} ./libft/libft.a
	${COMP} ${FLGS} ${OBJS} ${INCL} ${LIBR} -o $@ 

%.o: %.c ${HEAD}
	${COMP} ${FLGS} ${INCL} -o $@ -c $<

clean:
	rm -rf ${OBJS}
	make clean -C libft

fclean: clean
	rm -rf ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re libft
