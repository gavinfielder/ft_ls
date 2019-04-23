/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:07:25 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 18:14:54 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ls.h"

t_file	*fileop_abort_close(t_file *f, t_ldhelper *h)
{
	if (f)
		del_node(&f);
	if (h->path)
		free(h->path);
	closedir(h->dp);
	perror("ft_ls");
	return (NULL);
}
