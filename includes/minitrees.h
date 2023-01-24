#ifndef MINITREES_H
# define MINITREES_H

# include "../liblkriefft/liblkriefft.h"
# include "minitrees_structs.h"

/*******************************/
/*************TREES*************/
/*******************************/

// make_tree.c
char	**ft_getenv(char **envp, t_data *data);
t_list	*ft_isoperator_treatment(t_data *data, t_list *out, t_list **addr_list);
void	*add_tree_to_list(t_list	*out, t_data *data, t_list **addr_list);
t_list	*get_tree_treatment(char *str, t_rpn rpn_var, t_data *data);
t_btree	*get_tree(char *str, char **env, t_data *data);

// trees.c
t_btree	*new_tree(void *node, t_data *data);
void	add_left(t_btree **tree, t_btree *left_son);
void	add_right(t_btree **tree, t_btree *right_son);
void	*free_tree(t_btree *t);


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

/*******************************/
/**************RPN**************/
/*******************************/

// rpn_algo_bis.c
int	rpn_isspecial(t_rpn *rpn, int i);
void	*rpn_handle_parenthesis(t_rpn *rpn);

// rpn_algo.c
void	*rpn_handle_operators(t_rpn *rpn);
void	*rpn_isspecialtreatment(t_rpn *rpn);
void	*rpn_generate_treatment_bis(t_rpn *rpn, int *i, int j);
void	*rpn_generate_treatment(t_rpn *rpn, int *i, int j);
t_rpn	*generate_rpn(t_rpn *rpn, char *str);

// rpn_basics.c
void	*init_rpn_aux(t_rpn *rpn, char *to_parse);
void	*init_rpn(t_rpn *rpn, char *to_parse);
void	free_rpn(t_rpn *rpn);
char	*invert_quotes(char *s);
t_rpn	*rpn(t_rpn *rpn, char *str);

// rpn_pop_utils.c
char	*rpn_pop_ops(t_rpn *rpn);
char	*rpn_popending(t_rpn *rpn);
void	rpn_pop_opsdel(t_rpn *rpn);

// rpn_utils.c
t_list	*ft_lstnew_rpn(void *content, int precedence);
void	*ft_lstappendcopy(t_list **lst, t_list *copy);
char	*ft_match_list(char *str, t_list *lst);
int	is_a_closed_parenthesis(char *str);
char	*ft_strndup(const char *s1, int n);

/*********************************/
/*************PARSING*************/
/*********************************/

// is_something.c
int	is_redirection(char *str, int n);
int	is_special_token(char *str, int n);
int	is_parenthesis(char *str);
int	is_special(char *str, int n);
int	is_blank(char *str);

// parsing.c
void	*is_special_parsing(t_parser *p);
void	*is_not_special_parsing(t_parser *p);
void	*next_is_null_parsing(t_parser *p);
void	*parse_check(t_parser *p);
char	*parsing(char *str);

// parsing_utils.c
int	get_token(char *str);
void	*init_parser(t_parser *parser, char *str);
void	*parse_error(char *str);

/*********************************/
/*************BUILTINS************/
/*********************************/

// cd.c
char	*get_homepath(char **av, char **ev);
char	*ft_getpath(char **av, char **ev);
int	change_directory(char *new_pwd, char ***addr_ev);
int	ft_cd(char **av, char ***addr_ev);

// env_utils_bis.c
int	ft_tablen(char **tab);
void	ft_swap_ev(char **tab, int i, int j);

// env_utils.c
char	**ft_copy_tab(char **tab);
char	**regenerate_ev(int len, int index, char **ev);
int	ft_ev_getvarindex(char *var, char **ev);
char	*ft_ev_getvar(char *var, char **ev);
char	*ft_ev_setvar(char *var_name, char *str, char ***addr_ev);

// export.c
char	**ft_sorted_ev(char **ev);
int	ft_display_ordered_ev(char **ev);
int	export_check_valid_name(char *str);
int	ft_export_var(char *str, char ***addr_ev);
int	ft_export(char **av, char ***addr_ev);

// unset.c
int	ft_unset(char **tab, char ***addr_ev);

/*******************************/
/*************ERROR*************/
/*******************************/

// error.c
void	*ft_puterror(int flag, void *param);

/*************/
/*************/
/*************/

// exec.c
// int	exec_command(t_btree *tree, int infile, int outfile, char **ev);
// int	exec_command(t_btree *tree);
// int	exec_tree(t_btree *tree);
int	exec_command(t_btree *tree, t_btree *head);
int	exec_tree(t_btree *tree, t_btree *head);
// int	exec_tree(t_btree *tree, int infile, int outfile, char **ev);

#endif