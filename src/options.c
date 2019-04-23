/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:24:54 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 04:13:41 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls.h"
#include "libft.h"

static void		options_init(t_ls_options *options)
{
	ft_bzero(options, sizeof(t_ls_options));
	options->sort = byname;
	options->display_mode = g_display_h;
	options->sort_dir = 1;
	options->time_sel = 'm';
	options->max_depth = 32767;
}

static void		parse_option_2(t_ls_options *options, char c)
{
	if (c == 'e')
		options->lacl = 1;
	else if (c == 'f')
		options->sort = nosort;
	else if (c == 'G')
		options->big_g = 1;
	else if (c == 'g')
		options->g = 1;
	else if (c == 'm')
		options->display_mode = g_display_c;
	else if (c == 'n')
		options->n = 1;
	else if (c == 'S')
		options->sort = bysize;
	else if (c == 'u')
		options->time_sel = 'a';
	else if (c == 'U')
		options->time_sel = 'U';
	else if (c >= '2' && c <= '9')
		options->max_depth = c - '0';
	else
		illegal_option(c);
}

static void		parse_option_1(t_ls_options *options, char c)
{
	if (c == 'a')
		options->a = 1;
	else if (c == 'l')
	{
		options->l = 1;
		options->display_mode = g_display_l;
	}
	else if (c == 'R')
		options->big_r = 1;
	else if (c == 'r')
		options->sort_dir = -1;
	else if (c == 't')
		options->sort = bytime;
	else if (c == '@')
		options->lxattr = 1;
	else if (c == '1')
		options->display_mode = g_display_v;
	else if (c == 'C')
		options->display_mode = g_display_h;
	else if (c == 'c')
		options->time_sel = 'c';
	else if (c == 'd')
		options->d = 1;
	else
		parse_option_2(options, c);
}

int				get_options(t_ls_options *options, int argc, char **argv)
{
	int			i;
	int			j;

	i = 1;
	options_init(options);
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				parse_option_1(options, argv[i][j]);
				j++;
			}
		}
		else
		{
			options_debrief(options);
			return (argc - i);
		}
		i++;
	}
	options_debrief(options);
	return (0);
}

void			options_debrief(t_ls_options *options)
{
	if (options->sort == bytime)
	{
		if (options->time_sel == 'm')
			options->sort = bytime_m;
		else if (options->time_sel == 'a')
			options->sort = bytime_a;
		else if (options->time_sel == 'c')
			options->sort = bytime_c;
		else if (options->time_sel == 'U')
			options->sort = bytime_bigu;
		else
			options->sort = bytime_m;
	}
	if (options->display_mode.display == out_h && options->big_g)
		options->display_mode.display = out_h_color;
	if (options->l)
		out_l_set_outl_options(options);
}
