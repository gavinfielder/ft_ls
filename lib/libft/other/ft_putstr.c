/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:15:20 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/17 20:47:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft.h"

void	ft_putstr(char const *str)
{
	if (str == NULL)
		return ;
	write(1, str, ft_strlen(str));
}

void	ft_putstr_fd(char const *str, int fd)
{
	if (str == NULL)
		return ;
	write(fd, str, ft_strlen(str));
}

void	ft_putstr_np(char const *str, char c_if_nonprintable)
{
	int i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_np(str[i], c_if_nonprintable);
		i++;
	}
}
