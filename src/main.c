/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:37:42 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 17:53:36 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls.h"
#include "libft.h"
#include "libftprintf.h"

static void	handle_dir_header(char *path, int times)
{
	if (times)
		ft_putchar('\n');
	if (times || get_queue_length() > 0)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
}

static void	process_head(t_ls_options *options, t_file *head)
{
	options->display_mode.display_init(head, options);
	out_main(head, options, 0);
	options->display_mode.display_deinit(head, options);
	del_tree(&head);
}

static void	process(t_ls_options *options, t_file *head)
{
	char		*path;
	t_queue		*q;
	int			times;

	times = 0;
	if (head)
	{
		process_head(options, head);
		times = 1;
	}
	while ((q = dequeue()))
	{
		path = q->path;
		if (q->depth <= options->max_depth)
		{
			handle_dir_header(path, times);
			head = list_directory(path, options, q->depth);
			process_head(options, head);
		}
		free(path);
		free(q);
		times++;
	}
}

static int	is_dir(char *str)
{
	DIR	*dir;

	if ((dir = opendir(str)) != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int				i;
	t_ls_options	options;
	t_file			*head;
	t_file			*f;

	head = NULL;
	i = argc - get_options(&options, argc, argv);
	if (i-- == argc)
		enqueue(".", 0);
	while (++i < argc)
	{
		if (is_dir(argv[i]) && !options.d)
			enqueue(argv[i], 0);
		else
		{
			f = new_file(argv[i], argv[i], &options);
			insert_node(&head, f,
					options.sort, options.sort_dir);
			if (options.display_mode.note_entry)
				options.display_mode.note_entry(f,
						(short)ft_strlen(argv[i]));
		}
	}
	process(&options, head);
	return (0);
}
