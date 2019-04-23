/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:52:15 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 03:31:11 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

long		byname(t_file *a, t_file *b)
{
	return (ft_strcmp(a->name, b->name));
}

long		nosort(t_file *a, t_file *b)
{
	(void)a;
	(void)b;
	return (0);
}

long		bysize(t_file *a, t_file *b)
{
	return (b->s->st_size - a->s->st_size);
}

long		bytime(t_file *a, t_file *b)
{
	(void)a;
	(void)b;
	return (0);
}
