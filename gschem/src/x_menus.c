/* gEDA - GPL Electronic Design Automation
 * gschem - gEDA Schematic Capture
 * Copyright (C) 1998-2010 Ales Hvezda
 * Copyright (C) 1998-2010 gEDA Contributors (see ChangeLog for details)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include "config.h"
#include <missing.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif


#include "gschem.h"

#include <glib/gstdio.h>

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

static GtkItemFactoryEntry popup_items[] = {
  { N_("/Add Net"), 	      NULL, i_callback_add_net,           0, NULL},
  { N_("/Add Attribute..."),  NULL, i_callback_add_attribute,     0, NULL},
  { N_("/Add Component..."),  NULL, i_callback_add_component,     0, NULL},
  { N_("/Add Bus"), 	      NULL, i_callback_add_bus,           0, NULL},
  { N_("/Add Text"), 	      NULL, i_callback_add_text,          0, NULL},
  { "/sep1", NULL, NULL, 0, "<Separator>"},
  { N_("/Zoom In"),       NULL, i_callback_view_zoom_in,      0, NULL},
  { N_("/Zoom Out"),      NULL, i_callback_view_zoom_out,     0, NULL},
  { N_("/Zoom Box"),      NULL, i_callback_view_zoom_box,     0, NULL},
  { N_("/Zoom Extents"),  NULL, i_callback_view_zoom_extents, 0, NULL},
  { "/sep1", NULL, NULL, 0, "<Separator>"},
  { N_("/Select"), 	  NULL, i_callback_edit_select,       0, NULL},
  { N_("/Edit..."), 	  NULL, i_callback_edit_edit,         0, NULL},
  { N_("/Edit pin type..."), 	  NULL, i_callback_edit_pin_type,         0, NULL},
  { N_("/Copy"),          NULL, i_callback_edit_copy,         0, NULL},
  { N_("/Move"),          NULL, i_callback_edit_move,         0, NULL},
  { N_("/Delete"),        NULL, i_callback_edit_delete,       0, NULL},
  /* Menu items for hierarchy added by SDB 1.9.2005.  */
  {"/sep1", NULL, NULL, 0, "<Separator>"},
  {N_("/Down Schematic"), NULL, i_callback_hierarchy_down_schematic, 0, NULL},
  {N_("/Down Symbol"),    NULL, i_callback_hierarchy_down_symbol,    0, NULL},
  {N_("/Up"),             NULL, i_callback_hierarchy_up,             0, NULL},
};  

