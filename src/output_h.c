/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:32:35 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 04:17:31 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "ls.h"

static uint16_t		g_num_entries = 0;
static uint16_t		g_col_size = 8;
static uint16_t		g_num_rows;
static uint16_t		g_num_cols;
static uint16_t		g_current_column;
static uint16_t		g_current_row;

void	out_h(t_file *f, t_ls_options *options)
{
	(void)options;
	outh_new_entry();
	ft_putstr(f->name);
}

void	note_entry(t_file *f, uint16_t len)
{
	(void)f;
	g_col_size = tty_note_length(len);
	g_num_entries++;
}

void	end_column_output(t_file *f, t_ls_options *options)
{
	(void)f;
	(void)options;
	g_col_size = 8;
	if (!g_num_entries)
		return ;
	g_num_entries = 0;
	tty_end_columns();
}

void	begin_column_output(t_file *f, t_ls_options *options)
{
	uint16_t	ws;
	uint16_t	i;

	(void)f;
	(void)options;
	if (!g_num_entries)
		return ;
	ws = tty_get_window_width();
	g_num_cols = ws / g_col_size;
	if (g_num_cols == 0)
		g_num_cols = 1;
	g_num_rows = (g_num_entries / g_num_cols) + 1;
	if (g_num_entries / g_num_rows + 1 < g_num_cols)
	{
		g_num_cols = g_num_entries / g_num_rows + 1;
		g_col_size = tty_note_length(ws / g_num_cols);
	}
	g_current_column = -1;
	g_current_row = 65535;
	i = 0;
	while (i++ < g_num_rows)
		write(1, "\n", 1);
	write(1, "\x1B[", 2);
	ft_putnbr((int)g_num_rows);
	write(1, "A", 1);
}

void	outh_new_entry(void)
{
	if (g_current_row >= g_num_rows)
	{
		g_current_row = 1;
		tty_begin_column(++g_current_column);
	}
	else
	{
		tty_next_row();
		g_current_row++;
	}
}
