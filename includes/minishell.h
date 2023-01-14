/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:22 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/14 11:34:59 by mgamil           ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SPACES " \t\n\v"
# define METACHAR "<>;"
# define SQUOTE '\''
# define DQUOTE '\"'
# define SPACE ' '
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

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
int		ft_builtin(char *s, char **env);
// expand.c
char	*ft_expand(char *s, char **env);
int		checksyntax(char *s);
int		checkquotes(char *s);
int		checkagain(char *temp, int len);
int		isaredirection(char *s);

char	*ft_slash(char *path, char *cmd);
void	dupnclose(int fd, int std);
void	ft_lstadd_back_rr(t_rr **lst, t_rr *new);
t_rr	*ft_lstnewrr(char *content, int type);
void	ft_printlist(t_rr *temp);
char	*ft_wildcard(char *wildcards);


#endif