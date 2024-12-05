NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC  =	add_others.c	cheaks.c	echo.c	ft_split.c	lst_utils.c	parsing.c	tokenisation.c	utils2.c \
		add_redir.c		count_tokens.c	env.c	main.c	pwd.c	unset.c	utils3.c	bulitins_cmp.c	expand_util.c\
		cpy_to_arr.c    execution.c		join_my_shell.c		read_user_cmd.c  util_malloc.c   utils_export1.c \
		cd.c  creat_my_shell.c  export.c  libft1.c   syntax_error.c   utils1.c  utils_export2.c  exit.c  exec_utils1.c\
		multi_pipes.c	herdoc_expand.c 	ft_itoa.c  exec_utils2.c	expand_cmd_line.c   fork.c ft_malloc2.c	add_util1.c\
		signals.c	her_doc.c  exec_utils3.c	my_util.c\



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
							
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all clean

.SECONDARY:$(OBJ)
