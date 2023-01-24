/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:06:41 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getenv(char **envp, t_data *data)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (!data->path)
				return (ft_puterror(FAILED_MALLOC, (char *)"ft_getenv"));
			return (NULL);
		}
	}
	data->path = 0;
	return (NULL);
}

t_list	*ft_isoperator_treatment(t_data *data, t_list *out, t_list **addr_list)
{
	t_btree	*tree;
	t_list	*tmp_list;

	tree = new_tree(out->content, data);
	if (tree == NULL)
		return (ft_puterror(FAILED_MALLOC, "ft_isoperator_treatment\n"));
	if (!*addr_list)
		return (ft_puterror(ERROR_EXPRESSION, NULL), free_tree(tree), NULL);
	tree->r = (t_btree *)(*addr_list)->content;
	free(ft_lstpop(addr_list));
	if (!(*addr_list))
		return (ft_puterror(ERROR_EXPRESSION, NULL), free_tree(tree), NULL);
	tree->l = (t_btree *)(*addr_list)->content;
	free(ft_lstpop(addr_list));
	tmp_list = ft_lstnew(tree);
	if (!tmp_list)
		return (ft_puterror(FAILED_MALLOC, "ft_isoperator_treatment\n"),
			free_tree(tree), NULL);
	ft_lstadd_front(addr_list, tmp_list);
	return (*addr_list);
}

void	*add_tree_to_list(t_list	*out, t_data *data, t_list **addr_list)
{
	t_list	*tmp_list;
	t_btree	*tmp_tree;

	tmp_tree = new_tree(out->content, data);
	if (!tmp_tree)
		return (ft_puterror(FAILED_MALLOC, "get_tree_treatment\n"),
			*addr_list);
	tmp_list = ft_lstnew(tmp_tree);
	if (!tmp_list)
		return (ft_puterror(FAILED_MALLOC, "get_tree_treatment\n"),
			free_tree(tmp_tree), *addr_list);
	ft_lstadd_front(addr_list, tmp_list);
	return (*addr_list);
}

t_list	*get_tree_treatment(char *str, t_rpn rpn_var, t_data *data)
{
	t_list	*out;
	t_list	*list;

	if (!str)
		return (NULL);
	list = NULL;
	out = rpn_var.out;
	while (out)
	{
		if (ft_match_list(out->content, rpn_var.operators))
		{
			if (!ft_isoperator_treatment(data, out, &list))
				return (list);
		}
		else if (!add_tree_to_list(out, data, &list))
			return (list);
		out = out->next;
	}
	return (list);
}

t_btree	*get_tree(char *str, char **env, t_data *data)
{
	t_rpn	rpn_var;
	t_btree	*tree;
	t_list	*list;

	// if (!ft_getenv(env, data))
	(void) env;
	// 	return (NULL);
	if (!rpn(&rpn_var, str))
		return (NULL);
	list = get_tree_treatment(str, rpn_var, data);
	if (!list)
		return (free_rpn(&rpn_var), NULL);
	tree = list->content;
	free(list);
	return (free_rpn(&rpn_var), tree);
}

// int main(int ac, char **av, char **ev)
// {
// 	t_btree	*tree;

// 	if (ac > 1)
// 	{
// 		if (!parsing(av[1]))
// 			return (-1);
// 		tree = get_tree(av[1], ev, NULL);

// 		free_tree(tree);
// 	}
// 	return (0);
// }