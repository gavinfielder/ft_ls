/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:42 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/22 18:12:06 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <dirent.h>
# include <stdint.h>

# define FTLS_NAME_SIZE 1024
# define FTLS_USER_SIZE 32
# define FTLS_GROUP_SIZE 32
# define FTLS_LINK_SIZE 1023
# define FTLS_XATTR_SIZE 1023
# define FTLS_WINSIZE_PAD 20

typedef struct				s_file
{
	struct s_file			*left;
	struct s_file			*right;
	struct s_file			*parent;
	char					name[FTLS_NAME_SIZE + 1];
	char					user[FTLS_USER_SIZE + 1];
	char					group[FTLS_GROUP_SIZE + 1];
	char					*link;
	char					*xattr;
	ssize_t					xattr_len;
	char					*path;
	acl_t					acl;
	struct stat				*s;
}							t_file;

/*
** From man 2 stat:
**
** struct stat { / when _DARWIN_FEATURE_64_BIT_INODE is defined /
**     dev_t           st_dev;           / ID of device containing file /
**     mode_t          st_mode;          / Mode of file (see below) /
**     nlink_t         st_nlink;         / Number of hard links /
**     ino_t           st_ino;           / File serial number /
**     uid_t           st_uid;           / User ID of the file /
**     gid_t           st_gid;           / Group ID of the file /
**     dev_t           st_rdev;          / Device ID /
**     struct timespec st_atimespec;     / time of last access /
**     struct timespec st_mtimespec;     / time of last data modification /
**     struct timespec st_ctimespec;     / time of last status change /
**     struct timespec st_birthtimespec; / time of file creation(birth) /
**     off_t           st_size;          / file size, in bytes /
**     blkcnt_t        st_blocks;        / blocks allocated for file /
**     blksize_t       st_blksize;       / optimal blocksize for I/O /
**     uint32_t        st_flags;         / user defined flags for file /
**     uint32_t        st_gen;           / file generation number /
**     int32_t         st_lspare;        / RESERVED: DO NOT USE! /
**     int64_t         st_qspare[2];     / RESERVED: DO NOT USE! /
** };
*/

/*
** -----------------------------------------------------------------------------
**    Function Types and Other Forward Declarations
** -----------------------------------------------------------------------------
*/
struct s_ls_options;
typedef struct s_ls_options	t_ls_options;
typedef void	(*t_static_initfunc)	(t_file *, t_ls_options *);
typedef void	(*t_note_entry)	(t_file *, uint16_t);
typedef void	(*t_fprnt)	(t_file *, t_ls_options *);
typedef void	(*t_outlo)	(t_file *);
typedef long	t_itsalong;
typedef t_itsalong	(*t_fcmp)	(t_file *, t_file *);

/*
** -----------------------------------------------------------------------------
**    Sorting
** -----------------------------------------------------------------------------
*/
long						byname(t_file *a, t_file *b);
long						nosort(t_file *a, t_file *b);
long						bytime(t_file *a, t_file *b);
long						bytime_a(t_file *a, t_file *b);
long						bytime_c(t_file *a, t_file *b);
long						bytime_m(t_file *a, t_file *b);
long						bytime_bigu(t_file *a, t_file *b);
long						bysize(t_file *a, t_file *b);

/*
** -----------------------------------------------------------------------------
**    Tree Operations
** -----------------------------------------------------------------------------
*/
t_file						*new_node(void);
t_file						*del_node(t_file **f);
t_file						*del_tree(t_file **head);
t_file						*insert_node(t_file **head, t_file *toadd,
								t_fcmp cmp, char sort_dir);
/*
** -----------------------------------------------------------------------------
**    Options Management
** -----------------------------------------------------------------------------
*/
typedef struct				s_display_mode
{
	t_fprnt					display;
	t_static_initfunc		display_init;
	t_static_initfunc		display_deinit;
	t_note_entry			note_entry;
}							t_display_mode;

struct						s_ls_options
{
	char					a;
	char					l;
	char					big_r;
	char					lxattr;
	char					sort_dir;
	char					time_sel;
	char					d;
	char					lacl;
	char					big_g;
	char					g;
	char					n;
	char					big_t;
	short					max_depth;
	t_display_mode			display_mode;
	t_fcmp					sort;
};

int							get_options(t_ls_options *options,
								int argc, char **argv);
void						options_debrief(t_ls_options *options);
void						out_l_set_outl_options(t_ls_options *options);

/*
** -----------------------------------------------------------------------------
**    File Operations
** -----------------------------------------------------------------------------
*/
t_file						*new_file(const char *path, const char *filename,
								t_ls_options *options);
t_file						*list_directory(const char *path,
								t_ls_options *options, int depth);

/*
** -----------------------------------------------------------------------------
**    Output
** -----------------------------------------------------------------------------
*/
extern const t_display_mode	g_display_h;
extern const t_display_mode g_display_v;
extern const t_display_mode g_display_c;
extern const t_display_mode	g_display_l;

void						out_main(t_file *head, t_ls_options *options,
								int depth);

void						out_v(t_file *f, t_ls_options *options);
void						out_l(t_file *f, t_ls_options *options);
void						out_h(t_file *f, t_ls_options *options);
void						out_h_color(t_file *f, t_ls_options *options);
void						out_c(t_file *f, t_ls_options *options);

void						out_color(t_file *f);

void						outh_new_entry(void);
void						note_entry(t_file *f, uint16_t len);
void						end_column_output(t_file *f,
								t_ls_options *options);
void						begin_column_output(t_file *f,
								t_ls_options *options);

void						cleanup_csv(t_file *f,
								t_ls_options *options);

void						outl_print_mode(t_file *f);
void						outl_print_totalblocks(t_file *f,
								t_ls_options *options);

void						out_l_n0g0(t_file *f);
void						out_l_n1g0(t_file *f);
void						out_l_n0g1(t_file *f);
void						out_l_n1g1(t_file *f);

/*
** -----------------------------------------------------------------------------
**    Query Queue
** -----------------------------------------------------------------------------
*/
typedef struct				s_queue
{
	char					*path;
	struct s_queue			*next;
	int						depth;
}							t_queue;

char						*enqueue(const char *path, int depth);
t_queue						*dequeue(void);
int							get_queue_length(void);

/*
** -----------------------------------------------------------------------------
**    Terminal Control
** -----------------------------------------------------------------------------
*/
uint16_t					tty_get_window_width(void);
void						tty_begin_column(int col);
void						tty_next_row(void);
void						tty_end_columns(void);
uint16_t					tty_note_length(uint16_t len);

/*
** -----------------------------------------------------------------------------
**    Miscellaneous
** -----------------------------------------------------------------------------
*/
void						noop(t_file *f, t_ls_options *options);
long						count_blocks(t_file *f);
struct timespec				*get_selected_timespec(t_file *f,
								t_ls_options *options);
char						*prepend_path(char const *dir,
								char const *filename);
void						illegal_option(char c);

/*
** -----------------------------------------------------------------------------
**    Stuff we need because norm makes us write bad code
** -----------------------------------------------------------------------------
*/
typedef struct				s_ldhelper
{
	t_file					*head;
	DIR						*dp;
	struct dirent			*ent;
	char					*path;
	t_file					*f;
	const char				*dir;
	t_ls_options			*options;
	int						depth;
}							t_ldhelper;

t_file						*fileop_abort_close(t_file *f, t_ldhelper *h);

#endif
