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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA
 */
#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <math.h>

#include "gschem.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

/* No special type for attributes */
/* You can only edit text attributes */

/* be sure in o_copy o_move o_delete you maintain the attributes */
/* delete is a bare, because you will have to unattach the other end */
/* and in o_save o_read as well */
/* and in o_select when selecting objects, select the attributes */

/* there needs to be a modifier (in struct.h, such as a flag) which
 * signifies that this is an attribute */

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *  Copy all attributes select to the selection list.
 *
 *  \todo get a better name
 */
void o_attrib_add_selected(GSCHEM_TOPLEVEL *w_current, SELECTION *selection,
                           OBJECT *selected)
{
  OBJECT *a_current;
  GList *a_iter;

  g_assert( selection != NULL );

  for (a_iter = selected->attribs; a_iter != NULL;
       a_iter = g_list_next (a_iter)) {
    a_current = a_iter->data;

    /* make sure object isn't selected already */
    if (!a_current->selected) {
      o_selection_add (w_current->toplevel, selection, a_current);
      o_invalidate (w_current, a_current);
    }
  }
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *  Remove all invisible attributes from the selection list.
 *
 *  \todo get a better name
 */
void o_attrib_remove_selected_invisible (GSCHEM_TOPLEVEL *w_current,
                                         SELECTION *selection,
                                         OBJECT *selected)
{
  OBJECT *a_current;
  GList *a_iter;

  g_assert( selection != NULL );

  for (a_iter = selected->attribs; a_iter != NULL;
       a_iter = g_list_next (a_iter)) {
    a_current = a_iter->data;

    if (!w_current->toplevel->show_hidden_text &&
        a_current->visibility == INVISIBLE &&
        a_current->selected) {
      o_selection_remove (w_current->toplevel, selection, a_current);
      o_invalidate (w_current, a_current);
    }
  }
}

/*! \brief Change visibility status of attribute object.
 *  \par Function Description
 *  This function toggles the visibility status of the attribute \a
 *  object and updates it. The object is erased or redrawn if
 *  necessary.
 *
 *  \param [in] w_current  The GSCHEM_TOPLEVEL object.
 *  \param [in] object     The attribute object.
 */
void o_attrib_toggle_visibility(GSCHEM_TOPLEVEL *w_current, OBJECT *object)
{
  TOPLEVEL *toplevel = w_current->toplevel;

  g_return_if_fail (object != NULL && object->type == OBJ_TEXT);

  if (object->visibility == VISIBLE) {
    /* only erase if we are not showing hidden text */
    if (!toplevel->show_hidden_text) {
      o_invalidate (w_current, object);
    }

    object->visibility = INVISIBLE;

    if (toplevel->show_hidden_text) {
      /* draw text so that little I is drawn */
      o_invalidate (w_current, object);
    }

  } else {
    /* if we are in the special show hidden mode, then erase text first */
    /* to get rid of the little I */
    if (toplevel->show_hidden_text) {
      o_invalidate (w_current, object);
    }

    object->visibility = VISIBLE;
    o_text_recreate(toplevel, object);

    o_invalidate (w_current, object);
  }

  toplevel->page_current->CHANGED = 1;
}

/*! \brief Set what part of an attribute is shown.
 *  \par Function Description
 *  This function changes what part (name, value or both) of an
 *  attribute is shown by its attribute object. The attribute object
 *  is erased, updated and finally redrawn.
 *
 *  \param [in] w_current  The GSCHEM_TOPLEVEL object.
 *  \param [in] object     The attribute object.
 *  \param [in] show_name_value  The new display flag for attribute.
 */
void o_attrib_toggle_show_name_value(GSCHEM_TOPLEVEL *w_current,
                                     OBJECT *object, int show_name_value)
{
  TOPLEVEL *toplevel = w_current->toplevel;

  g_return_if_fail (object != NULL && object->type == OBJ_TEXT);

  o_invalidate (w_current, object);
  object->show_name_value = show_name_value;
  o_text_recreate(toplevel, object);
  o_invalidate (w_current, object);

  toplevel->page_current->CHANGED = 1;
}


/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
/* This function no longer returns NULL, but will always return the new */
/* text item */
OBJECT *o_attrib_add_attrib(GSCHEM_TOPLEVEL *w_current,
			    const char *text_string, int visibility, 
			    int show_name_value, OBJECT *object)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  OBJECT *new_obj;
  int world_x = - 1, world_y = -1;
  int color; 
  int left, right, top, bottom;
  OBJECT *o_current;

  color = DETACHED_ATTRIBUTE_COLOR;

  o_current = object;

  /* creating a toplevel or unattached attribute */
  if (o_current) {
    /* get coordinates of where to place the text object */
    switch(o_current->type) {
      case(OBJ_COMPLEX):
      case(OBJ_PLACEHOLDER):
        world_x = o_current->complex->x;
        world_y = o_current->complex->y;
        color = ATTRIBUTE_COLOR;
        break;

      case(OBJ_ARC):
        world_x = o_current->arc->x;
        world_y = o_current->arc->y;
        color = ATTRIBUTE_COLOR;
        break;

      case(OBJ_CIRCLE):
        world_x = o_current->circle->center_x;
        world_y = o_current->circle->center_y;
        color = ATTRIBUTE_COLOR;
        break;

      case(OBJ_BOX):
        world_x = o_current->box->upper_x;
        world_y = o_current->box->upper_y;
        color = ATTRIBUTE_COLOR;
        break;

      case(OBJ_LINE):
      case(OBJ_NET):
      case(OBJ_PIN):
      case(OBJ_BUS):
        world_x = o_current->line->x[0];
        world_y = o_current->line->y[0];
        color = ATTRIBUTE_COLOR;
        break;

      case(OBJ_TEXT):

        world_x = o_current->text->x;
        world_y = o_current->text->y;
			
        color = DETACHED_ATTRIBUTE_COLOR;

	o_current = NULL;
        break;
    }
  } else {
    world_get_object_glist_bounds (toplevel,
                                   s_page_objects (toplevel->page_current),
                                   &left, &top, &right, &bottom);
	
    /* this really is the lower left hand corner */	
    world_x = left; 
    world_y = top;  

    /* printf("%d %d\n", world_x, world_y); */
    color = DETACHED_ATTRIBUTE_COLOR;
  }

  /* first create text item */
  new_obj = o_text_new(toplevel, OBJ_TEXT, color, world_x, world_y,
             LOWER_LEFT, 0, /* zero is angle */
             text_string,  w_current->text_size,  /* current text size */
             visibility, show_name_value);
  s_page_append (toplevel, toplevel->page_current, new_obj);

  /* now attach the attribute to the object (if o_current is not NULL) */
  /* remember that o_current contains the object to get the attribute */
  if (o_current) {
    o_attrib_attach (toplevel, new_obj, o_current, FALSE);
  }

  o_selection_add (toplevel, toplevel->page_current->selection_list, new_obj);

  o_invalidate (w_current, new_obj);

  /* handle slot= attribute, it's a special case */
  if (o_current != NULL &&
      g_ascii_strncasecmp (text_string, "slot=", 5) == 0) {
    o_slot_end (w_current, o_current, text_string);
  }

  /* Run the add attribute hook */
  if (scm_hook_empty_p(add_attribute_hook) == SCM_BOOL_F &&
      o_current != NULL) {
    scm_run_hook (add_attribute_hook,
                  scm_cons (g_make_object_smob (toplevel, o_current),
                            SCM_EOL));
  }

  toplevel->page_current->CHANGED = 1;

  return new_obj;
}
