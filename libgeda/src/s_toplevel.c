/* gEDA - GPL Electronic Design Automation
 * libgeda - gEDA's library
 * Copyright (C) 1998, 1999, 2000 Kazu Hirata / Ales Hvezda
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
#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "libgeda_priv.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

static GList *new_toplevel_hooks = NULL;

typedef struct {
  NewToplevelFunc func;
  void *data;
} NewToplevelHook;


void s_toplevel_append_new_hook (NewToplevelFunc func, void *data)
{
  NewToplevelHook *new_hook;

  new_hook = g_new0 (NewToplevelHook, 1);
  new_hook->func = func;
  new_hook->data = data;

  new_toplevel_hooks = g_list_append (new_toplevel_hooks, new_hook);
}


static void call_new_toplevel_hook (gpointer hook, gpointer toplevel)
{
  NewToplevelHook *h = (NewToplevelHook*) hook;
  TOPLEVEL *t = (TOPLEVEL*) toplevel;

  h->func (t, h->data);
}

/*!
 *  \brief Create a TOPLEVEL object
 *  \par Function Description
 *  Create and return an empty TOPLEVEL object with sensible defaults
 *  for its properties.
 *
 *  \returns the newly created TOPLEVEL.
 *
 *  \todo rethink block below that is set in gschem but used in libgeda.
 */
