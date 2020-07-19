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


#include "../gwsupport.h"

#include <string.h> /* strcmp */


#define GW_STRING_BUFFER_CAN_CONTAINS(p,l) (p->size > l)


typedef struct string_buffer_s
{
	gulong size; /* This is the allocated size of the string buffer. */
	gulong length; /* This is the current string buffer length. */
	gchar *buff; /* The pointer to the string contained by the string buffer. */
} GWStringBuffer;


GWStringBuffer * gw_string_buffer_new ( void)
{
	GWStringBuffer *p = NULL;
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif


	/* Allocates a new GWStringBuffer. The initial capacity is 0 and the initial
	   string is NULL. */
	if ( (p = (GWStringBuffer*)g_malloc0 ( sizeof ( GWStringBuffer))) != NULL )
	{
		p->size = 0;
		p->length = 0;
		p->buff = NULL;
	}

	return p;
}


gulong gw_string_buffer_resize ( GWStringBuffer *p, gulong newsize)
{
	gchar *ptr = NULL;
	gulong result = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p  != NULL )
	{
		/* This function can only increase the string capacity, not decrease. */
		if ( newsize >= p->size )
		{
			if ( p->buff != NULL )
			{
				/* Realloc the string buffer memory. And sets to '\0' all
				   the new allocated memory. */
				ptr = (gchar*)g_realloc ( p->buff, sizeof ( gchar)*(newsize+1));

				if ( ptr != NULL )
				{
					p->buff = ptr;
					memset(&p->buff[p->size+1],'\0',newsize-p->size);
					result = newsize + 1;
				}
				else
				{
					result = 0;
				}
			}
			else
			{
				if ( (p->buff = (gchar*)g_malloc0 ( sizeof ( gchar)*(newsize+1))) != NULL )
				{
					result = newsize + 1;
				}
				else
				{
					result = 0;
				}
			}

			p->size = result;
		}
	}

	return result;
}


gulong gw_string_buffer_delete ( GWStringBuffer *p, gulong start, gulong end)
{
	gchar *first = NULL;
	gulong first_index = 0;
	gchar *last = NULL;
	gulong last_index = 0;
	gulong result = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p  != NULL )
	{
		/* If start is greater than end, negative, greater than length or if
		   the size is 0 no changes are made. */
		if ( (start < end) && (start >= 0) && (start<=p->length) && (p->size > 0) )
		{
			/* The first character to delete is at the start position
			   the last character to delete is at the end - 1 position if
			   end is smaller than length or at the length position. */
			first_index = start;
			first = p->buff + first_index;
			last_index = (end<p->length?end-1:p->length);
			last = p->buff + last_index;
			result = last_index - first_index;
			memmove ( first, last+1, p->length - last_index);
			memset ( &p->buff[p->length-result], '\0', result-1);
			p->length = p->length - result;
		}
		else
		{
			result = 0;
		}
	}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : size=%lu len=%lu str=%s deleted=%lu\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,p->size,p->length,p->buff,result);
#endif

	return result;
}


gulong gw_string_buffer_delete_all ( GWStringBuffer *p)
{
	gulong result = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		result = gw_string_buffer_delete ( p, 0, p->length);
	}

	return result;
}


void gw_string_buffer_set_str ( GWStringBuffer *p, gchar *str, gulong len)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		/* If the string buffer cannot contains the specified string,
		   his size must be increase. */
		if (!GW_STRING_BUFFER_CAN_CONTAINS(p,len))
		{
			gw_string_buffer_resize ( p, len);
		}

		if ( str != NULL )
		{
			/* If the specified string his different from NULL, copies
			it in the string buffer. */
			memcpy ( p->buff, str, len);
			p->buff[len] = '\0';
			p->length = len;
		}
		else
		{
			/* Otherwize set the empty string in the string
			   buffer. */
			memset ( p->buff, '\0', p->length);
			p->length = 0;
		}
	}

	return;
}


void gw_string_buffer_append_str ( GWStringBuffer *p, gchar *str, gulong len)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif


	/* Doesn't add any character if the str parameter is NULL. */
	if ( (p != NULL) && (str != NULL))
	{
		/* Checks if the current string buffer can contain the
		   given string to append. */
		if (!GW_STRING_BUFFER_CAN_CONTAINS(p,p->length+len))
		{
			/* Resizes the string buffer if the sum of the current
			   string buffer length and the number of caracters to
			   add to this one is bigger than the string buffer
			   capacity. */
			gw_string_buffer_resize ( p, p->length + len);
		}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s(): size=%lu len=%lu\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,p->size,p->length);
