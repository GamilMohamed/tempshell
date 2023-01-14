#ifndef MINITREES_H
# define MINITREES_H

# include "../liblkriefft/liblkriefft.h"
# include "minitrees_structs.h"

// lst_utils.c
t_list *ft_lstnew_rpn(void *content, int precedence);
void	ft_lstappendcopy(t_list **lst, t_list *copy);
char	*ft_match_list(char *str, t_list *lst);
int	is_a_closed_parenthesis(char *str);

// make_tree.c
t_btree	*get_tree(char *str, char **env, t_data *data);
// t_btree	*get_tree(char *str);

// print_trees.c
void	bfs(t_queue **trees, t_queue **to_print);
int	get_local_depth(t_queue *to_print);
int	get_depth(t_queue *to_print);
void	print_print(t_queue *to_print, int node_size);
void	print_tree(t_btree *t, int node_size);

// queues.c
t_queue	*new_queue(void *data, int id);
void	add_queue(t_queue **queue, t_queue *add);
t_btree	*pop(t_queue **trees);
void	print_queue(t_queue *q);

// rpn_algo.c
int	rpn_isspecial(t_rpn *rpn, int i);
char	*rpn_handle_parenthesis(t_rpn *rpn);
char	*rpn_handle_operators(t_rpn *rpn);
char	*rpn_isspecialtreatment(t_rpn *rpn);
t_rpn	*generate_rpn(t_rpn *rpn, char *str);

// rpn_basics.c
void	init_rpn(t_rpn *rpn, char *to_parse);
void	free_rpn(t_rpn *rpn);
char	*invert_quotes(char *s);
t_rpn	*rpn(t_rpn *rpn, char *str);

// rpn_pop_utils.c
char	*rpn_pop_ops(t_rpn *rpn);
char	*rpn_popending(t_rpn *rpn);
void	rpn_pop_opsdel(t_rpn *rpn);

// trees.c
t_btree	*new_tree(void *node, t_data *data);
void	add_left(t_btree **tree, t_btree *left_son);
void	add_right(t_btree **tree, t_btree *right_son);
void	free_tree(t_btree *t);

// exec.c
int	exec_command(t_btree *tree, int infile, int outfile, char **ev);
int	exec_tree(t_btree *tree, int infile, int outfile, char **ev);

#endif