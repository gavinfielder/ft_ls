/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 23:56:09 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/17 15:40:00 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putchar_np(char c, char c_if_nonprintable)
{
	if (c >= 32 && c <= 126)
		write(1, &c, 1);
	else
		write(1, &c_if_nonprintable, 1);
}

void	ft_putnchar_np_hex(const char *str, size_t n)
{
	size_t i;

	if (str == NULL)
		return ;
	i = 0;
	while (i < n)
	{
		if (str[i] >= 32 && str[i] <= 126)
			ft_putchar(str[i]);
		else
		{
			ft_putstr("\\x");
			ft_printhexbyte(str + i);
		}
		i++;
	}
}
