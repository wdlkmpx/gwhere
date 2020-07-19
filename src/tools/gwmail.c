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


#include "../gwsupport.h"
#include "gwmail.h"
#include "gwfile.h"

#include <sys/types.h>
#if defined ( OS_WIN32)
  /*#include <winsock.h>*/ /* gethostbyname */
  #include <winsock2.h> /* gethostbyname */
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <netdb.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* strcat strncmp */

#define MAX_MSG 5000
#define BOUNDARY "=-=Pipocrouch=-="
#define DEBUG 0


/* Table for base 64 encoding */
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                  "0123456789+/";
char rcv_msg[MAX_MSG]; /* Reception buffer */


int gw_mail_check_msg ( char * msg, char * code)
{
#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : server message=%s, error code=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, code);
#endif

	return strncmp ( msg, code, 3)==0?1:0;
}


int gw_mail_read_msg ( int sd)
{
	int result = -1;
	int n;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	memset ( rcv_msg, 0x0, MAX_MSG);
	n = recv ( sd, rcv_msg, MAX_MSG, 0);

 	if ( n < 0 )
	{
		perror ( _( "Cannot receive data"));

		result = -1;
	}
	else if ( n == 0 )
	{
		perror ( _( "Connexion closed by client\n"));
		close ( sd);

		result = -1;
	}
	else
	{
		result = 0;
	}

	return result;
}


int gw_mail_send_msg ( int sd, char * msg)
{
	int result = -1;
	int rc;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	strcat ( msg, "\r\n");
	rc = send ( sd, msg, strlen ( msg), 0);

  	if ( rc < 0 )
	{
    		perror ( _( "Cannot send data"));
    		close ( sd);

    		result = -1;
  	}
  	else
  	{
  		result = 0;
  	}

	return result;
}


int gw_mail_attachment_encode_base64_and_send ( int sd, char * file )
{
	int result = -1;
	char buf[80];
	unsigned long  value;
	int shift = 0;
	int save_shift = 0;
	int accum = 0;
	int index = 0;
	int quit=0;
	FILE * fin;
	unsigned char blivit;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens file. */
	if ( (fin = fopen ( file, "rb")) != NULL )
	{
		/* Beginning of reading. */
		while ( ( !feof ( fin) ) || ( shift != 0 ) )
		{
			if ( ( !feof ( fin) ) && ( quit == 0 ) )
			{
				blivit = fgetc ( fin);

				if ( feof ( fin) )
				{
					quit = 1;
					save_shift = shift;
					blivit = 0;
				}
			}
			else
			{
				quit = 1;
				save_shift = shift;
				blivit = 0;
			}

			if ( ( quit == 0 ) || ( shift != 0 ) )
			{
				value = (unsigned long)blivit;
				accum <<= 8;
				shift += 8;
				accum |= value;
			}

			while ( shift >= 6 )
			{
				shift -= 6;
				value = (accum >> shift) & 0x3Fl;
				blivit = alphabet[value];

				buf[index++] = blivit;

				if ( index >= 60 )
				{
					buf[index] = '\0';

					send ( sd, buf, strlen ( buf), 0);
					send ( sd, "\n", 1, 0);

					index = 0;
				}

				if ( quit != 0 )
				{
					shift = 0;
				}
			}
		}

		if ( save_shift == 2 )
		{
			buf[index++] = '=';

			if ( index >= 60 )
			{
				buf[index] = '\0';

				send ( sd, buf, strlen ( buf), 0);
				send ( sd, "\n", 1, 0);

				index = 0;
			}

			buf[index++] = '=';

			if ( index >= 60 )
			{
				buf[index] = '\0';

				send ( sd, buf, strlen ( buf), 0);
				send ( sd, "\n", 1, 0);

				index = 0;
			}
		}
		else if ( save_shift == 4 )
		{
			buf[index++] = '=';

			if ( index >= 60 )
			{
				buf[index] = '\0';

				send ( sd, buf, strlen ( buf), 0);
				send ( sd, "\n", 1, 0);

				index = 0;
			}
		}

		if ( index != 0)
		{
			buf[index] = '\0';

			send ( sd, buf, strlen ( buf), 0);
			send ( sd, "\n", 1, 0);
		}

		/* Closes file. */
		fclose ( fin);

		result = 0;
	}

	return result;
}


