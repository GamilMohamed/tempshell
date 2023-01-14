/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 04:56:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	*new_queue(void *data, int id)
{
	t_queue *q;

	q = malloc (sizeof(*q));
	if (!q)
		return (NULL);
	q->data = data;
	q->id = id;
	q->next = NULL;
	return (q);
}

void	add_queue(t_queue **queue, t_queue *add)
{
	t_queue *q;

	q = *queue;
	if (!q)
		*queue = add;
	else
	{
		while (q->next)
			q = q->next;
		q->next = add;
	}
}

t_btree	*pop(t_queue **trees)
{
	t_btree	*t;

	t = ((t_btree *)(*trees)->data);
	*trees = (*trees)->next;
	return (t);
}

void	print_queue(t_queue *q)
{
	while(q)
	{
		printf("(%d) %s\n", q->id, (char *)q->data);
		q = q->next;
	}
	printf("\n");
}
