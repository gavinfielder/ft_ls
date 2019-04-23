/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:09:01 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 02:06:31 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "ls.h"

static int		g_total_rows = -1;
static int		g_rows_in_col = -1;
static int		g_col_pos = -1;
static uint16_t	g_col_size = 8;

uint16_t		tty_get_window_width(void)
{
	struct ttysize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ts_cols - FTLS_WINSIZE_PAD);
}

void			tty_begin_column(int col)
{
	if (g_col_pos == -1)
	{
		g_total_rows = 0;
		g_col_pos = 0;
		write(1, "\x1B[s", 3);
	}
	else
	{
		g_col_pos = col * g_col_size;
		write(1, "\x1B[u\x1B[", 5);
		ft_putnbr(g_col_pos);
		write(1, "G", 1);
	}
	g_rows_in_col = 0;
}

void			tty_next_row(void)
{
	write(1, "\x1B[1e\x1B[", 6);
	ft_putnbr(g_col_pos);
	write(1, "G", 1);
	g_rows_in_col++;
	if (g_rows_in_col > g_total_rows)
		g_total_rows = g_rows_in_col;
}

void			tty_end_columns(void)
{
	write(1, "\x1B[u\x1B[", 5);
	ft_putnbr(g_total_rows + 1);
	write(1, "B", 1);
	g_total_rows = -1;
	g_col_pos = -1;
	g_col_size = 8;
}

uint16_t		tty_note_length(uint16_t len)
{
	if (g_col_size <= len)
		g_col_size = len + 2;
	return (g_col_size);
}
