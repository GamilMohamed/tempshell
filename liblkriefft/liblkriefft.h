/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblkriefft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:50:07 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 03:00:59 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef liblkriefft_H
# define liblkriefft_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

/*********************/
/******MANDATORY******/
/*********************/

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s1, int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsiz);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsiz);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

/*********************/
/********BONUS********/
/*********************/

typedef struct s_list
{
	void			*content;
	int				precedence;
	struct s_list	*next;
}t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
int	ft_lstbelongs(t_list *lst, void *does_it, int (*cmp)(void *, void *), int (*len)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstpop(t_list **lst);
int		ft_lstsize(t_list *lst);
void	ft_lstprint(t_list *lst);

/*********************/
/****GET_NEXT_LINE****/
/*********************/

# ifndef GET_NEXT_LINE_H
#  define GET_NEXT_LINE_H

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 1000
#  endif

void	ft_reset_buff(char *buff);
char	*ft_strjoin_gnl(char const *res, char const *buff);
void	aux_gnl(char **res, char *buff);
char	*one_line(char *buff, int fd);
char	*get_next_line(int fd);

# endif

#endif