int gw_mail_send_mail ( char * hostname, int server_port, char * from, char * to, char * cc, char * bcc, char * object, char * msg, char * file)
{
	int rc;
	struct sockaddr_in localAddr, servAddr;
	struct hostent *h = NULL;
	char commande[MAX_MSG];
	int sd;
	char * filename = NULL;
#if defined ( OS_WIN32)
	WSADATA wsd; 
#endif


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
	g_print ( "*** GW - %s (%d) :: %s() : hostname=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, hostname);
	g_print ( "*** GW - %s (%d) :: %s() : server_port=%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, server_port);
	g_print ( "*** GW - %s (%d) :: %s() : from=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, from);
	g_print ( "*** GW - %s (%d) :: %s() : to=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, to);
	g_print ( "*** GW - %s (%d) :: %s() : cc=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, cc);
	g_print ( "*** GW - %s (%d) :: %s() : bcc=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, bcc);
	g_print ( "*** GW - %s (%d) :: %s() : object=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, object);
	g_print ( "*** GW - %s (%d) :: %s() : message=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg);
	g_print ( "*** GW - %s (%d) :: %s() : file=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, file);
#endif


#if defined ( OS_WIN32)
	if ( WSAStartup ( MAKEWORD ( 2, 2), &wsd) != 0)
	{
    		perror ( "Couldn't start winsock");

    		return -1;
	}
#endif


	if ( (h = gethostbyname ( hostname)) != NULL )
	{
		servAddr.sin_family = h->h_addrtype;
		memcpy ( (char *)&servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
		servAddr.sin_port = htons ( server_port);

		/* Creates socket. */
		sd = socket ( AF_INET, SOCK_STREAM, 0);

		if ( sd >= 0 )
		{
			/* Bind the port. */
			localAddr.sin_family = AF_INET;
			localAddr.sin_addr.s_addr = htonl ( INADDR_ANY);
			localAddr.sin_port = htons ( 0);

			rc = bind ( sd, (struct sockaddr *) &localAddr, sizeof ( localAddr));

			if ( rc >= 0 )
			{
				/* Connects to the server. */
				rc = connect ( sd, (struct sockaddr *) &servAddr, sizeof ( servAddr));

				if ( rc >= 0 )
				{
					/* Reads data in socket. */
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "220") )
					{
						perror ( "Invalid server");
					}

					strcpy ( commande, "HELO ");
					strcat ( commande, hostname);
					gw_mail_send_msg ( sd, commande);
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "250") )
					{
						perror ( "Invalid server");
					}

					strcpy ( commande, "MAIL FROM: ");
					strcat ( commande, from);
					gw_mail_send_msg ( sd, commande);
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "250") )
					{
						perror ( "Invalid shipper");
					}

					strcpy ( commande, "RCPT TO: ");
					strcat ( commande, to);
					gw_mail_send_msg ( sd, commande);
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "250") )
					{
						perror ( "Invalid recipient");
					}

					if ( cc != NULL )
					{
						if ( strlen ( cc) > 1 )
						{
							strcpy ( commande, "RCPT TO: ");
							strcat ( commande, cc);
							gw_mail_send_msg ( sd, commande);
							gw_mail_read_msg ( sd);

							if ( !gw_mail_check_msg ( rcv_msg, "250") )
							{
								perror ( "Invalid recipient");
							}
						}
					}

					if ( bcc != NULL )
					{
						if ( strlen ( bcc) > 1 )
						{
							strcpy ( commande, "RCPT TO: ");
							strcat ( commande, bcc);
							gw_mail_send_msg ( sd, commande);
							gw_mail_read_msg ( sd);

							if ( !gw_mail_check_msg ( rcv_msg, "250") )
							{
								perror ( "Invalid recipient");
							}
						}
					}

					strcpy ( commande, "DATA");
					gw_mail_send_msg ( sd, commande);
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "354") )
					{
						perror ( "Unknown error");
					}

					strcpy ( commande, "Subject: ");
					strcat ( commande, object);
					strcat ( commande, "\r\n");
					strcat ( commande, "From: ");
					strcat ( commande, from);
					strcat ( commande, "\r\n");

					strcat ( commande, "To: ");
					strcat ( commande, to);
					strcat ( commande, "\r\n");

					if ( cc != NULL )
					{
						if ( strlen ( cc) > 1 )
						{
							strcat ( commande, "Cc: ");
							strcat ( commande, cc);
							strcat ( commande, "\r\n");
						}
					}

					if ( bcc != NULL)
					{
						if ( strlen ( cc) > 1 )
						{
							strcat ( commande, "Bcc: ");
							strcat ( commande, bcc);
							strcat ( commande, "\r\n");
						}
					}

					strcat ( commande, "MIME-Version: 1.0\r\n");
					strcat ( commande, "Content-Type: multipart/mixed; boundary=\"");
					strcat ( commande, BOUNDARY);
					strcat ( commande, "\"; charset=us-ascii\r\n");

					/* Writes message. */
					strcat ( commande, "\r\n--");
					strcat ( commande, BOUNDARY);
					strcat ( commande, "\r\nContent-Type: text/plain; charset=us-ascii\r\n");
					strcat ( commande, "Content-Transfer-Encoding: 7bit\r\n\r\n");
					strcat ( commande, msg);
					strcat ( commande, "\r\n--");
					strcat ( commande, BOUNDARY );

					if ( (file != NULL) && (gw_file_exists ( file) == 0) )
					{
						filename = gw_file_get_name ( file);

						/* Sends the attached file. */
						strcat ( commande, "\r\nContent-Type: application/octet-stream; name=");
						strcat ( commande, filename);
						strcat ( commande, "\r\nContent-Disposition: attachment;filename=\"");
						strcat ( commande, filename);
						strcat ( commande, "\"\r\n");
						strcat ( commande, "Content-Transfer-Encoding: base64\r\n");

						gw_mail_send_msg ( sd, commande);

						if ( filename != NULL )
						{
							g_free ( filename);
						}

						/* Inserts the file body. */
						gw_mail_attachment_encode_base64_and_send ( sd, file);

						strcpy ( commande, "\r\n--");
						strcat ( commande, BOUNDARY);
					}

					strcat ( commande, "\r\n\r\n");
					strcat ( commande, ".");

					gw_mail_send_msg ( sd, commande);
					gw_mail_read_msg ( sd);

					if ( !gw_mail_check_msg ( rcv_msg, "250") )
					{
						perror ( "Sending failed");
					}

					strcpy ( commande, "QUIT");
					gw_mail_send_msg ( sd, commande);
				}
				else
				{
#ifdef GW_DEBUG_TOOLS_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : cannot connect to %s on TCP port %u\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, hostname, server_port);
#endif
				}
			}
			else
			{
#ifdef GW_DEBUG_TOOLS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : %s cannot bind the TCP port %u\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, hostname, server_port);
#endif
			}

			/* Closes the socket. */
			close ( sd);
		}
		else
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : cannot open socket\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}
	}
	else
	{
#ifdef GW_DEBUG_TOOLS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : %s -> unknown host\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, hostname);
#endif

		switch ( h_errno)
		{
			case HOST_NOT_FOUND:	g_print ( "*** GW - %s (%d) :: %s() : unknown host name\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
						break;

			case NO_ADDRESS:	g_print ( "*** GW - %s (%d) :: %s() : host name valid, but no IP\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
						break;

//			case NO_DATA:		g_print ( "*** GW - %s (%d) :: %s() : host name valid, but no IP\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
//						break;

			case NO_RECOVERY:	g_print ( "*** GW - %s (%d) :: %s() : fatal error on DSN\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
						break;

			case TRY_AGAIN:		g_print ( "*** GW - %s (%d) :: %s() : temporary error on DSN, try later\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
						break;

			default: 		g_print ( "*** GW - %s (%d) :: %s() : unknown error\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
						break;
		}
	}

#if defined ( OS_WIN32)
	WSACleanup ( );
#endif

	return 0;
}


gboolean gw_mail_check_email_list ( const char * email_list)
{
	gboolean result = FALSE;
	gboolean good = TRUE;
	gchar **list = NULL;
	gchar *first = NULL;
	gint i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( email_list != NULL )
	{
		list = g_strsplit ( email_list, ";", 0);

		while ( (list[i++] != NULL) && good )
		{
#ifdef GW_DEBUG_TOOLS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : checking email (%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, list[i-1]);
#endif

			first = strchr ( list[i - 1], '@');

			if (  first != NULL )
			{
				if ( strchr ( first + 1, '@') != NULL )
				{
					good = FALSE;
				}
			}
			else
			{
				good = FALSE;
			}
		}

		g_strfreev ( list);

		result = good;
	}

	return result;
}
