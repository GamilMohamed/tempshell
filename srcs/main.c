/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:43 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/28 01:35:10 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strxdup(const char *s1)
{
	int		len;
	int		i;
	char	*new;

	len = 0;
	i = -1;
	if (!s1)
		return (ft_calloc(1, 1));
	while (s1[len])
		len++;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}

char	*prompt(t_data *data)
{
	char	*str;
	char	prompt[PATH_MAX] = "lol";
	char	**tab;
	int		count;

	str = ft_strxdup(ft_ev_getvar("PWD", data->env));
	tab = ft_split(str, "/", & count);
	if (data->status)
		ft_strcpy(prompt, RED);
	else
		ft_strcpy(prompt, GREEN);
	if (count)
		ft_strcat(prompt, tab[count - 1]);
	else
		ft_strcat(prompt, str);
	ft_strcat(prompt, "minishell");
	ft_strcat(prompt, "\001\033[0m\002:");
	free_all(1, 1, &str, tab);
	return (readline(prompt));
}

void	pre_exec(t_data *data)
{
	t_btree	*tree;
	t_btree	*temp;
	int		i;

	here_doc(data, data->str);
	tree = get_tree(data->str, data->env, data);
	ft_free((void **)&data->str);
	if (tree)
	{
		temp = tree;
		exec_tree(tree, temp);
		free_tree(tree);
	}
	i = -1;
	while (++i < data->nb_here)
		close(data->here[i].pipe[0]);
	freestruct(data);
	ft_freetab(data->path);
	ft_getenv(data->env, data);
}

int	exec(t_data *data)
{
	t_here	here;

	while (1)
	{
		data->str = prompt(data);
		if (!data->str)
			break ;
		add_history(data->str);
		if (syntax(data, data->str) == 1)
			continue ;
		if (syntax(data, data->str) == 2)
			break ;
		data->here = &here;
		pre_exec(data);
	}
	free_all(1, 2, &data->str, data->path, data->env);
	ft_printf("exit\n");
	rl_clear_history();
	return (0);
}

void	init(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->prev_pipes = -1;
	data->env = ft_copy_tab(env);
	ft_getenv(data->env, data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	init(data, env);
	exec(data);
	exit(data->status);
}
