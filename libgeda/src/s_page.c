/* gEDA - GPL Electronic Design Automation
 * libgeda - gEDA's library
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

/*! \file s_page.c
 *  \brief The page system
 *
 *  libgeda can handle multiple schematic or symbol pages. libgeda keeps 
 *  track of the currently opened pages with a managed _GedaList.
 *  The currently used page is refered with an extra pointer.
 *
 *  Each page carries a list of the objects that are on the page.
 *  The first and the last element are referenced by the head and tail
 *  pointers.
 *
 *  \image html s_page_overview.png
 *  \image latex s_page_overview.pdf "page overview" width=14cm
 */

#include <config.h>

#include <stdio.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libgeda_priv.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

static gint global_pid = 0;

/*! \brief create a new page object
 *  \par Function Description
 *  Creates a new page and add it to <B>toplevel</B>'s list of pages.
 *
 *  It initializes the #PAGE structure and set its <B>page_filename</B>
 *  to <B>filename</B>. <B>toplevel</B>'s current page is not changed by
 *  this function.
 */
PAGE *s_page_new (TOPLEVEL *toplevel, const gchar *filename)
{
  PAGE *page;

  /* Now create a blank page */
  page = (PAGE*)g_new0 (PAGE, 1);

  page->pid = global_pid++;

  page->CHANGED = 0;

  /* big assumption here that page_filename isn't null */
  if (g_path_is_absolute (filename)) {
    page->page_filename = g_strdup (filename);
  } else {
    gchar *pwd = g_get_current_dir ();
    page->page_filename = g_build_filename (pwd, filename, NULL);
    g_free (pwd);
  }
	
  g_assert (toplevel->init_bottom != 0);
  page->coord_aspectratio = (
    ((float) toplevel->init_right) / ((float) toplevel->init_bottom));

  page->up = -2;
  page->page_control = 0;

  /* Init tile array */
  s_tile_init (toplevel, page);

  /* Init the object list */
  page->_object_list = NULL;

  /* new selection mechanism */
  page->selection_list = o_selection_new();

  /* net/pin/bus stretch when doing moves */
  page->stretch_list = NULL;

  page->place_list = NULL;

  /* init undo struct pointers */
  s_undo_init(page);
  
  page->object_lastplace = NULL;
  
  set_window (toplevel, page,
              toplevel->init_left, toplevel->init_right,
              toplevel->init_top,  toplevel->init_bottom);

  /* Backup variables */
  g_get_current_time (&page->last_load_or_save_time);
  page->ops_since_last_backup = 0;
  page->saved_since_first_loaded = 0;
  page->do_autosave_backup = 0;

  /* now append page to page list of toplevel */
  geda_list_add( toplevel->pages, page );

  return page;
}

/*! \brief delete a page and it's contents
 *  \par Function Description
 *  Deletes a single page <B>page</B> from <B>toplevel</B>'s list of pages.
 *
 *  See #s_page_delete_list() to delete all pages of a <B>toplevel</B>
 *
 *  If the current page of toplevel is given as parameter <B>page</B>,
 *  the function sets the field <B>page_current</B> of the TOPLEVEL
 *  struct to NULL.
 */
void s_page_delete (TOPLEVEL *toplevel, PAGE *page)
{
  PAGE *tmp;
  gchar *backup_filename;
  gchar *real_filename;

  /* We need to temporarily make the page being deleted current because
   * various functions called below (some indirectly) assume they are
   * deleting objects from the current page.
   *
   * These functions are known to include:
   *   s_delete_object ()
   */

  /* save page_current and switch to page */
  if (page == toplevel->page_current) {
    tmp = NULL;
  } else {
    tmp = toplevel->page_current;
    s_page_goto (toplevel, page);
  }

  /* Get the real filename and file permissions */
  real_filename = follow_symlinks (page->page_filename, NULL);
  
  if (real_filename == NULL) {
    s_log_message (_("s_page_delete: Can't get the real filename of %s."),
                   page->page_filename);
  }
  else {
    backup_filename = f_get_autosave_filename (real_filename);

    /* Delete the backup file */
    if ( (g_file_test (backup_filename, G_FILE_TEST_EXISTS)) && 
	 (!g_file_test(backup_filename, G_FILE_TEST_IS_DIR)) )
    {
      if (unlink(backup_filename) != 0) {
	s_log_message(_("s_page_delete: Unable to delete backup file %s."),
                      backup_filename);
      }
    }
    g_free (backup_filename);
  }
  g_free(real_filename);

  /* Free the selection object */
  g_object_unref( page->selection_list );

  /* then delete objects of page */
  s_page_delete_objects (toplevel, page);

  /* Free the objects in the place list. */
  s_delete_object_glist (toplevel, page->place_list);
  page->place_list = NULL;

#if DEBUG
  printf("Freeing page: %s\n", page->page_filename);
  s_tile_print(toplevel);
#endif
  s_tile_free_all (page);

  s_stretch_destroy_all (page->stretch_list);

  /* free current page undo structs */
  s_undo_free_all (toplevel, page); 

  /* ouch, deal with parents going away and the children still around */
  page->up = -2;
  g_free (page->page_filename);

  geda_list_remove( toplevel->pages, page );

#if DEBUG
  s_tile_print (toplevel);
#endif

  g_free (page);

  /* restore page_current */
  if (tmp != NULL) {
    s_page_goto (toplevel, tmp);
  } else {
    /* page was page_current */
    toplevel->page_current = NULL;
    /* page_current must be updated by calling function */
  }

}


/*! \brief Deletes the list of pages of <B>toplevel</B>.
 *  \par Function Description
 *  Deletes the list of pages of <B>toplevel</B>.
 *  This function should only be called when you are finishing up.
 *
 *  \param toplevel  The TOPLEVEL object.
 */
void s_page_delete_list(TOPLEVEL *toplevel)
{
  GList *list_copy, *iter;
  PAGE *page;

  /* s_page_delete removes items from the page list, so make a copy */
  list_copy = g_list_copy (geda_list_get_glist (toplevel->pages));

  for (iter = list_copy; iter != NULL; iter = g_list_next (iter)) {
    page = (PAGE *)iter->data;

    s_page_delete (toplevel, page);
  }

  g_list_free (list_copy);

  /* reset toplevel fields */
  toplevel->page_current = NULL;
}

/*! \brief changes the current page in toplevel
 *  \par Function Description
 *  Changes the current page in \a toplevel to the page \a p_new.
 *
 *  \param toplevel  The TOPLEVEL object
 *  \param p_new     The PAGE to go to
 */
void s_page_goto (TOPLEVEL *toplevel, PAGE *p_new) 
{
  gchar *dirname;

  toplevel->page_current = p_new;

  dirname = g_dirname (p_new->page_filename);
  if (chdir (dirname)) {
    /* An error occured with chdir */
#warning FIXME: What do we do?
  }
  g_free (dirname);

}

/*! \brief Search for pages by filename.
 *  \par Function Description
 *  Searches in \a toplevel's list of pages for a page with a filename
 *  equal to \a filename.
 *
 *  \param toplevel  The TOPLEVEL object
 *  \param filename  The filename string to search for
 *  
 *  \return PAGE pointer to a matching page, NULL otherwise.
 */
PAGE *s_page_search (TOPLEVEL *toplevel, const gchar *filename)
{
  const GList *iter;
  PAGE *page;

  for ( iter = geda_list_get_glist( toplevel->pages );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    page = (PAGE *)iter->data;
    if ( g_strcasecmp( page->page_filename, filename ) == 0 )
      return page;
  }
  return NULL;
}

/*! \brief Search for a page given its page id in a page list.
 *  \par Function Description
 *  This functions returns the page that have the page id \a pid in
 *  the list of pages starting at \a page_list, or NULL if there is no
 *  such page.
 *
 *  \param [in] list      The list of page to search the page in.
 *  \param [in] pid       The ID of the page to find.
 *  \returns A pointer on the page found or NULL if not found.
 */
PAGE *s_page_search_by_page_id (GedaPageList *list, int pid)
{
  const GList *iter;

  for ( iter = geda_list_get_glist (list);
        iter != NULL;
        iter = g_list_next (iter) ) {
    PAGE *page = (PAGE *)iter->data;
    if (page->pid == pid) {
      return page;
    }
  }

  return NULL;
}

/*! \brief Print full TOPLEVEL structure.
 *  \par Function Description
 *  This function prints the internal structure of <B>toplevel</B>'s
 *  list of pages.
 *
 *  \param [in] toplevel  The TOPLEVEL object to print.
 */
void s_page_print_all (TOPLEVEL *toplevel)
{
  const GList *iter;
  PAGE *page;

  for ( iter = geda_list_get_glist( toplevel->pages );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    page = (PAGE *)iter->data;
    printf ("FILENAME: %s\n", page->page_filename);
    print_struct_forw (page->_object_list);
  }
}

/*! \brief Saves all the pages of a TOPLEVEL object.
 *  \par Function Description
 *  Saves all the pages in the <B>toplevel</B> parameter.
 *
 *  \param [in] toplevel  The TOPLEVEL to save pages from.
 *  \return The number of failed tries to save a page.
 */
gint s_page_save_all (TOPLEVEL *toplevel)
{
  const GList *iter;
  PAGE *p_save, *p_current;
  gint status = 0;

  /* save current page */
  p_save = toplevel->page_current;

  for ( iter = geda_list_get_glist( toplevel->pages );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    p_current = (PAGE *)iter->data;

    /* make p_current the current page of toplevel */
    s_page_goto (toplevel, p_current);

    if (f_save (toplevel, p_current->page_filename)) {
      s_log_message (_("Saved [%s]\n"),
                     toplevel->page_current->page_filename);
      /* reset the CHANGED flag of p_current */
      p_current->CHANGED = 0;

    } else {
      s_log_message (_("Could NOT save [%s]\n"),
                     toplevel->page_current->page_filename);
      /* increase the error counter */
      status++;
    }

  }

  /* restore current page */
  if (p_save != NULL) 
  {
     s_page_goto (toplevel, p_save);
  }

  return status;
}

/*! \brief Check if CHANGED flag is set for any page in list.
 *  \par Function Description
 *  This function checks the CHANGED flag for all pages in the <B>list</B>
 *  object.
 *
 *  \param [in] list  GedaPageList to check CHANGED flag in.
 *  \return 1 if any page has the CHANGED flag set, 0 otherwise.
 */
gboolean s_page_check_changed (GedaPageList *list)
{
  const GList *iter;
  PAGE *p_current;

  for ( iter = geda_list_get_glist( list );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    p_current = (PAGE *)iter->data;
    if (p_current->CHANGED) {
      return TRUE;
    }
  }

  return FALSE;
}

/*! \brief Reset the CHANGED flag of all pages.
 *  \par Function Description
 *  This function resets the CHANGED flag of each page following \a head.
 *
 *  \param [in,out] list  PAGE list to set CHANGED flags in.
 */
void s_page_clear_changed (GedaPageList *list)
{
  const GList *iter;
  PAGE *p_current;

  for ( iter = geda_list_get_glist( list );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    p_current = (PAGE *)iter->data;
    p_current->CHANGED = 0;
  }
}

/*! \brief Autosave initialization function.
 *  \par Function Description
 *  This function sets up the autosave callback function.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 */
void s_page_autosave_init(TOPLEVEL *toplevel)
{
  if (toplevel->auto_save_interval != 0) {

    /* 1000 converts seconds into milliseconds */
    toplevel->auto_save_timeout = 
      g_timeout_add(toplevel->auto_save_interval*1000,
                    (GSourceFunc) s_page_autosave,
                    toplevel);
  }
}

/*! \brief Autosave callback function.
 *  \par Function Description
 *  This function is a callback of the glib g_timeout functions.
 *  It is called every "interval" milliseconds and it sets a flag to save
 *  a backup copy of the opened pages.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \return The length in milliseconds to set for next interval.
 */
gint s_page_autosave (TOPLEVEL *toplevel) 
{
  const GList *iter;
  PAGE *p_current;

  if (toplevel == NULL) {
    return 0;
  }

  /* Do nothing if the interval is 0 */
  if (toplevel->auto_save_interval == 0) {
    return toplevel->auto_save_interval;
  }

  /* Should we just disable the autosave timeout returning 0 or
     just wait for more pages to be added? */
  if ( toplevel->pages == NULL)
    return toplevel->auto_save_interval;

  for ( iter = geda_list_get_glist( toplevel->pages );
        iter != NULL;
        iter = g_list_next( iter ) ) {

    p_current = (PAGE *)iter->data;

    if (p_current->ops_since_last_backup != 0) {
      /* Real autosave is done in o_undo_savestate */
      p_current->do_autosave_backup = 1;
    }
  }

  return toplevel->auto_save_interval;
}

