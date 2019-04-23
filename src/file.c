/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:30:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 18:13:56 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>
#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <stdio.h>

static t_file	*fileop_abort(t_file *f)
{
	if (f)
		del_node(&f);
	perror("ft_ls");
	return (NULL);
}

static t_file	*new_file_helper(const char *path, t_file *f,
		t_ls_options *options, int tmp)
{
	if ((f->s->st_mode & S_IFMT) == S_IFLNK)
	{
		if (!(((f->link = (char *)malloc(FTLS_LINK_SIZE + 1)) == NULL) ||
				((tmp = readlink(path, f->link, FTLS_LINK_SIZE)) < 0)))
			f->link[tmp] = '\0';
		else
			perror("ft_ls");
	}
	if (options->l)
	{
		if ((tmp = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		{
			if ((f->xattr = (char *)malloc(tmp + 1)) &&
				(listxattr(path, f->xattr, tmp, XATTR_NOFOLLOW) > 0))
			{
				f->xattr_len = tmp;
				f->path = ft_strdup(path);
			}
			else
				perror("ft_ls");
		}
		f->acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	}
	return (f);
}

t_file			*new_file(const char *path, const char *filename,
					t_ls_options *options)
{
	t_file			*f;
	struct passwd	*pw;
	struct group	*gr;
	int				tmp;

	f = NULL;
	tmp = 0;
	if ((f = new_node()) == NULL)
		return (fileop_abort(f));
	ft_strncpy(f->name, filename, FTLS_NAME_SIZE);
	if (lstat(path, f->s) < 0)
		return (fileop_abort(f));
	if ((pw = getpwuid(f->s->st_uid)) != NULL)
		ft_strncpy(f->user, pw->pw_name, FTLS_USER_SIZE);
	if ((gr = getgrgid(f->s->st_gid)) != NULL)
		ft_strncpy(f->group, gr->gr_name, FTLS_GROUP_SIZE);
	return (new_file_helper(path, f, options, tmp));
}

static t_file	*list_directory_helper(t_ldhelper h)
{
	if ((h.dp = opendir(h.dir)) == NULL)
		return (fileop_abort(h.head));
	while ((h.ent = readdir(h.dp)))
	{
		if (!(h.options->a) && ft_strnequ(h.ent->d_name, ".", 1))
			continue ;
		if ((h.path = prepend_path(h.dir, h.ent->d_name)) == NULL)
			return (fileop_abort(NULL));
		if (!ft_strequ(h.ent->d_name, ".") && !ft_strequ(h.ent->d_name, ".."))
		{
			if ((h.f = new_file(h.path, h.ent->d_name, h.options)) == NULL)
				return (fileop_abort_close(NULL, &h));
			insert_node(&(h.head), h.f, h.options->sort, h.options->sort_dir);
			if (h.options->big_r && (h.f->s->st_mode & S_IFMT) == S_IFDIR)
				enqueue(h.path, h.depth + 1);
			if (h.options->display_mode.note_entry)
				h.options->display_mode.note_entry(h.f, h.ent->d_namlen);
		}
		else
			insert_node(&(h.head), new_file(h.path, h.ent->d_name,
						h.options), h.options->sort, h.options->sort_dir);
		free(h.path);
	}
	closedir(h.dp);
	return (h.head);
}

t_file			*list_directory(const char *dir,
					t_ls_options *options, int depth)
{
	t_ldhelper		h;
	t_file			*ret;

	h.head = NULL;
	h.dp = NULL;
	h.ent = NULL;
	h.path = NULL;
	h.f = NULL;
	h.dir = dir;
	h.options = options;
	h.depth = depth;
	ret = list_directory_helper(h);
	return (ret);
}