int npopup_items = sizeof(popup_items) / sizeof(popup_items[0]);

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
static void g_menu_execute(GtkAction *action, gpointer user_data)
{
  gchar *guile_string = NULL;
  const gchar *func = gtk_action_get_name (action);
  GSCHEM_TOPLEVEL *w_current = (GSCHEM_TOPLEVEL *) user_data;

  guile_string = g_strdup_printf("(%s)", func);
#if DEBUG
  printf("%s\n", guile_string);
#endif
  scm_dynwind_begin (0);
  scm_dynwind_unwind_handler (g_free, guile_string, SCM_F_WIND_EXPLICITLY);
  g_dynwind_window (w_current);
  g_scm_c_eval_string_protected (guile_string);
  scm_dynwind_end ();
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
GtkWidget *
get_main_menu(GSCHEM_TOPLEVEL *w_current)
{
  char *buf;
  GschemAction *action;
  GtkWidget *menu_item;
  GtkWidget *root_menu;
  GtkWidget *menu_bar;
  GtkWidget *menu;
  int scm_items_len;
  SCM scm_items;
  SCM scm_item;
  SCM scm_item_name;
  SCM scm_item_func;
  SCM scm_item_hotkey_func;
  SCM scm_item_stock;
  SCM scm_index;
  SCM scm_keys;
  char *menu_name;
  char *action_name;
  char **raw_menu_name = g_malloc (sizeof(char *));
  char *menu_item_name;
  char *raw_menu_item_name;
  char *menu_item_hotkey_func;
  char *menu_item_stock;
  char *menu_item_keys;
  int i, j;

  menu_bar = gtk_menu_bar_new ();

  scm_dynwind_begin (0);
  g_dynwind_window (w_current);
  /*! \bug This function may leak memory if there is a non-local exit
   * in Guile code. At some point, unwind handlers need to be added to
   * clean up heap-allocated strings. */

  for (i = 0 ; i < s_menu_return_num(); i++) {
    
    scm_items = s_menu_return_entry(i, raw_menu_name);   
    if (*raw_menu_name == NULL) {
      fprintf(stderr, "Oops.. got a NULL menu name in get_main_menu()\n");
      exit(-1);
    }

    menu = gtk_menu_new();

    menu_item = gtk_tearoff_menu_item_new ();
    gtk_menu_append(GTK_MENU(menu), menu_item);
    gtk_widget_show(menu_item);

    scm_items_len = (int) scm_ilength (scm_items);
    for (j = 0 ; j < scm_items_len; j++) {

      scm_index = scm_from_int (j);
      scm_item = scm_list_ref (scm_items, scm_index);
      scm_item_name = SCM_CAR (scm_item);
      scm_item_func = SCM_CADR (scm_item);
      scm_item_hotkey_func = SCM_CADDR (scm_item);
      scm_item_stock = scm_is_pair (SCM_CDDDR (scm_item)) ?
                         SCM_CADDDR (scm_item) : SCM_BOOL_F;
      SCM_ASSERT(scm_is_string(scm_item_name), scm_item_name, SCM_ARGn, "get_main_menu item_name");
      SCM_ASSERT(scm_is_symbol (scm_item_func) ||
                    scm_is_false (scm_item_func),
                 scm_item_func, SCM_ARGn, "get_main_menu item_func");
      SCM_ASSERT (scm_is_symbol (scm_item_hotkey_func) ||
                    scm_is_false (scm_item_hotkey_func),
                  scm_item_hotkey_func, SCM_ARGn, "get_main_menu hotkey_func");
      SCM_ASSERT (scm_is_string (scm_item_stock) ||
                    scm_is_false (scm_item_stock),
                  scm_item_stock, SCM_ARGn, "get_main_menu stock");

      raw_menu_item_name = scm_to_utf8_string(scm_item_name);
      scm_dynwind_begin(0);
      scm_dynwind_free(raw_menu_item_name);

      menu_item_name = (char *) gettext(raw_menu_item_name);

      if (strcmp(menu_item_name, "SEPARATOR") == 0) {
        menu_item = gtk_menu_item_new();
        gtk_menu_append(GTK_MENU(menu), menu_item);
      } else {

        if (scm_is_false (scm_item_hotkey_func)) {
          menu_item_hotkey_func = NULL;
        } else {
          menu_item_hotkey_func = scm_to_utf8_string (scm_symbol_to_string (scm_item_hotkey_func));
          scm_dynwind_free (menu_item_hotkey_func);
        }

        if (menu_item_hotkey_func != NULL) {
          SCM s_expr =
            scm_list_2 (scm_from_utf8_symbol ("find-key"),
                        scm_list_2 (scm_from_utf8_symbol ("quote"),
                                    scm_from_utf8_symbol (menu_item_hotkey_func)));

          scm_keys = g_scm_eval_protected (s_expr, scm_interaction_environment ());

          if (scm_is_false (scm_keys)) {
            menu_item_keys = "";
          } else {
            menu_item_keys = scm_to_utf8_string (scm_keys);
            scm_dynwind_free(menu_item_keys);
          }

        } else {
          menu_item_keys = "";
        }

        if(scm_is_false (scm_item_func)) {
          menu_item = gtk_menu_item_new_with_mnemonic(menu_item_name);
        } else {
          if (scm_is_false (scm_item_stock))
            menu_item_stock = NULL;
          else
            menu_item_stock = scm_to_utf8_string (scm_item_stock);

          action_name = scm_to_utf8_string (scm_symbol_to_string (scm_item_func));
          action = gschem_action_new (action_name,  /* Action name */
                                      menu_item_name,  /* Text */
                                      menu_item_name,  /* Tooltip */
                                      menu_item_stock, /* Icon stock ID */
                                      menu_item_keys); /* Accelerator string */
          free(action_name);
          free(menu_item_stock);

          menu_item = gtk_action_create_menu_item (GTK_ACTION (action));
          g_signal_connect (G_OBJECT(action), "activate",
                            G_CALLBACK(g_menu_execute),
                            w_current);
        }

        gtk_menu_append (GTK_MENU (menu), menu_item);
      }

      gtk_widget_show (menu_item);

      /* add a handle to the menu_bar object to get access to widget objects */
      /* This string should NOT be internationalized */
      buf = g_strdup_printf("%s/%s", *raw_menu_name, raw_menu_item_name);
      gtk_object_set_data(GTK_OBJECT(menu_bar), buf, menu_item);
      g_free(buf);

      scm_dynwind_end();
    }
    
    menu_name = (char *) gettext(*raw_menu_name);
    root_menu = gtk_menu_item_new_with_mnemonic (menu_name);
    /* do not free *raw_menu_name */

    /* no longer right justify the help menu since that has gone out of style */

    gtk_widget_show (root_menu);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
    gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), root_menu);
  }
  scm_dynwind_end ();

  g_free(raw_menu_name);
  return menu_bar;
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
static gchar* gettext_fn(const gchar *path,
			 gpointer func_data ATTRIBUTE_UNUSED)
{
  /*! \bug Note that we have to discard the 'const' qualifier here to
   * avoid build warnings when gettext is disabled.  This is required
   * due to the prototype of the function pointer argument to
   * gtk_item_factory_set_translate_func() */
  return (gchar *) gettext(path);
}

