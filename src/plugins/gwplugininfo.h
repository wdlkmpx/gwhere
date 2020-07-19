/*  GWhere
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
 * \file gwplugininfo.h
 * \brief An object for commons plugin information.\n
 * All the plugins \e SHOULD use this object in order to give their own information.
 *
 * \author Sébastien LECACHEUR <zero@gwhere.org>
 * \version 1.0
 * \date 2000-2005
 */


#ifndef GW_PLUGIN_INFO_H
#define GW_PLUGIN_INFO_H


/*!
 * \brief A type definition for the plugin information.\n
 * This type definition is used by all the following functions.
 */
typedef struct gw_plugin_info_s GWPluginInfo;


/*!
 * \brief Allocates a new GWPluginInfo object.\n
 * All the fields are NULL initialized.
 * \return The new allocated GWPluginInfo or NULL if no more memory available.
 */
GWPluginInfo * gw_plugin_info_new ( void);


/*!
 * \brief Sets the name of the plugin.
 * \param plugin_info The plugin to set name.
 * \param name The name to set.
 * \return 0 if the name is correctly setted otherwise -1.
 * \warning The previous setted name is freed even if the given \a name is NULL.
 */
gint gw_plugin_info_set_name ( GWPluginInfo *plugin_info, gchar *name);


/*!
 * \brief Sets the version of the plugin.
 * \param plugin_info The plugin to set version.
 * \param version The version to set.
 * \return 0 if the version is correctly setted otherwise -1.
 * \warning The previous setted version is freed even if the given \a version is NULL.
 */
gint gw_plugin_info_set_version ( GWPluginInfo *plugin_info, gchar *version);


/*!
 * \brief Sets the author of the plugin.
 * \param plugin_info The plugin to set author.
 * \param author The author to set.
 * \return 0 if the author is correctly setted otherwise -1.
 * \warning The previous setted author is freed even if the given \a author is NULL.
 */
gint gw_plugin_info_set_author ( GWPluginInfo *plugin_info, gchar *author);


/*!
 * \brief Sets the description of the plugin.
 * \param plugin_info The plugin to set description.
 * \param description The description to set.
 * \return 0 if the description is correctly setted otherwise -1.
 * \warning The previous setted description is freed even if the given \a description is NULL.
 */
gint gw_plugin_info_set_description ( GWPluginInfo *plugin_info, gchar *description);


/*!
 * \brief Sets the help of the plugin.
 * \param plugin_info The plugin to set help.
 * \param help The help to set.
 * \return 0 if the help is correctly setted otherwise -1.
 * \warning The previous help name is freed even if the given \a help is NULL.
 */
gint gw_plugin_info_set_help ( GWPluginInfo *plugin_info, gchar *help);


/*!
 * \brief Returns the name of the plugin.
 * \param plugin_info The plugin to get name.
 * \return The plugin name if it was setted otherwise NULL.
 */
gchar * gw_plugin_info_get_name ( GWPluginInfo *plugin_info);


/*!
 * \brief Returns the version of the plugin.
 * \param plugin_info The plugin to get version.
 * \return The plugin version if it was setted otherwise NULL.
 */
gchar * gw_plugin_info_get_version ( GWPluginInfo *plugin_info);


/*!
 * \brief Returns the author of the plugin.
 * \param plugin_info The plugin to get author.
 * \return The plugin author if it was setted otherwise NULL.
 */
gchar * gw_plugin_info_get_author ( GWPluginInfo *plugin_info);


/*!
 * \brief Returns the description of the plugin.
 * \param plugin_info The plugin to get description.
 * \return The plugin description if it was setted otherwise NULL.
 */
gchar * gw_plugin_info_get_description ( GWPluginInfo *plugin_info);


/*!
 * \brief Returns the help of the plugin.
 * \param plugin_info The plugin to get help.
 * \return The plugin help if it was setted otherwise NULL.
 */
gchar * gw_plugin_info_get_help ( GWPluginInfo *plugin_info);


/*!
 * \brief Frees the given GWPluginInfo object.
 * \param plugin_info The object to free
 * \warning All the fields are freed to.
 */
gint gw_plugin_info_free ( GWPluginInfo *plugin_info);


#endif
