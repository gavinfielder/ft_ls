/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:26:32 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/21 04:11:59 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>
#include "ls.h"
#include "libft.h"
#include <strings.h>

t_file			*new_node(void)
{
	t_file	*f;

	f = (t_file *)malloc(sizeof(t_file));
	if (!f)
		return (NULL);
	ft_bzero(f, sizeof(t_file));
	f->s = (struct stat *)malloc(sizeof(struct stat));
	if (!(f->s))
		return (del_node(&f));
	return (f);
}

t_file			*del_node(t_file **f)
{
	if (*f)
	{
		if ((*f)->link)
			free((*f)->link);
		if ((*f)->s)
			free((*f)->s);
		if ((*f)->xattr)
			free((*f)->xattr);
		if ((*f)->acl)
			acl_free((void *)((*f)->acl));
		if ((*f)->path)
			free((*f)->path);
		free(*f);
		*f = NULL;
	}
	return (NULL);
}

t_file			*del_tree(t_file **head)
{
	if (*head)
	{
		del_tree(&((*head)->left));
		del_tree(&((*head)->right));
		del_node(head);
	}
	return (NULL);
}

t_file			*insert_node(t_file **head, t_file *toadd, t_fcmp cmp,
					char sort_dir)
{
	t_file	**curr;

	if (*head == NULL)
		*head = toadd;
	else if (toadd && cmp)
	{
		curr = (cmp(toadd, *head) * sort_dir < 0 ?
				&((*head)->left) : &((*head)->right));
		while (*curr != NULL)
		{
			curr = (cmp(toadd, *curr) * sort_dir < 0 ?
					&((*curr)->left) : &((*curr)->right));
		}
		*curr = toadd;
	}
	return (*head);
}