GtkWidget *get_main_popup(GSCHEM_TOPLEVEL *w_current)
{
  static GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;
  GtkWidget *menu;

  accel_group = gtk_accel_group_new();

  /* This function initializes the item factory.
     Param 1: The type of menu - can be GTK_TYPE_MENU_BAR, GTK_TYPE_MENU, or GTK_TYPE_OPTION_MENU.
     Param 2: The path of the menu.
     Param 3: A pointer to a gtk_accel_group.  The item factory sets up
     the accelerator table while generating menus.
  */
  item_factory = gtk_item_factory_new(GTK_TYPE_MENU, "<popup>",
                                      accel_group);
  gtk_item_factory_set_translate_func (item_factory,
                                       gettext_fn,
                                       NULL, NULL);
  /* This function creates the pop-up menu itself & attaches it to the
     GtkItemFactory. Pass the item factory,
     the number of items in the array, the array itself, and any
     callback data for the the menu items. Note that npopup_items is 
     a static var declared in this file above; popup_items is also a
     static var declared above.
  */
  gtk_item_factory_create_items(item_factory, npopup_items, popup_items, w_current);

  /* Finally, return the actual menu created by the item factory. */
  menu = (GtkWidget *) gtk_item_factory_get_widget(item_factory, "<popup>");
  return (menu);

}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 *  \note
 *  need to look at this... here and the setup
 */
gint do_popup (GSCHEM_TOPLEVEL *w_current, GdkEventButton *event)
{
  GtkWidget *menu;   /* =NULL; */ /* was static */

  menu = NULL;  /* Why do I need to do this? */
  if (!menu)
    menu = (GtkWidget *) w_current->popup_menu;

  if (menu == NULL) {
    printf("null menu\n");
  }

  gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL,
                  event->button, event->time);

  return FALSE;
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
void x_menus_sensitivity (GSCHEM_TOPLEVEL *w_current, const char *buf, int flag)
{
  GtkWidget* item=NULL;
  
  if (!buf) {
    return;
  }

  if (!w_current->menubar) {
    return;
  }
  
  item = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(w_current->menubar), buf);

  if (item) {
    gtk_widget_set_sensitive(GTK_WIDGET(item), flag);
    /* free(item); */ /* Why doesn't this need to be freed?  */
  } else {
    s_log_message(_("Tried to set the sensitivity on non-existent menu item '%s'\n"), buf); 
  }
 
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *  This function sets the sensitivity of the items in the right button
 *  popup.
 *
 *  \note
 *  1.9.2005 -- SDB.
 */
void x_menus_popup_sensitivity (GSCHEM_TOPLEVEL *w_current, const char *buf, int flag)
{
  GtkWidget *menu_item;
  GtkItemFactory *menu_item_factory;
  
  if (!buf) {
    return;
  }

  if (!w_current->popup_menu) {
    s_log_message(_("Popup_menu_item_factory doesn't exist!\n")); 
    return;
  }

  /* 
   * first get entire item factory from popup, then get the individual 
   * menu item indexed by buf.
   */
  menu_item_factory = (GtkItemFactory *)gtk_item_factory_from_widget(w_current->popup_menu);  
  menu_item = (GtkWidget *) gtk_item_factory_get_widget(menu_item_factory, buf);
  if (menu_item) {
    gtk_widget_set_sensitive(GTK_WIDGET(menu_item), flag);
  } else {
    s_log_message(_("Tried to set the sensitivity on a non-existent popup menu_item\n")); 
  }
}

#define MAX_RECENT_FILES 10
/*! \brief Callback for recent-chooser.
 *
 * Will be called if element of recent-file-list is activated
 */
void
recent_chooser_item_activated (GtkRecentChooser *chooser, GSCHEM_TOPLEVEL *w_current)
{
  PAGE *page;
  gchar *uri;
  gchar *filename;

  uri = gtk_recent_chooser_get_current_uri (chooser);
  filename = g_filename_from_uri(uri, NULL, NULL);
  gtk_recent_manager_add_item(recent_manager, uri);
  page = x_window_open_page(w_current, (char *)filename);
  x_window_set_current_page(w_current, page);

  g_free(uri);
  g_free(filename);
}

/*! \brief Attach a submenu with filenames to the 'Open Recent'
 *         menu item.
 *
 *  Called from x_window_setup().
 */
void x_menu_attach_recent_files_submenu(GSCHEM_TOPLEVEL *w_current)
{
  GtkWidget* menuitem_to_append_to = NULL;
  GtkRecentFilter *recent_filter;
  GtkWidget *menuitem_file_recent_items;
  recent_manager = gtk_recent_manager_get_default();

  menuitem_file_recent_items = gtk_recent_chooser_menu_new_for_manager(recent_manager);

  /* Show only schematic- and symbol-files (*.sch and *.sym) in list */
  recent_filter = gtk_recent_filter_new();
  gtk_recent_filter_add_mime_type(recent_filter, "application/x-geda-schematic");
  gtk_recent_filter_add_mime_type(recent_filter, "application/x-geda-symbol");
  gtk_recent_filter_add_pattern(recent_filter, "*.sch");
  gtk_recent_filter_add_pattern(recent_filter, "*.sym");
  gtk_recent_chooser_add_filter(GTK_RECENT_CHOOSER(menuitem_file_recent_items), recent_filter);

  gtk_recent_chooser_set_show_tips(GTK_RECENT_CHOOSER(menuitem_file_recent_items), TRUE);
  gtk_recent_chooser_set_sort_type(GTK_RECENT_CHOOSER(menuitem_file_recent_items),
                                   GTK_RECENT_SORT_MRU);
  gtk_recent_chooser_set_limit(GTK_RECENT_CHOOSER(menuitem_file_recent_items), MAX_RECENT_FILES);
  gtk_recent_chooser_set_local_only(GTK_RECENT_CHOOSER(menuitem_file_recent_items), FALSE);
  gtk_recent_chooser_menu_set_show_numbers(GTK_RECENT_CHOOSER_MENU(menuitem_file_recent_items), TRUE);
  g_signal_connect(GTK_OBJECT(menuitem_file_recent_items), "item-activated",
                   G_CALLBACK(recent_chooser_item_activated), w_current);

  menuitem_to_append_to = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(w_current->menubar), "_File/Open Recen_t");
  if(menuitem_to_append_to == NULL)
    return;
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_to_append_to), menuitem_file_recent_items);
}
