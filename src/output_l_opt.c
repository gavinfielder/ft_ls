/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_l_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 04:21:18 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 04:21:51 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libftprintf.h"

void		out_l_n0g0(t_file *f)
{
	ft_printf("%4hu %-9.9s %-16.16s %6lli ",
			f->s->st_nlink, f->user,
			f->group, f->s->st_size);
}

void		out_l_n1g0(t_file *f)
{
	ft_printf("%4hu %-9u %-16u %6lli ",
			f->s->st_nlink, f->s->st_uid,
			f->s->st_gid, f->s->st_size);
}

void		out_l_n0g1(t_file *f)
{
	ft_printf("%4hu %-16.16s %6lli ",
			f->s->st_nlink,
			f->group, f->s->st_size);
}

void		out_l_n1g1(t_file *f)
{
	ft_printf("%4hu %-16u %6lli ",
			f->s->st_nlink,
			f->s->st_gid, f->s->st_size);
}
