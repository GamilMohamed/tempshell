NAME			=	minishell

LIBFT			=	libft.a liblkriefft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c split.c builtin.c expand.c syntax.c wildcard.c signals.c \
				rpn/rpn_algo.c \
				rpn/rpn_basics.c \
				rpn/rpn_pop_utils.c \
				rpn/rpn_utils.c rpn/rpn_algo_bis.c \
				parsing/is_something.c	parsing/parsing.c  parsing/parsing_utils.c\
				trees/make_tree.c \
				trees/trees.c \
				trees/print_tree/print_trees.c \
				trees/print_tree/queues.c \
				exec/exec.c exec/utils.c exec/freeutils.c exec/space.c exec/error.c  exec/utils_exec.c \
				exec/files.c exec/free_all.c \
				builtins/cd.c  \
				builtins/env_utils.c \
				builtins/export.c \
				error_handler/error.c \
				builtins/unset.c \
				here_doc/here_doc.c


OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft/includes -Iliblkriefft

LIB				=	-lreadline -lm -Llibft -lft -Lliblkriefft -llkriefft

CC				=	cc

CDFLAGS 		= -MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	make -C libft
	make -C liblkriefft
	$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/trees/print_tree
	mkdir -p objs/rpn
	mkdir -p objs/builtins
	mkdir -p objs/parsing
	mkdir -p objs/error_handler
	mkdir -p objs/here_doc
	mkdir -p objs/exec
	mkdir -p here_doc/

clean:
	make clean -C libft
	make clean -C liblkriefft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	make fclean -C liblkriefft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

leaks: ${NAME}
	valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

leask: $(NAME)
	valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell


env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
# .SILENT: