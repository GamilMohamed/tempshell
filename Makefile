NAME			=	minishell

LIBFT			=	libft.a liblkriefft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c split.c builtin.c expand.c syntax.c wildcard.c cd.c \
				rpn/rpn_algo.c \
				rpn/rpn_basics.c \
				rpn/rpn_pop_utils.c \
				rpn/rpn_utils.c \
				trees/make_tree.c \
				trees/trees.c \
				trees/print_tree/print_trees.c \
				trees/print_tree/queues.c \
				exec/exec.c exec/utils.c \
				builtins/cd.c  \
				builtins/env_utils.c \
				builtins/export.c \
				builtins/unset.c 


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
	mkdir -p objs/exec

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
	valgrind --suppressions=ignore.txt -s --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
# .SILENT: