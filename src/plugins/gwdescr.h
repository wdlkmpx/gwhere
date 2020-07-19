/*  GWhere.
 *  Copyright (C) 2000  Sébastien LECACHEUR
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


/*!
 * \file gwdescr.h
 * \brief This is the interface specification of description plugins.\n
 * A description plugin \e MUST implements the following functions in order to be
 * used by GWhere as plugin.
 *
 * \author Sébastien LECACHEUR <zero@gwhere.org>
 * \version 1.0
 * \date 2000-2005
 */


#ifndef GW_PLUGINS_DESCR_H
#define GW_PLUGINS_DESCR_H


/*!
 * \brief The function get the author of the plugin.
 * \return The author name.
 * \warning This function is needed.
 */
typedef gchar* (*func_get_author_t)(void);


/*!
 * \brief The function get some information about the plugin.
 * \return The information.
 * \warning This function is needed.
 */
typedef gchar* (*func_get_info_t)(void);


/*!
 * \brief The function get some help about the plugin.
 * \return The help.
 * \warning This function is needed.
 */
typedef gchar* (*func_get_help_t)(void);


/*!
 * \brief The function get a list for file extention supported by the plugin.
 * \return The file extensions list separated by <i>"|"</i>.
 * \warning This function is optional, but it \e MUST implemented with func_get_file_descr_t.
 */
typedef gchar* (*func_get_allowed_ext_t)(void);


/*!
 * \brief The function get a list for file name supported by the plugin.
 * \return The file name list separated by <i>"|"</i>.
 * \warning This function is optional, but it \e MUST implemented with func_get_files_descr_t
 * or func_get_parent_descr_t.
 */
typedef gchar* (*func_get_allowed_name_t)(void);


/*!
 * \brief The function get the file description.
 * \param file_path File path to make description.
 * \param mode Used mode to build description.
 * \return The file description.
 * \warning This function is optional, but it is used only if func_get_allowed_ext_t is
 * implemented.
 */
typedef gchar* (*func_get_file_descr_t)(const char* file_path, const char* mode);


/*!
 * \brief The function get the files description.
 * \param file_path File path to make description.
 * \param mode Used mode to build description.
 * \return All the files description.
 * \warning This function is optional, but it is used only if func_get_allowed_name_t is
 * implemented.
 */
typedef gchar*** (*func_get_files_descr_t)(const char* file_path, const char* mode);


/*!
 * \brief The function get the parent file description.
 * \param file_path File path to make description.
 * \param mode Used mode to build description.
 * \return The parent file description.
 * \warning This function is optional, but it is used only if func_get_allowed_name_t is
 * implemented.
 */
typedef gchar* (*func_get_parent_descr_t)(const char* file_path, const char* mode);


#endif
