/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:02:36 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 03:26:32 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

const t_display_mode	g_display_h = {
	out_h,
	begin_column_output,
	end_column_output,
	note_entry
};

const t_display_mode	g_display_v = {
	out_v,
	noop,
	noop,
	NULL
};

const t_display_mode	g_display_c = {
	out_c,
	noop,
	cleanup_csv,
	NULL
};

const t_display_mode	g_display_l = {
	out_l,
	outl_print_totalblocks,
	noop,
	NULL
};

void			out_main(t_file *head, t_ls_options *options, int depth)
{
	if (!head)
		return ;
	if (head->left)
		out_main(head->left, options, depth);
	options->display_mode.display(head, options);
	if (head->right)
		out_main(head->right, options, depth);
}

void			out_color(t_file *f)
{
	if ((f->s->st_mode & S_IFMT) == S_IFDIR)
		ft_putstr("\x1B[34m");
	else if ((f->s->st_mode & S_IFMT) != S_IFREG)
		ft_putstr("\x1B[36m");
	else if (f->s->st_mode & S_IXUSR)
		ft_putstr("\x1B[31m");
}

void			out_v(t_file *f, t_ls_options *options)
{
	(void)options;
	if (options->big_g)
		out_color(f);
	ft_putstr(f->name);
	if (options->big_g)
		ft_putstr("\x1B[0m");
	ft_putchar('\n');
}

void			out_c(t_file *f, t_ls_options *options)
{
	(void)options;
	ft_putstr(f->name);
	ft_putstr(", ");
}
