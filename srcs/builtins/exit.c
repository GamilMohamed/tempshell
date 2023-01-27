/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:03:54 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 14:12:55 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoll(const char *str)
{
	int			i;
	int			y;
	long long	res;

	i = 0;
	y = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			y = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res * y);
}

// static void	exit_msg(const char *tmp, t_data *data)
// {
// 	ft_printf("bash: exit: %s: numeric argument required\n", tmp);
// 	free_shell(data);
// 	exit(2);
// }

// int	is_exit(t_data *data, char **argument)
// {
// 	const char	*tmp;
// 	long long	res;
// 	int			index;
// 	int			a;

// 	if (!argument || !*argument)
// 		return (ft_putendl("exit"), 0);
// 	index = 0;
// 	while (argument[++index])
// 	{
// 		tmp = argument[index];
// 		res = ft_atoull(tmp);
// 		if (*tmp == '+' || *tmp == '-')
// 			tmp++;
// 		while (ft_isdigit(*tmp))
// 			tmp++;
// 		if (index > 1)
// 			return (ft_printf("exit\nbash: exit: too many arguments\n"),
// 					update_status_code(data, 127),
// 					0);
// 		if (*tmp != '\0' || res > LLMAX || res < LLMIN)
// 			exit_msg(tmp, data);
// 	}
// 	ft_putendl("exit");
// 	a = EXIT_SUCCESS;
// 	if (argument[1] != NULL)
// 		a = ft_atoull(argument[1]) % 256;
// 	free_shell(data);
// 	exit(a);
// }

void	freenexit(t_data *data, t_cmd *cmd, int val, char **tab)
{
	ft_errorcmd(data, cmd, cmd->redi, NULL);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->copyfd);
	ft_freetab(tab);
	exit(val);
}

static int	allgood(t_data *data, t_cmd *cmd, char *str, char **tab)
{
	int	ret;

	if (data->nbcmd == 1)
		printf("exit\n");
	ret = 0;
	if (str)
		ret = ft_atoll(str) % 256;
	ft_printf("ret=%i\n", ret);
	return (freenexit(data, cmd, ret, tab), 1);
}

int	ft_exit(t_data *data, t_cmd *cmd, char **tab)
{
	int			i;
	char		*tmp;
	long long	ret;

	ft_printtab(tab);
	i = -1;
	ret = 0;
	if (!tab)
		return (printf("Error\n"));
	while (tab[++i])
	{
		tmp = tab[i];
		ret = ft_atoll(tmp);
		printf("ret:%lli\n", ret);
		if (*tmp == '+' || *tmp == '-')
			tmp++;
		while (ft_isdigit(*tmp))
			tmp++;
		if (i > 1)
			return (printf("exit\nbash: exit: too many arguments\n"), data->status);
		if (*tmp)
			return (printf("bash: exit: %s: numeric argument required\n",
					tab[i]), freenexit(data, cmd, 2, tab), 1);
	}
	return (allgood(data, cmd, tab[0], tab));
}
