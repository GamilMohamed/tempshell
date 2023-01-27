/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:22 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 14:53:00 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../liblkriefft/liblkriefft.h"
# include "libft.h"
# include "minitrees.h"
# include "minitrees_structs.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SPACES " \t\n\v"
# define METACHAR "<>;"
# define SQUOTE '\''
# define DQUOTE '\"'
# define SPACE ' '
# define RESET "\001\033[0m\002"
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

/*
struct	dirent 
{
	ino_t d_ino;             // numéro d'inœud
	off_t d_off;             // décalage jusqu'à la dirent suivante
	unsigned short d_reclen; // longueur de cet enregistrement
	unsigned char d_type;    // type du fichier
	char d_name[256];        // nom du fichier 
};
*/

// split.c
char	**ft_splitex(char const *s);
// builtin.c
int	builtin_exit(t_data *data, t_cmd *cmd, char *str);
int	ft_exit(t_data *data, t_cmd *cmd, char **tab);
int		ft_builtin(t_cmd *cmd, t_data *data);
// int		ft_builtin(char *s, char **env, char ***addr_env);
// expand.c
char	*ft_expand(t_data *data, char *s);
int		checksyntax(char *s);
int		checkquotes(char *s);
int		checkagain(char *temp, int len);
int		isaredirection(char *s);

char	*ft_slash(char *path, char *cmd);
void	dupnclose(int fd, int std);
int		ft_lstadd_back_rr(t_rr **lst, t_rr *var);
t_rr	*ft_lstnewrr(char *content, int type);
void	ft_printlist(t_rr *temp);
char	*ft_wildcard(char *wildcards);
void	*ft_puterror(int flag, void *param);
// exec
int		exec_tree(t_btree *tree, t_btree *head);
char	*invert(char *str);
int	exec_builtin(t_cmd *cmd, t_data *data);
void	execute(t_data *data, t_cmd *cmd, int boolean);

//fork.c
void	ft_child(t_btree *tree, t_btree *head, t_cmd *cmd, int index);
void	ft_father(t_btree *tree, t_btree *head, t_cmd *cmd);
void	forker(t_btree *tree, t_btree *head, t_cmd *cmd, int i);
void	forking(t_data *data, int index, int max, t_cmd *cmd);
// exec_parse.c
char	*checkstring(t_cmd *cmd, char *str);

// free_utils.c
int		error_fd_bt(t_rr *node, t_data *data, t_cmd *cmd, int index);
void	ft_freerr(t_rr *node);
void	ft_errorcmd(t_data *data, t_cmd *cmd, t_rr *node, char *str);
// utils.c
void	ft_errorcmd_bt(t_data *data, t_cmd *cmd, t_rr *node, char *str);
// files.c
int		openfiles_bt(t_rr *node, t_data *data, t_cmd *cmd, int index);
void	openfiles(t_rr *node, t_data *data, t_cmd *cmd, int index);
// free_all.c
void	free_all(int s, int t, ...);
void	freestruct(t_data *data);

// space.c
char	*ft_spacestr(char *str);
// error.c
void	error_fd(t_rr *node, t_data *data, t_cmd *cmd, int index);
void	execve_error(t_data *data, char *str, char **tab, int boolean);
// utils_exec.c
void	exec_waitpid(t_data *data);
void	dupnclose(int fd, int std);
int		matching(char *match);

// heredoc
t_here	*here_doc(t_data *data, char *str);
// utils.c
int		get_len_word(char *str);
char	*get_word(char *str);
int		count_hd(char *str);

// char	*here_doc(t_here *here, t_data *data, char *str);
// char	*here_doc(t_data *data, char *str);
void	antislash(int sig);
t_data	*starton(void);
void	ctrlc(int sig);
int	syntax(t_data *data, char *str);
char	*ft_quote(char *str);

int	builtin_env(char *str, char **env);
char	*builtin_echo_expand(char *str, char **env);
int	builtin_echo_opt(char **tab, int *opt);
int	builtin_echo(char *s, char **env);
char	*builtin_pwd(char *s);
// char	*builtin_pwd(char *s, char **env);

int	lenof(int n);
void	ft_stoval(t_data *data, int n);
char	*dostatus(t_data *data, int *n, int *index);
char	*ft_boost(char *s1, char *s2, int size);


// signal.c
void	antislash(int sig);
void	ctrlc(int sig);

#endif