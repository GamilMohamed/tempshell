/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/14 17:29:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getenv(char **envp, t_data *data)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (!data->path)
			{
				free(data);
				exit(1);
			}
		}
	}
}

t_btree	*get_tree(char *str, char **env, t_data *data)
{
	t_rpn	rpn_var;
	t_list	*out;
	t_list	*list;
	t_btree	*tree;

	ft_getenv(env, data);
	if (!str)
		return (NULL);
	rpn(&rpn_var, str);
	if (rpn_var.current)
	{
		printf ("Error or special case: %s\n", (char *) rpn_var.current->content);
		free_rpn(&rpn_var);
		return (NULL);
	}
	list = NULL;
	out = rpn_var.out;
	tree = NULL;
	while (out)
	{
		if (ft_match_list(out->content, rpn_var.operators))
		{
			tree = new_tree(out->content, data);
			if (!list)
			{
				printf("Erreur d'expression\n");
				free_tree(tree);
				return (NULL);
			}
			tree->r = (t_btree *) list->content;
			free(ft_lstpop(&list));
			if (!list)
			{
				printf("Erreur d'expression\n");
				free_tree(tree);
				return (NULL);
			}
			tree->l = (t_btree *) list->content;
			free(ft_lstpop(&list));
			ft_lstadd_front(&list, ft_lstnew(tree));
		}
		else
		{
			ft_lstadd_front(&list, ft_lstnew(new_tree(out->content, data)));
			tree = (t_btree*)list->content;

		}
		out = out->next;
	}
	free_rpn(&rpn_var);
	return ((t_btree *) list->content);
}