TOPLEVEL *s_toplevel_new (void)
{
  TOPLEVEL *toplevel;

  toplevel = (TOPLEVEL*)g_new (TOPLEVEL, 1);

  toplevel->RC_list = NULL;

  toplevel->untitled_name      = NULL;
  toplevel->bitmap_directory   = NULL;

  toplevel->init_left = 0;
  toplevel->init_top  = 0;
  /* init_right and _bottom are set before this function is called */

  toplevel->width  = 1;
  toplevel->height = 1;

  toplevel->override_color = -1;

  toplevel->pages = geda_list_new();
  toplevel->page_current = NULL;

  toplevel->show_hidden_text = 0;

  toplevel->major_changed_refdes = NULL;

  /* BLOCK SET IN GSCHEM, BUT USED IN LIBGEDA - NEEDS A RETHINK */
  toplevel->background_color   = 0;
  toplevel->override_net_color = -1;
  toplevel->override_bus_color = -1;
  toplevel->override_pin_color = -1;
  toplevel->pin_style = 0;
  toplevel->net_style = 0;
  toplevel->bus_style = 0;
  toplevel->line_style = 0;
  /* END BLOCK - ALTHOUGH THERE ARE MORE CASES! */

  toplevel->object_clipping = 0;

  toplevel->print_orientation = 0;

  toplevel->image_color = FALSE;

  toplevel->print_color = FALSE;

  toplevel->print_color_background = 0;

  toplevel->setpagedevice_orientation = FALSE;

  toplevel->setpagedevice_pagesize = FALSE;

  toplevel->postscript_prolog = NULL;

  toplevel->net_consolidate = FALSE;

  /* The following is an attempt at getting (deterministic) defaults */
  /* for the following variables */
  toplevel->attribute_promotion = FALSE;
  toplevel->promote_invisible   = FALSE;
  toplevel->keep_invisible      = FALSE;

  toplevel->make_backup_files = TRUE;

  toplevel->print_output_type = 0;

  toplevel->print_output_capstyle = BUTT_CAP;

  toplevel->paper_width  = 0;
  toplevel->paper_height = 0;

  toplevel->bus_ripper_symname = NULL;

  toplevel->force_boundingbox = FALSE;

  toplevel->always_promote_attributes = NULL;

  toplevel->net_naming_priority = 0;
  toplevel->hierarchy_traversal = 0;
  toplevel->hierarchy_uref_mangle = 0;
  toplevel->hierarchy_netname_mangle = 0;
  toplevel->hierarchy_netattrib_mangle = 0;
  toplevel->hierarchy_uref_separator      = NULL;
  toplevel->hierarchy_netname_separator   = NULL;
  toplevel->hierarchy_netattrib_separator = NULL;
  toplevel->hierarchy_netattrib_order = 0;
  toplevel->hierarchy_netname_order = 0;
  toplevel->hierarchy_uref_order = 0;
  toplevel->unnamed_netname = NULL;
  toplevel->unnamed_busname = NULL;

  toplevel->rendered_text_bounds_func = NULL;
  toplevel->rendered_text_bounds_data = NULL;

  toplevel->change_notify_funcs = NULL;

  toplevel->attribs_changed_hooks = NULL;

  toplevel->conns_changed_hooks = NULL;

  toplevel->load_newer_backup_func = NULL;
  toplevel->load_newer_backup_data = NULL;

  /* Auto-save interval */
  toplevel->auto_save_interval = 0;
  toplevel->auto_save_timeout = 0;

  toplevel->weak_refs = NULL;

  /* Call hooks */
  g_list_foreach (new_toplevel_hooks, call_new_toplevel_hook, toplevel);

  return toplevel;
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
void s_toplevel_delete (TOPLEVEL *toplevel)
{
  GList *iter;

  if (toplevel->auto_save_timeout != 0) {
    /* Assume this works */
    g_source_remove (toplevel->auto_save_timeout);
  }

  g_free (toplevel->untitled_name);
  g_free (toplevel->bitmap_directory);
  g_free (toplevel->bus_ripper_symname);
  
  /* free all fonts */
  /* if you close a window, then you free the font set... */
  /* this is probably a bad idea... */
  /* The font set can ONLY be freed when exiting!!! */
  /*  o_text_freeallfonts (toplevel); */

  /* delete all pages */
  s_page_delete_list (toplevel);

  /* Delete the page list */
  g_object_unref(toplevel->pages);

  /* Remove all change notification handlers */
  for (iter = toplevel->change_notify_funcs;
       iter != NULL; iter = g_list_next (iter)) {
    g_free (iter->data);
  }
  g_list_free (toplevel->change_notify_funcs);

  s_weakref_notify (toplevel, toplevel->weak_refs);

  g_free (toplevel);

}

/*! \brief Add a weak reference watcher to an TOPLEVEL.
 * \par Function Description
 * Adds the weak reference callback \a notify_func to \a toplevel.  When
 * \a toplevel is destroyed, \a notify_func will be called with two
 * arguments: the \a toplevel, and the \a user_data.
 *
 * \sa s_toplevel_weak_unref
 *
 * \param [in,out] toplevel   Toplevel to weak-reference.
 * \param [in] notify_func    Weak reference notify function.
 * \param [in] user_data      Data to be passed to \a notify_func.
 */
void
s_toplevel_weak_ref (TOPLEVEL *toplevel,
                     void (*notify_func)(void *, void *),
                     void *user_data)
{
  g_return_if_fail (toplevel != NULL);
  toplevel->weak_refs = s_weakref_add (toplevel->weak_refs,
                                       notify_func, user_data);
}

/*! \brief Remove a weak reference watcher from an TOPLEVEL.
 * \par Function Description
 * Removes the weak reference callback \a notify_func from \a toplevel.
 *
 * \sa s_toplevel_weak_ref()
 *
 * \param [in,out] toplevel       Toplevel to weak-reference.
 * \param [in] notify_func    Notify function to search for.
 * \param [in] user_data      Data to to search for.
 */
void
s_toplevel_weak_unref (TOPLEVEL *toplevel,
                       void (*notify_func)(void *, void *),
                       void *user_data)
{
  g_return_if_fail (toplevel != NULL);
  toplevel->weak_refs = s_weakref_remove (toplevel->weak_refs,
                                          notify_func, user_data);
}

/*! \brief Add a weak pointer to an TOPLEVEL.
 * \par Function Description
 * Adds the weak pointer at \a weak_pointer_loc to \a toplevel. The
 * value of \a weak_pointer_loc will be set to NULL when \a toplevel is
 * destroyed.
 *
 * \sa s_toplevel_remove_weak_ptr
 *
 * \param [in,out] toplevel      Toplevel to weak-reference.
 * \param [in] weak_pointer_loc  Memory address of a pointer.
 */
void
s_toplevel_add_weak_ptr (TOPLEVEL *toplevel,
                         void *weak_pointer_loc)
{
  g_return_if_fail (toplevel != NULL);
  toplevel->weak_refs = s_weakref_add_ptr (toplevel->weak_refs,
                                           weak_pointer_loc);
}

/*! \brief Remove a weak pointer from an TOPLEVEL.
 * \par Function Description
 * Removes the weak pointer at \a weak_pointer_loc from \a toplevel.
 *
 * \sa s_toplevel_add_weak_ptr()
 *
 * \param [in,out] toplevel      Toplevel to weak-reference.
 * \param [in] weak_pointer_loc  Memory address of a pointer.
 */
void
s_toplevel_remove_weak_ptr (TOPLEVEL *toplevel,
                            void *weak_pointer_loc)
{
  g_return_if_fail (toplevel != NULL);
  toplevel->weak_refs = s_weakref_remove_ptr (toplevel->weak_refs,
                                              weak_pointer_loc);
}
