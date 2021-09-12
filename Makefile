# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/11 13:26:32 by lcouto            #+#    #+#              #
#    Updated: 2021/09/11 18:16:20 by lcouto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

INCLUDES	=	-I includes

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g -pthread
RM			=	/bin/rm -f

DIR_SRCS	=	sources
DIR_OBJS	=	objects

SRCS		=	$(DIR_SRCS)/main.c \
				$(DIR_SRCS)/ft_putendl_fd.c \
				$(DIR_SRCS)/ft_atoi.c \
				$(DIR_SRCS)/ft_atoll.c \
				$(DIR_SRCS)/ft_isdigit.c \
				$(DIR_SRCS)/error.c \

OBJS		=	$(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

ifeq ($(SANITIZE_A),true)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

ifeq ($(SANITIZE_L),true)
	CFLAGS += -fsanitize=leak -fno-omit-frame-pointer
endif

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.c
			@mkdir -p $(DIR_OBJS) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@echo "Compiled "$<" successfully!"

all:		$(NAME)

$(LIBFT):
			@make --no-print-directory -C $(LIBFT_DIR)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			@echo "created philo executable file successfully!"

clean:
			@$(RM) $(OBJS)
			@$(RM) -r $(DIR_OBJS)
			@echo "Cleanup completed!"

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re