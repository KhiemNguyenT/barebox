/*
 * (C) Copyright 2009-2010 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __MENU_H__
#define __MENU_H__

#include <linux/list.h>
#include <malloc.h>

struct menu;

struct menu_entry {
	int num;
	char *display;
	void (*action)(struct menu *m, struct menu_entry *me);
	void (*free)(struct menu_entry *me);
	int non_re_ent;

	struct list_head list;
};

struct menu {
	char *name;
	char *display;

	struct list_head list;
	struct list_head entries;

	int nb_entries;
	int width;
	struct menu_entry *selected;
	void *priv;
};

/*
 * menu functions
 */
static inline struct menu* menu_alloc(void)
{
	struct menu *m;

	m = calloc(1, sizeof(struct menu));
	if (m) {
		INIT_LIST_HEAD(&m->entries);
		m->nb_entries = 0;
	}
	return m;
}
struct menu_entry *menu_add_submenu(struct menu *parent, char *submenu, char *display);
struct menu_entry *menu_add_command_entry(struct menu *m, char *display, char *command);
void menu_free(struct menu *m);
int menu_add(struct menu* m);
void menu_remove(struct menu *m);
struct menu* menu_get_by_name(char *name);
int menu_show(struct menu *m);
int menu_set_selected_entry(struct menu *m, struct menu_entry* me);
int menu_set_selected(struct menu *m, int num);
struct menu* menu_get_menus(void);

/*
 * menu entry functions
 */
static inline struct menu_entry* menu_entry_alloc(void)
{
	return calloc(1, sizeof(struct menu_entry));
}
void menu_entry_free(struct menu_entry *me);
int menu_add_entry(struct menu *m, struct menu_entry* me);
void menu_remove_entry(struct menu *m, struct menu_entry *me);
struct menu_entry* menu_entry_get_by_num(struct menu* m, int num);

/*
 * menu entry action functions
 */
void menu_action_exit(struct menu *m, struct menu_entry *me);

#endif /* __MENU_H__ */