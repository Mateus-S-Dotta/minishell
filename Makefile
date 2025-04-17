NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf

SRCS = main.c \
	   main_utils.c \
	   debug.c \
	   src/error.c \
	   src/env.c \
	   src/expand.c \
	   src/redirect.c \
	   src/redirect_utils.c \
	   src/command.c \
	   src/command_utils.c \
	   src/super_split.c \
	   src/super_split_utils.c \
	   src/super_split_utils_2.c \
	   src/unify_.c \
	   src/here_doc.c \
	   src/signals.c \
	   src/here_doc_utils.c \
	   builtins/builtins_utils.c \
	   builtins/ft_echo.c \
	   builtins/ft_pwd.c \
	   builtins/ft_env.c \
	   builtins/ft_cd.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(LIBFT_LIB)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)
		make clean -C libft

fclean: clean
		$(RM) $(NAME)
		make fclean -C libft

re: fclean all
