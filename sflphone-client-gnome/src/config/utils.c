/*
 *  Copyright (C) 2009 Savoir-Faire Linux inc.
 *  Author: Emmanuel Milou <emmanuel.milou@savoirfairelinux.com>
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

#include "utils.h"

void gnome_main_section_new (gchar *title, GtkWidget **frame)
{
    GtkWidget *_frame, *label;
    PangoAttrList *attrs = NULL;
    PangoAttribute *attr = NULL;

    attrs = pango_attr_list_new ();
    attr = pango_attr_weight_new (PANGO_WEIGHT_BOLD);
    attr->start_index = 0;
    attr->end_index = -1;
    pango_attr_list_insert (attrs, attr);

    _frame = gtk_frame_new (title);
    gtk_frame_set_shadow_type (GTK_FRAME (_frame), GTK_SHADOW_NONE);
    gtk_container_set_border_width(GTK_CONTAINER(_frame), 2);
    
    label = gtk_frame_get_label_widget (GTK_FRAME (_frame));
    gtk_label_set_attributes (GTK_LABEL (label), attrs);
    pango_attr_list_unref (attrs);
    
    *frame = _frame;
}


