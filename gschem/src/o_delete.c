/* gEDA - GPL Electronic Design Automation
 * gschem - gEDA Schematic Capture
 * Copyright (C) 1998-2010 Ales Hvezda
 * Copyright (C) 1998-2011 gEDA Contributors (see ChangeLog for details)
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

#include "gschem.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

/*! \brief Delete an object.
 *  \par Function Description
 *  This function erases the object \a object before deleting it. It
 *  deals with connection and object connected to it.
 *
 *  \param [in] w_current The GSCHEM_TOPLEVEL object.
 *  \param [in] object    The object to delete.
 */
void o_delete (GSCHEM_TOPLEVEL *w_current, OBJECT *object)
{
  TOPLEVEL *toplevel = w_current->toplevel;

  g_return_if_fail (object != NULL);

  o_selection_remove (toplevel, toplevel->page_current->selection_list, object);
  s_page_remove (toplevel, toplevel->page_current, object);
  g_run_hook_object (w_current, "%remove-objects-hook", object);
  s_delete_object (toplevel, object);

  toplevel->page_current->CHANGED = 1;
}

/*! \brief Delete objects from the selection.
 *  \par Function Description
 *  This function deletes the objects selected on the current page of
 *  toplevel \a w_current.
 *
 *  \param [in] w_current The GSCHEM_TOPLEVEL object.
 */
void o_delete_selected (GSCHEM_TOPLEVEL *w_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  SELECTION *selection = toplevel->page_current->selection_list;
  GList *to_remove;
  GList *iter;

  g_return_if_fail (o_select_selected (w_current));

  to_remove = g_list_copy (geda_list_get_glist (selection));

  for (iter = to_remove; iter != NULL; iter = g_list_next (iter)) {
    OBJECT *obj = (OBJECT *) iter->data;
    o_selection_remove (toplevel, selection, obj);
    s_page_remove (toplevel, toplevel->page_current, obj);
  }

  g_run_hook_object_list (w_current, "%remove-objects-hook", to_remove);

  for (iter = to_remove; iter != NULL; iter = g_list_next (iter)) {
    s_delete_object (toplevel, (OBJECT *) iter->data);
  }

  g_list_free (to_remove);

  w_current->inside_action = 0;
  o_undo_savestate (w_current, UNDO_ALL);
  i_update_menus (w_current);
}
