/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:42:21 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 02:59:37 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ls.h"
#include "libft.h"

static t_queue	*g_qhead = NULL;
static t_queue	*g_qtail = NULL;
static int		g_queue_size = 0;

char			*abort_queue_operation(void)
{
	perror("ft_ls");
	exit(-1);
	return (NULL);
}

char			*enqueue(const char *path, int depth)
{
	t_queue			*q;

	if ((q = (t_queue *)malloc(sizeof(t_queue))) == NULL)
		return (abort_queue_operation());
	if ((q->path = ft_strdup(path)) == NULL)
		return (abort_queue_operation());
	q->next = NULL;
	q->depth = depth;
	if (g_qhead == NULL)
	{
		g_qhead = q;
		g_qtail = q;
	}
	else
	{
		g_qtail->next = q;
		g_qtail = q;
	}
	g_queue_size++;
	return (q->path);
}

t_queue			*dequeue(void)
{
	t_queue		*ret;

	if (g_qhead == NULL)
		return (NULL);
	ret = g_qhead;
	g_qhead = g_qhead->next;
	if (!g_qhead)
		g_qtail = NULL;
	g_queue_size--;
	return (ret);
}

int				get_queue_length(void)
{
	return (g_queue_size);
}
