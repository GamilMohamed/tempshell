SRCS		=	ft_put_fd/ft_putchar_fd.c \
				ft_put_fd/ft_putendl_fd.c \
				ft_put_fd/ft_putnbr_fd.c \
				ft_put_fd/ft_putstr_fd.c \
				is_something/ft_isalnum.c \
				is_something/ft_isalpha.c \
				is_something/ft_isascii.c \
				is_something/ft_isdigit.c \
				is_something/ft_isprint.c \
				mem/ft_memchr.c \
				mem/ft_memcmp.c \
				mem/ft_memcpy.c \
				mem/ft_memmove.c \
				mem/ft_memset.c \
				str/ft_strchr.c \
				str/ft_strcmp.c \
				str/ft_strndup.c \
				str/ft_striteri.c \
				str/ft_strjoin.c \
				str/ft_strlcat.c \
				str/ft_strlcpy.c \
				str/ft_strlen.c \
				str/ft_strmapi.c \
				str/ft_strncmp.c \
				str/ft_strnstr.c \
				str/ft_strrchr.c \
				str/ft_strtrim.c \
				str/ft_substr.c \
				to_something/ft_tolower.c \
				to_something/ft_toupper.c \
				utils/ft_atoi.c \
				utils/ft_bzero.c \
				utils/ft_calloc.c \
				utils/ft_itoa.c \
				utils/ft_split.c \
				lst/ft_lstadd_back.c \
				lst/ft_lstadd_front.c \
				lst/ft_lstclear.c \
				lst/ft_lstdelone.c \
				lst/ft_lstiter.c \
				lst/ft_lstlast.c \
				lst/ft_lstmap.c \
				lst/ft_lstnew.c \
				lst/ft_lstpop.c \
				lst/ft_lstprint.c \
				lst/ft_lstsize.c \
				get_next_line/get_next_line.c

OBJS		= 	${SRCS:.c=.o}
INCLUDE		= 	-I.
NAME		= 	liblkriefft.a
CC			= 	cc
RM			= 	rm -f
CFLAGS		= 	-Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
.SILENT: