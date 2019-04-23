/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 00:56:30 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 15:41:16 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

static long	bytime_ts(struct timespec *a, struct timespec *b)
{
	long		diff;

	if ((diff = b->tv_sec - a->tv_sec))
		return (diff);
	return ((b->tv_nsec - a->tv_nsec));
}

long		bytime_a(t_file *a, t_file *b)
{
	long	diff;

	if ((diff = bytime_ts(&(a->s->st_atimespec), &(b->s->st_atimespec))))
		return (diff);
	return (ft_strcmp(a->name, b->name));
}

long		bytime_m(t_file *a, t_file *b)
{
	long	diff;

	if ((diff = bytime_ts(&(a->s->st_mtimespec), &(b->s->st_mtimespec))))
		return (diff);
	return (ft_strcmp(a->name, b->name));
}

long		bytime_bigu(t_file *a, t_file *b)
{
	long	diff;

	if ((diff = bytime_ts(&(a->s->st_birthtimespec),
					&(b->s->st_birthtimespec))))
		return (diff);
	return (ft_strcmp(a->name, b->name));
}

long		bytime_c(t_file *a, t_file *b)
{
	long	diff;

	if ((diff = bytime_ts(&(a->s->st_ctimespec), &(b->s->st_ctimespec))))
		return (diff);
	return (ft_strcmp(a->name, b->name));
}