/*! \brief Append an OBJECT to the PAGE
 *
 *  \par Function Description
 *  Links the passed OBJECT to the end of the PAGE's
 *  linked list of objects.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE the object is being added to.
 *  \param [in] object    The OBJECT being added to the page.
 */
void s_page_append (TOPLEVEL *toplevel, PAGE *page, OBJECT *object)
{
  page->_object_list = g_list_append (page->_object_list, object);
}

/*! \brief Append a GList of OBJECTs to the PAGE
 *
 *  \par Function Description
 *  Links the passed OBJECT GList to the end of the PAGE's
 *  object_list.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE the objects are being added to.
 *  \param [in] obj_list  The OBJECT list being added to the page.
 */
void s_page_append_list (TOPLEVEL *toplevel, PAGE *page, GList *obj_list)
{
  page->_object_list = g_list_concat (page->_object_list, obj_list);
}

/*! \brief Remove an OBJECT from the PAGE
 *
 *  \par Function Description
 *  Removes the passed OBJECT from the PAGE's
 *  linked list of objects.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE the object is being removed from.
 *  \param [in] object    The OBJECT being removed from the page.
 */
void s_page_remove (TOPLEVEL *toplevel, PAGE *page, OBJECT *object)
{
  page->_object_list = g_list_remove (page->_object_list, object);
}

/*! \brief Remove and free all OBJECTs from the PAGE
 *
 *  \par Function Description
 *  Removes and frees all OBJECTs from the PAGE.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE being cleared.
 */
void s_page_delete_objects (TOPLEVEL *toplevel, PAGE *page)
{
  s_delete_object_glist (toplevel, page->_object_list);
  page->_object_list = NULL;
}


/*! \brief Return a GList of OBJECTs on the PAGE
 *
 *  \par Function Description
 *  An accessor for the PAGE's GList of objects.
 *
 *  NB: This GList is owned by the PAGE, and must not be
 *      free'd or modified by the caller.
 *
 *  \param [in] page      The PAGE to get objects on.
 *  \returns a const pointer to the PAGE's GList of objects
 */
const GList *s_page_objects (PAGE *page)
{
  return page->_object_list;
}


/*! \brief Find the objects in a given region
 *
 *  \par Function Description
 *  Finds the objects which are inside, or intersect
 *  the passed box shaped region.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE to find objects on.
 *  \param [in] min_x     The smaller X coordinate of the region.
 *  \param [in] min_y     The smaller Y coordinate of the region.
 *  \param [in] max_x     The larger  X coordinate of the region.
 *  \param [in] max_y     The larger  Y coordinate of the region.
 *  \return The GList of OBJECTs in the region.
 */
GList *s_page_objects_in_region (TOPLEVEL *toplevel, PAGE *page,
                                 int min_x, int min_y, int max_x, int max_y)
{
  BOX rect;

  rect.lower_x = min_x;
  rect.lower_y = min_y;
  rect.upper_x = max_x;
  rect.upper_y = max_y;

  return s_page_objects_in_regions (toplevel, page, &rect, 1);
}

/*! \brief Find the objects in a given region
 *
 *  \par Function Description
 *  Finds the objects which are inside, or intersect
 *  the passed box shaped region.
 *
 *  \param [in] toplevel  The TOPLEVEL object.
 *  \param [in] page      The PAGE to find objects on.
 *  \param [in] rects     The BOX regions to check.
 *  \param [in] n_rects   The number of regions.
 *  \return The GList of OBJECTs in the region.
 */
GList *s_page_objects_in_regions (TOPLEVEL *toplevel, PAGE *page,
                                  BOX *rects, int n_rects)
{
  GList *iter;
  GList *list = NULL;
  int i;

  for (iter = page->_object_list; iter != NULL; iter = g_list_next (iter)) {
    OBJECT *object = iter->data;

    for (i = 0; i < n_rects; i++) {
      int left, top, right, bottom;

      if (world_get_single_object_bounds (toplevel, object,
                                          &left, &top, &right, &bottom) &&
          right  >= rects[i].lower_x &&
          left   <= rects[i].upper_x &&
          top    <= rects[i].upper_y &&
          bottom >= rects[i].lower_y) {
        list = g_list_prepend (list, object);
        break;
      }
    }
  }

  list = g_list_reverse (list);
  return list;
}