#endif

		/* Checks if the current string buffer really can contain
		   the given string to append. */
		if (GW_STRING_BUFFER_CAN_CONTAINS(p,p->length+len))
		{
			/* The appending is a copy of the given string to
			   the end of the string buffer. This copy copies
			   only the number of characters given by the len
			   parameter. After increases the string buffer
			   length and doesn't forget to add the ending
			   '\0' character. */
			memcpy ( &(p->buff[p->length]), str, len);
			p->length+=len;
			p->buff[p->length] = '\0';
		}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s(): size=%lu len=%lu\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,p->size,p->length);
#endif

	}

	return;
}


void gw_string_buffer_insert_str ( GWStringBuffer *p, gchar *str, gulong start, gulong len)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif


	/* Doesn't add any character if the str parameter is NULL. */
	if ( (p != NULL) && (str != NULL) )
	{
		/* Checks if the index position where the string must be inserted
		   is valid. */
		if ( (start >= 0) && (start <= p->length) )
		{
			/* Checks if the current string buffer can contain the
			given string to append. */
			if (!GW_STRING_BUFFER_CAN_CONTAINS(p,p->length+len))
			{
				/* Resizes the string buffer if the sum of the current
				string buffer length and the number of caracters to
				add to this one is bigger than the string buffer
				capacity. */
				gw_string_buffer_resize ( p, p->length + len);
			}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s(): size=%lu len=%lu\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,p->size,p->length);
#endif

			/* Checks if the current string buffer really can contain
			the given string to insert. */
			if (GW_STRING_BUFFER_CAN_CONTAINS(p,p->length+len))
			{
				/* The insert is a copy of the given string to
				the specified offset of the string buffer. This
				copy copies only the number of characters given
				by the len parameter. After increases the string
				buffer length and doesn't forget to add the ending
				'\0' character. */
				memmove ( &(p->buff[start+len]), &(p->buff[start]), (p->length - start));
				memcpy ( &(p->buff[start]), str, len);
				p->length+=len;
				p->buff[p->length] = '\0';
			}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s(): size=%lu len=%lu\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,p->size,p->length);
#endif

		}
	}

	return;
}


void gw_string_buffer_replace_str ( GWStringBuffer *p, gchar *str, gulong start, gulong len)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p  != NULL )
	{
		if ( (start >= 0) && ( start < p->length) )
		{
			/* Checks if the current string buffer can contain the
			given string to use. */
			if (!GW_STRING_BUFFER_CAN_CONTAINS(p,start+len))
			{
				/* Resizes the string buffer if the sum of the current
				string buffer length and the number of caracters to
				add to this one is bigger than the string buffer
				capacity. */
				gw_string_buffer_resize ( p, start + len);
			}

			/* Checks if the current string buffer can contain the
			given string to use. */
			if (!GW_STRING_BUFFER_CAN_CONTAINS(p,p->length+len))
			{
				/* The replace is a copy of the given string to
				the specified offset of the string buffer. This
				copy copies only the number of characters given
				by the len parameter. After increases the string
				buffer length and doesn't forget to add the ending
				'\0' character. */
				memcpy ( &p->buff[start], str, len);
				if ( p->length < (start + len) )
				{
					p->length = start + len;
					p->buff[p->length] = '\0';
				}
			}
		}
	}

	return;
}


void gw_string_buffer_replace_chr ( GWStringBuffer *p, gchar chr, gulong index)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p  != NULL )
	{
		if ( (index >= 0) && (index < p->length) )
		{
			p->buff[index] = chr;
		}
	}

	return;
}


gchar * gw_string_buffer_get_str ( GWStringBuffer *p)
{
	gchar * str = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->length >= 0 )
		{
			str = p->buff;
		}
	}

#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : str=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,str);
#endif

	return str;
}


gulong gw_string_buffer_get_size ( GWStringBuffer *p)
{
	gulong size = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		size = p->size;
	}

	return size;
}


void gw_string_buffer_free ( GWStringBuffer *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif


	if ( p != NULL )
	{
		if ( p->buff != NULL )
		{
			g_free ( p->buff);
		}

		g_free ( p);
	}

	return;
}

#undef GW_DEBUG_DATA_COMPONENT
