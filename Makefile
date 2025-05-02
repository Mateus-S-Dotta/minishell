# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 17:03:25 by lsilva-x          #+#    #+#              #
#    Updated: 2025/05/02 18:38:48 by lsilva-x         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf

# Libraries
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBS = -lreadline $(LIBFT_LIB)

# Directories
SRC_DIR = src
GC_DIR = $(SRC_DIR)/gc
UTILS_DIR = $(SRC_DIR)/utils
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
ENV_DIR = $(SRC_DIR)/env
HEREDOC_DIR = $(SRC_DIR)/heredoc
SIGNAL_DIR = $(SRC_DIR)/signal
BUILTINS_DIR = $(SRC_DIR)/builtins

SRCS_MAIN = main.c
SRCS_UTILS = $(UTILS_DIR)/main_utils.c \
             $(UTILS_DIR)/debug.c \
             $(UTILS_DIR)/get_next_line.c \
             $(UTILS_DIR)/error.c \
             $(UTILS_DIR)/function_utils.c
SRCS_ENV = $(ENV_DIR)/env.c \
           $(ENV_DIR)/env_file_utils.c \
           $(ENV_DIR)/env_functions.c
SRCS_LEXER = $(LEXER_DIR)/expand.c \
             $(LEXER_DIR)/super_split.c \
             $(LEXER_DIR)/super_split_utils.c \
             $(LEXER_DIR)/super_split_utils_2.c
SRCS_PARSER = $(PARSER_DIR)/redirect.c \
              $(PARSER_DIR)/redirect_utils.c \
              $(PARSER_DIR)/command.c \
              $(PARSER_DIR)/command_node.c \
              $(PARSER_DIR)/command_utils.c \
              $(PARSER_DIR)/unify_.c
SRCS_HEREDOC = $(HEREDOC_DIR)/here_doc.c \
               $(HEREDOC_DIR)/here_doc_utils.c
SRCS_SIGNAL = $(SIGNAL_DIR)/signals.c
SRCS_BUILTINS = $(BUILTINS_DIR)/builtins_utils.c \
                $(BUILTINS_DIR)/ft_echo.c \
                $(BUILTINS_DIR)/ft_pwd.c \
                $(BUILTINS_DIR)/ft_env.c \
                $(BUILTINS_DIR)/ft_cd.c \
                $(BUILTINS_DIR)/ft_export.c \
                $(BUILTINS_DIR)/export_utils.c \
                $(BUILTINS_DIR)/ft_unset.c \
                $(BUILTINS_DIR)/ft_exit.c
SRCS_GC = $(GC_DIR)/gc.c

SRCS = $(SRCS_MAIN) \
       $(SRCS_UTILS) \
       $(SRCS_ENV) \
       $(SRCS_LEXER) \
       $(SRCS_PARSER) \
       $(SRCS_HEREDOC) \
       $(SRCS_SIGNAL) \
       $(SRCS_BUILTINS) \
       $(SRCS_GC)

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libft