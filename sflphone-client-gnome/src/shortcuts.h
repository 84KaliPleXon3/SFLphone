/*
 *  Copyright (C) 2010 Savoir-Faire Linux inc.
 *  Author: Julien Bonjean <julien.bonjean@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_

typedef struct
{
  gchar *action;
  GdkModifierType mask;
  guint value;
  void
  (*callback) (void);
} Accelerator;

static void
grab_key (int key_code, GdkWindow *root);

static void
ungrab_key (int key_code, GdkWindow *root);

static GdkFilterReturn
filter_keys (GdkXEvent *xevent, GdkEvent *event, gpointer data);

static void
remove_bindings ();

static void
create_bindings ();

static void
pick_up_callback ();

static void
hang_up_callback ();

static void
toggle_pick_up_hang_up_callback ();

static void
toggle_hold_callback ();

static void
initialize_binding (const gchar* action, const guint code);

static void
initialize_shortcuts_keys ();

static void*
get_action_callback (const gchar* action);

static void
update_bindings_data (const guint index, const guint code);

/*
 * "Public" functions
 */

void
shortcuts_initialize_bindings ();

void
shortcuts_update_bindings (const guint index, const guint code);

void
shortcuts_destroy_bindings ();

Accelerator*
shortcuts_get_list ();

#endif /* SHORTCUTS_H_ */