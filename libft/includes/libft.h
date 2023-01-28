/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:25:30 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/28 01:24:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/*	PERSO/			*/
int		ft_printf(const char *format, ...);
// char				*get_next_line(int fd, int boolean);
void	ft_swap(void *a, void *b, int size);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_freetab(char **tab);
void	*ft_free(void **ptr);
char	*ft_strcpy(char *dst, char *src);
char	*ft_realloc(char *s1, char *s2);
int		ft_checkchars(char c, char c1, char c2, char c3);
int		ft_isspace(int c);

// char				*ft_realloc(char *s1, char const *s2);
void	ft_printtab(char **tab);
char	*ft_strcat(char *dest, char *src);
int		ft_countdelim(char const *str, char *charset);
// int		ft_countdelim(char const *str, char c);

/*	IS/				*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
/*	TO/				*/
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
/*	MEM/			*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
/*	STR/			*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(char const *s, int c);
char	*ft_strrchr(char const *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(char const *haystack, char const *needle, size_t len);
char	*ft_strtrim(char const *s, char const *set);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char *charset, int *size);
// char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
/*	PUT/			*/
// void				ft_putchar_fd(char c, int fd);
// void				ft_putendl_fd(char const *s, int fd);
// void				ft_putnbr_fd(int n, int fd);
// void				ft_putstr_fd(char const *s, int fd);

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_list;
// /*	LST					*/
// t_list				*ft_lstnew(void *content);
// void				ft_lstadd_front(t_list **lst, t_list *new);
// int					ft_lstsize(t_list *lst);
// t_list				*ft_lstlast(t_list *lst);
// void				ft_lstadd_back(t_list **lst, t_list *new);
// void				ft_lstdelone(t_list *lst, void (*del)(void *));
// void				ft_lstclear(t_list **lst, void (*del)(void *));

#endif
