# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 20:50:14 by mgamil            #+#    #+#              #
#    Updated: 2023/01/14 12:08:30 by mgamil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

DIR_SRCS	=	srcs
DIR_PTF		=	printf
DIR_GNL		=	gnl
DIR_PERSO	=	perso
DIR_TO		=	to
DIR_IS		=	is
DIR_MEM		=	mem
DIR_PUT		=	put
DIR_STR		=	str
DIR_LST		=	lst
DIR_OBJS	=	objs

SRCS 		= 																																																																\
$(DIR_GNL)/get_next_line.c	$(DIR_GNL)/get_next_line_utils.c																																																				\
$(DIR_PTF)/ft_printf.c		$(DIR_PTF)/ft_printf_utils.c	$(DIR_PTF)/ft_printf_colors.c																																													\
$(DIR_MEM)/ft_calloc.c		$(DIR_MEM)/ft_bzero.c			$(DIR_MEM)/ft_memset.c																																															\
$(DIR_PERSO)/ft_swap.c		$(DIR_PERSO)/ft_freetab.c		$(DIR_PERSO)/ft_strcpy.c $(DIR_PERSO)/ft_strcmp.c	$(DIR_PERSO)/ft_free.c	$(DIR_PERSO)/ft_checkchars.c	${DIR_PERSO}/ft_realloc.c	${DIR_PERSO}/ft_printtab.c	${DIR_PERSO}/ft_strcat.c																			\
$(DIR_TO)/ft_atoi.c			$(DIR_TO)/ft_tolower.c			$(DIR_TO)/ft_toupper.c		$(DIR_TO)/ft_itoa.c																																									\
$(DIR_IS)/ft_isalpha.c		$(DIR_IS)/ft_isascii.c			$(DIR_IS)/ft_isalnum.c		$(DIR_IS)/ft_isdigit.c	$(DIR_IS)/ft_isprint.c																																		\
$(DIR_STR)/ft_strlcpy.c		$(DIR_STR)/ft_split.c		$(DIR_STR)/ft_strchr.c			$(DIR_STR)/ft_strdup.c		$(DIR_STR)/ft_strjoin.c	$(DIR_STR)/ft_strlen.c		$(DIR_STR)/ft_strncmp.c		$(DIR_STR)/ft_strnstr.c		$(DIR_STR)/ft_strrchr.c	$(DIR_STR)/ft_strtrim.c	$(DIR_STR)/ft_substr.c	\
# $(DIR_LST)/ft_lstnew.c		$(DIR_LST)/ft_lstadd_front.c	$(DIR_LST)/ft_lstsize.c		$(DIR_LST)/ft_lstlast.c	$(DIR_LST)/ft_lstadd_back.c	$(DIR_LST)/ft_lstdelone.c	$(DIR_LST)/ft_lstclear.c																			\
# $(DIR_PUT)/ft_putchar_fd.c	$(DIR_PUT)/ft_putendl_fd.c		$(DIR_PUT)/ft_putnbr_fd.c	$(DIR_PUT)/ft_putstr_fd.c																																							\

SOURCES_PREFIXED	=	$(addprefix $(DIR_SRCS)/, $(SRCS))
OBJS				=	$(subst $(DIR_SRCS), $(DIR_OBJS), $(SOURCES_PREFIXED:.c=.o))

INCLUDES	=	-Iincludes
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3


all:		$(NAME)

$(DIR_OBJS)/%.o :	$(DIR_SRCS)/%.c
			mkdir -p $(DIR_OBJS)/$(DIR_PTF)
			mkdir -p $(DIR_OBJS)/$(DIR_GNL)
			mkdir -p $(DIR_OBJS)/$(DIR_PERSO)
			mkdir -p $(DIR_OBJS)/$(DIR_TO)
			mkdir -p $(DIR_OBJS)/$(DIR_IS)
			mkdir -p $(DIR_OBJS)/$(DIR_MEM)
			mkdir -p $(DIR_OBJS)/$(DIR_PUT)
			mkdir -p $(DIR_OBJS)/$(DIR_STR)
			mkdir -p $(DIR_OBJS)/$(DIR_LST)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)

clean:
			rm -rf $(OBJS)
			rm -rf $(DIR_OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re leaks
.DEFAULT:
.SILENT: