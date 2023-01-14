/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:12:39 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/14 02:47:18 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

void	ft_reset_buff(char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	while (buff[i])
		buff[j++] = buff[i++];
	buff[j] = '\0';
}

char	*ft_strjoin_gnl(char const *res, char const *buff)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (buff[0] == 0)
		return (NULL);
	if (res == NULL)
		join = malloc(sizeof(*join) * (ft_strlen(buff) + 1));
	else
		join = malloc(sizeof(*join) * (ft_strlen(res) + \
			ft_strlen(buff) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (res && res[i])
		join[j++] = res[i++];
	i = 0;
	while (buff[i] && buff[i] != '\n')
		join[j++] = buff[i++];
	if (buff[i] == '\n')
		join[j++] = '\n';
	join[j] = '\0';
	return (join);
}

void	aux_gnl(char **res, char *buff)
{
	char	*tmp;

	tmp = *res;
	*res = ft_strjoin_gnl(*res, buff);
	if (tmp)
		free(tmp);
}

char	*one_line(char *buff, int fd)
{
	int		ret;
	char	*res;

	res = NULL;
	ret = 0;
	aux_gnl(&res, buff);
	if (!ft_strchr(buff, '\n'))
		ret = read(fd, buff, BUFFER_SIZE);
	while (ret && !ft_strchr(buff, '\n'))
	{
		buff[ret] = '\0';
		aux_gnl(&res, buff);
		ret = read(fd, buff, BUFFER_SIZE);
	}
	if (ret)
	{
		buff[ret] = '\0';
		aux_gnl(&res, buff);
	}
	ft_reset_buff(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	return (one_line(buff, fd));
}
