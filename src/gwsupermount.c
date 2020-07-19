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


#include "gwsupport.h"
#include "gwsupermount.h"

#include <glib.h>

/* To open and close files */
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h> /* malloc free */
#include <errno.h> /* codes d'erreur */
#include <string.h> /* strncmp */
#include <stdio.h> /* sprintf */

/* To mount partition */
#include <sys/stat.h>

#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
	/* To get informations about a file system */
	#include <sys/vfs.h>

	/* To eject a CD */
	#include <sys/ioctl.h>
	#include <sys/mtio.h>
#endif

#if defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)
	/* To eject a CD */
	#include <sys/ioctl.h>
	#include <sys/mtio.h>
	#include <sys/cdio.h>
	#define CDROMEJECT CDIOCEJECT
#endif

/* To eject a CD. */
#if defined ( OS_WIN32) || defined ( OS_CYGWIN_DEPRECATED)
	#include <windows.h>
 	#include <winioctl.h>
#endif

/* Must be after gwsupport.h!! */
#if defined ( OS_LINUX)
	/* #include <linux/fs.h> */
	#include <linux/cdrom.h>
#endif

#if defined ( OS_LINUX)
	#include <mntent.h>
	#include <sys/mount.h>
#endif

#if defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	#include <sys/param.h>
	#include <sys/mount.h>
	#include <fstab.h>
#endif
#if defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	#include <sys/ucred.h>
#endif

#if defined ( OS_CYGWIN)
	#include <sys/cygwin.h> /* cygwin_conv_to_full_win32_path */
#endif

#if defined ( OS_CYGWIN) || defined ( OS_WIN32)
	#include <sys/types.h> /* opendir */
	#include <dirent.h> /* opendir */
#endif

#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
    #include <io.h>
    #include <sys/stat.h>
    #include <windows.h> /* GetLogicalDriveStrings*/
    #include <ctype.h> /* toupper */
	#include <stdio.h>
	#include <winioctl.h>
#if defined ( OS_WIN32)
	#include <tchar.h>
#endif

	/* Define the structures to eject under Win95/98/Me */
	#if !defined ( VWIN32_DIOC_DOS_IOCTL)
	#define VWIN32_DIOC_DOS_IOCTL     1

	typedef struct _DIOC_REGISTERS {
		DWORD reg_EBX;
		DWORD reg_EDX;
		DWORD reg_ECX;
		DWORD reg_EAX;
		DWORD reg_EDI;
		DWORD reg_ESI;
		DWORD reg_Flags;
	} DIOC_REGISTERS, *PDIOC_REGISTERS;
	#endif /* VWIN32_DIOC_DOS_IOCTL */
#endif


GList * gw_get_drives_list ( GList *g)
{
#if defined ( HAVE_MOUNT_SYSTEM) && !defined (OS_LINUX) && !defined (OS_FREEBSD) && !defined (OS_OPENBSD) && !defined (OS_NETBSD)
#if defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct fstab *partition = NULL;
	gchar *fsname = NULL;
	gint status = -1;
	gint i = 0;
	struct statfs *mnt = NULL;
	int count = 0;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

#ifdef GW_DEBUG_MODE
	count = getmntinfo ( &mnt, MNT_NOWAIT);
	g_print ( "%d mount points are listed in getmntinfo()\n",count);
#endif
	for ( i = 0; i < count; i++) {
#ifdef GW_DEBUG_MODE
		g_print("%s at %d position\n",mnt[i].f_mntfromname,i);
#endif
		if ( mnt[i].f_fstypename!=NULL && strcmp(mnt[i].f_fstypename!=NULL,"procfs")!=0 && strcmp(mnt[i].f_fstypename!=NULL,"kernfs")!=0 && strcmp(mnt[i].f_fstypename!=NULL,"swap")!=0) {
#ifdef GW_DEBUG_MODE
			g_print ( "getfsent() : add %s\n",mnt[i].f_mntonname);
#endif
			fsname = g_strdup ( mnt[i].f_mntonname);
			g = g_list_insert_sorted ( g, fsname, (GCompareFunc)strcmp);
		} else {
#ifdef GW_DEBUG_MODE
			g_print ( "getfsent() : fstab->fs_vfstype==%s for %s\n",mnt[i].f_mntfromname,mnt[i].f_mntonname);
#endif
		}
	}

#ifdef __DEPRECATED__
	/* Opens the /etc/fstab file. */
	if ( (status = setfsent ( )) == 1 ) {
		while ( (partition = getfsent ( )) != NULL) {
			i++;
			g_print("%s at %d position\n",partition->fs_spec,i);
			if ( partition->fs_vfstype != NULL ) {
				if ( (strcmp ( partition->fs_vfstype, "procfs") != 0) && (strcmp ( partition->fs_vfstype, "kernfs") != 0) && (strcmp ( partition->fs_vfstype, "swap") != 0) ) {
					g_print ( "getfsent() : add %s\n",partition->fs_file);
 					fsname = g_strdup ( partition->fs_file);
					g = g_list_insert_sorted ( g, fsname, (GCompareFunc)strcmp);
				} else {
					g_print ( "getfsent() : fstab->fs_vfstype==%s for %s\n",partition->fs_vfstype,partition->fs_file);
				}
			} else {
				g_print ( "getfsent() : fstab->fs_vfstype==NULL for %s\n",partition->fs_file);
			}
		}

		/* Closes the /etc/fstab file. */
		endfsent ( );
	} else {
		g_print ( "setfsent() : cannot open /etc/fstab (%d)\n",status);
	}

	g_print ( "%d mount points are listed in /etc/fstab\n",i);
#endif
#endif
#elif defined ( HAVE_MOUNT_SYSTEM) && !defined (OS_FREEBSD) && !defined (OS_OPENBSD) && !defined (OS_NETBSD)
	FILE *fstab = NULL;
	struct mntent *partition = NULL;
	gchar *fsname = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	if ( (fstab = setmntent ( "/etc/fstab", "r")) != NULL )
	{
		while ( ( partition = getmntent ( fstab)) != NULL)
		{
			if ( partition->mnt_type != NULL )
			{
				if ( (strcmp ( partition->mnt_type, "proc") != 0) && (strcmp ( partition->mnt_type, "devpts") != 0) && (strcmp ( partition->mnt_type, "swap") != 0) )
				{
 					fsname = g_strdup ( partition->mnt_dir);
					g = g_list_insert_sorted ( g, fsname, (GCompareFunc)strcmp);
				}
			}
		}

		/* Closes the /etc/fstab file. */
		endmntent ( fstab);
	}

	/* Opens the /etc/mtab file. */
	if ( (fstab = setmntent ( "/etc/mtab", "r")) != NULL )
	{
		while ( ( partition = getmntent ( fstab)) != NULL)
		{
			if ( partition->mnt_type != NULL )
			{
				if ( (strcmp ( partition->mnt_type, "proc") != 0) && (strcmp ( partition->mnt_type, "devpts") != 0) && (strcmp ( partition->mnt_type, "swap") != 0) )
				{
					/* Check if the device is not already in the drives list (due to the first reading of /etc/fstab). */
					if ( g_list_find_custom ( g, partition->mnt_dir, (GCompareFunc)strcmp) == NULL )
					{
						fsname = g_strdup ( partition->mnt_dir);
						g = g_list_insert_sorted ( g, fsname, (GCompareFunc)strcmp);
					}
				}
			}
		}

		/* Closes the /etc/mtab file. */
		endmntent ( fstab);
	}
#elif defined ( HAVE_MOUNT_SYSTEM) && (defined (OS_FREEBSD) || defined (OS_OPENBSD) || defined (OS_NETBSD))
	struct fstab *partition = NULL;
	gchar *fsname = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (partition = getfsent ( )) != NULL )
	{
		if ( partition->fs_vfstype != NULL )
		{
			if ( (strcmp ( partition->fs_vfstype, "procfs") != 0) && ( strcmp ( partition->fs_vfstype, "swap") != 0) )
			{
 				fsname = g_strdup ( partition->fs_file);
				g = g_list_insert_sorted ( g, fsname, (GCompareFunc)strcmp);
			}
		}
	}

	/* Closes the /etc/mtab file. */
	endfsent( );
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	/* Floppy drive A: and B: are listed at the end of list because
	   cannot fix bug on GtkCombo when user click on the button and
	   the first item of the list is selected.
	*/
	gchar *textPtr = NULL;
	gchar buffer[128];
	gchar formatBuffer[128];
	gchar floppy_drives[2] = {'\0','\0'};


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets the drives string */
	GetLogicalDriveStringsA ( sizeof ( buffer), buffer);

	/* Adds the drives as necessary */
	textPtr = buffer;
	while ( *textPtr != '\0')
	{
		if ( toupper ( textPtr[0]) == 'A' )
		{
			floppy_drives[0] = textPtr[0];
		}
		else if ( toupper ( textPtr[0]) == 'B' )
		{
			floppy_drives[1] = textPtr[0];
		}
		else
		{
			/* Builds the actual displayable string */
			sprintf ( formatBuffer, "%c:\\", toupper ( textPtr[0]));

			/* Adds to the list */
			g = g_list_insert_sorted ( g, g_strdup ( formatBuffer), (GCompareFunc)strcmp);
		}

		textPtr += (strlen ( textPtr) + 1);
	}

	if ( floppy_drives[0] != '\0' )
	{
		/* Builds the actual displayable string */
		sprintf ( formatBuffer, "%c:\\", toupper ( floppy_drives[0]));

		/* Adds to the list */
		g = g_list_append ( g, g_strdup ( formatBuffer));
	}

	if ( floppy_drives[1] != '\0' )
	{
		/* Builds the actual displayable string */
		sprintf ( formatBuffer, "%c:\\", toupper ( floppy_drives[1]));

		/* Adds to the list */
		g = g_list_append ( g, g_strdup ( formatBuffer));
	}
#endif

	return g;
}


gboolean gw_drive_eject ( const gchar *drive_path) {
	gboolean l_result = FALSE;
#if defined ( HAVE_MOUNT_SYSTEM) && !defined (OS_FREEBSD) && !defined (OS_OPENBSD) && !defined (OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *fstab = NULL;
	struct mntent *pm = NULL;
	gint fd = 0;
	gint status;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s() : drive=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, drive_path);
#endif

	/* Opens the /etc/fstab file. */
	if ( (fstab = setmntent ( "/etc/fstab", "r")) != NULL ) {
		while ( (pm = getmntent ( fstab)) != NULL) {
			if ( (pm->mnt_dir != NULL) && (strcmp ( pm->mnt_dir, drive_path) == 0) ) {
				/* Search the type of mount. */
//				if ( (pm->mnt_type != NULL) && ((strcmp ( pm->mnt_type,"supermount") == 0)||(strcmp ( pm->mnt_type,"subfs") == 0)) ) {
				if ( (pm->mnt_type != NULL) && (strcmp ( pm->mnt_type,"supermount") == 0) ) {
					/* Gets the name of the device. */
					char *temp;
					//FIXME memory leak ?
					temp = strtok ( hasmntopt ( pm, "dev"), "=");
					temp = strtok ( NULL, "=");

					if ( temp ) {
						fd = open ( temp, O_RDONLY|O_NONBLOCK );
					}
				} else {
					fd = open ( pm->mnt_fsname, O_RDONLY|O_NONBLOCK );
				}

				if ( fd >= 0 ) {
#if defined ( OS_FREEBSD_DEPRECATED) || defined ( OS_OPENBSD_DEPRECATED) || defined ( OS_NETBSD_DEPRECATED) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
					ioctl ( fd, CDIOCALLOW);
#endif
					status = ioctl ( fd, CDROMEJECT);

					close ( fd);
				}

				l_result = TRUE;
			}
		}

		/* Closes the /etc/fstab file. */
		endmntent ( fstab);
	}
#elif defined ( HAVE_MOUNT_SYSTEM) && (defined ( OS_FREEBSD) || defined ( OS_FREEBSD) || defined ( OS_FREEBSD))
	struct fstab* partition = NULL;
	gint fd = 0;
	gint status;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (partition = getfsent ( )) != NULL ) {
		if ( (partition->fs_file != NULL) && (strcmp ( partition->fs_file, drive_path) == 0) ) {
			fd = open ( partition->fs_spec, O_RDONLY );

			if ( fd >= 0 ) {
				status = ioctl ( fd, CDIOCEJECT);

				close ( fd);
			}

			l_result = TRUE;

			break;
		}
	}

	/* Closes the /etc/fstab file. */
 	endfsent ( );

#elif defined ( OS_WIN32) || defined ( OS_CYGWIN_DEPRECATED)
	HANDLE hdl_file = NULL;
	DWORD lp_bytes_returned;
	gchar *device_name = NULL;
#ifdef GW_DEBUG_MODE
	LPVOID msg = NULL;
#endif
	DWORD dw_result;
	BYTE by_drive;
	DIOC_REGISTERS regs = {0};
	guint errmode;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s() : drive=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, drive_path);
#endif

	if ( drive_path != NULL ) {
		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

		/* Win2K ejection code */
		if ( GetVersion() < 0x80000000 ) {
#ifdef GW_DEBUG_MODE
			g_print ( "*** GW - %s (%d) :: %s() : using NT kernel API\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		/* I don't know with but the drive letter has to be passed without a trailing slash (ie "\\.\C:" instead of "\\.\C:\"). */
		device_name = g_strdup_printf ( "\\\\.\\%s", drive_path);
		if ( device_name[strlen(device_name)-1] == '\\') {
			device_name[strlen(device_name)-1] = '\0';
		}

		if ( (hdl_file = CreateFile ( (char *)device_name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL)) != NULL ) {
		/*if ( (hdl_file = CreateFile ( (char *)device_name, GENERIC_READ, 0 , NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL)) != NULL ) {*/
			l_result = DeviceIoControl ( hdl_file, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &lp_bytes_returned, NULL);

#ifdef GW_DEBUG_TOOLS_COMPONENT
				if ( l_result == FALSE ) {
					FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
					g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
					LocalFree( msg );
				}
#endif

			CloseHandle ( hdl_file);
		} else {
#ifdef GW_DEBUG_TOOLS_COMPONENT
			FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
			g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
			LocalFree( msg );
#endif
		}

		g_free ( device_name);
	} else {
		/* Win95/98/ME */
#ifdef GW_DEBUG_MODE
		g_print ( "*** GW - %s (%d) :: %s() : using Win9x kernel API\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		/* Create the handle to VWIN32 */
		if ( (hdl_file = CreateFile ( "\\\\.\\vwin32", 0, 0, NULL, 0, FILE_FLAG_DELETE_ON_CLOSE, NULL)) != NULL ) {
			/* Convert logical disk name to DOS-like disk name */
			by_drive = (toupper ( *drive_path) - 'A') + 1;

			/* Let's eject now : Int 21H function 440DH minor code 49h */
			regs.reg_EAX = 0x440D;
			regs.reg_EBX = by_drive;
			regs.reg_ECX = MAKEWORD ( 0x49, 0x08);	/* minor code */

			l_result = DeviceIoControl ( hdl_file, VWIN32_DIOC_DOS_IOCTL, &regs, sizeof ( regs), &regs, sizeof ( regs), &dw_result, 0);

#ifdef GW_DEBUG
			if ( l_result == FALSE ) {
				FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
				g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
				LocalFree( msg );
			}
#endif

				CloseHandle ( hdl_file) ;
			} else {
#ifdef GW_DEBUG
				FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
				g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
				LocalFree( msg );
#endif
			}
		}

		SetErrorMode ( errmode);
	}
#endif

	return l_result;
}


#ifdef HAVE_MOUNT_SYSTEM


gint gw_drive_mount ( const gchar *drive_path)
{
	gint l_result = -1;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	static gchar *filesystemtype[] = {"iso9660", "fat", "ext2", "vfat", "msdos", "minix", "ext"};
	FILE *fstab = NULL;
	struct mntent *pm = NULL;
	gint j = 0;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	if ( (fstab = setmntent ( "/etc/fstab", "r")) != NULL )
	{
		while ( (pm = getmntent ( fstab)) != NULL)
		{
			if ( (pm->mnt_dir != NULL) && (strcmp ( pm->mnt_dir, drive_path) == 0) )
			{
				/* Search if the mount point is not automatic. */
				if ( hasmntopt ( pm, "noauto") != NULL )
				{
					if ( (pm->mnt_type != NULL) && (strcmp ( pm->mnt_type, "auto") == 0) )
					{
						/* If the file system is not indicated, try with the most used types. */
						while ( j <= 6 )
						{
							if ( mount ( pm->mnt_fsname, pm->mnt_dir, filesystemtype[j++], 0xc0ed0000|MS_RDONLY, "") == 0 )
							{
								/* The mount point is not mounted correctly. */
								l_result = 0;
							}
							else
							{
								switch ( errno )
								{
									case EPERM :		g_print ( "L'utilisateur n'est pas le  Super-User\n");

														l_result = -1;
														break;

									case ENODEV :		/* Ce type de système de fichier n'existe pas */
														g_print ( "Warning : %s doesn't exist!!\n", filesystemtype[j-1]);

														l_result = -1;
														break;

									case ENOTBLK :		g_print ( "Specialfile n'est pas un fichier special en mode bloc\n");

														l_result = -1;
														break;

									case EBUSY :		/* Le point de montage est déjà monté */

														l_result = -1;
														break;

									case EINVAL :		/* Le type de système de fichier est invalide */
												break;

									case EFAULT :		g_print ( "L'un des arguments pointe en-dehors de l'espace d'adressage accessible.\n");

														l_result = -1;
														break;

									case ENOMEM :		g_print ( "Pas assez de mémoire pour le noyau.\n");

														l_result = -1;
														break;

									case ENAMETOOLONG :	g_print ( "Un des arguments est trop long.\n");

														l_result = -1;
														break;

									case ENOENT :		g_print ( "Un répertoire des arguments n'existe pas ou est un lien symbolique pointant nulle part.\n");

														l_result = -1;
														break;

									case ENOTDIR :		g_print ( "Le point de montage, ou l'un des éléments du chemin d'accès au périphérique n'est pas un répertoire.\n");

														l_result = -1;
														break;

									case EACCES :		g_print ( "Un élément de chemin d'accès n'est pas consultable,\n");

														l_result = -1;
														break;

									case ENXIO :		g_print ( "Le nombre majeur du périphérique specialfile est invalide.\n");

														l_result = -1;
														break;

									case EMFILE :		g_print ( "Table de montage pleine.\n");

														l_result = -1;
														break;

									default :		/* Problème lors du montage */
												g_print ( "Aie!!\n");

														l_result = -1;
														break;
								}
							}
						}

						g_print ( "Le filesystemtype de ce point de montage n'est pas reconnu.\n");
						g_print ( "Cela est surement du par la présence du paramètre \"auto\" dans le fichier /etc/fstab.\n");
						g_print ( "Pour pouvoir utiliser ce point de montage avec l'automount dans GWhere veuillez\n");
						g_print ( "préciser le filesystemtype dans le fichier /etc/fstab\n");
					}
					else
					{
						/* If the fyle system is not reconized. */
						if ( mount ( pm->mnt_fsname, pm->mnt_dir, pm->mnt_type, 0xc0ed0000|MS_RDONLY, "") == 0 )
						{
							l_result = 0;
						}
						else
						{
							/* In the case the mount failed.*/
							switch ( errno)
							{
								case EPERM :	g_print ( "L'utilisateur n'est pas le  Super-User\n");
												break;

								case ENODEV :	g_print ( "Le fylesystemtype n'est pas configuré ds le noyau\n");
												break;

								case ENOTBLK :	g_print ( "Specialfile n'est pas un fichier special en mode bloc\n");
												break;

								case EBUSY :	g_print ( "Specialfile est dèjà monté");
												l_result = 1;
												break;

								case EINVAL :	g_print ( "Specialfile a un superbloc invalide\n");
												break;

								case EFAULT :	g_print ( "L'un des arguments pointe en-dehors de l'espace d'adressage accessible.\n");
												break;

								case ENOMEM :	g_print ( "Pas assez de mémoire pour le noyau.\n");
												break;

								case ENAMETOOLONG :	g_print ( "Un des arguments est trop long.\n");
												break;

								case ENOENT :	g_print ( "Un répertoire des arguments n'existe pas ou est un lien symbolique pointant nulle part.\n");
												break;

								case ENOTDIR :	g_print ( "Le point de montage, ou l'un des éléments du chemin d'accès au périphérique n'est pas un répertoire.\n");
												break;

								case EACCES :	g_print ( "Un élément de chemin d'accès n'est pas consultable,\n");
												break;

								case ENXIO :	g_print ( "Le nombre majeur du périphérique specialfile est invalide.\n");
												break;

								case EMFILE :	g_print ( "Table de montage pleine.\n");
												break;

								default :		g_print ( "Erreur non référencée!!\n");
												break;
							}
						}

						/* If mount failed. */
						g_print ( "Aie!! (bis)\n");
						l_result = -1;
					}
				}
				else
				{
					/* If the mount point is not automatic, the function doesn't try to mount it. */
					l_result = 1;
				}
			}
		}

		/* Closes the /ect/fstab file. */
		endmntent ( fstab);
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct fstab* pm = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (pm = getfsent ( )) != NULL )
	{
		if ( (pm->fs_file != NULL) && (strcmp ( pm->fs_file, drive_path) == 0) )
		{
			/* Search if the mount point is not automatic. */
			if ( (pm->fs_mntops != NULL) && (strstr ( pm->fs_mntops, "noauto") != NULL) )
			{
				/* Mount it */
				if ( mount ( pm->fs_vfstype, pm->fs_file, MNT_RDONLY, NULL) == 0 )
				{
					l_result = 0;
				}
				else
				{
					/* In the case the mount failed.*/
					switch ( errno)
					{
						case EPERM :	g_print ( "L'utilisateur n'est pas le  Super-User\n");
										break;

						case ENODEV :	g_print ( "Le fylesystemtype n'est pas configuré ds le noyau\n");
										break;

						case ENOTBLK :	g_print ( "Specialfile n'est pas un fichier special en mode bloc\n");
										break;

						case EBUSY :	g_print ( "Specialfile est dèjà monté");
										l_result = 1;
										break;

						case EINVAL :	g_print ( "Specialfile a un superbloc invalide\n");
										break;

						case EFAULT :	g_print ( "L'un des arguments pointe en-dehors de l'espace d'adressage accessible.\n");
										break;

						case ENOMEM :	g_print ( "Pas assez de mémoire pour le noyau.\n");
										break;

						case ENAMETOOLONG :	g_print ( "Un des arguments est trop long.\n");
										break;

						case ENOENT :	g_print ( "Un répertoire des arguments n'existe pas ou est un lien symbolique pointant nulle part.\n");
										break;

						case ENOTDIR :	g_print ( "Le point de montage, ou l'un des éléments du chemin d'accès au périphérique n'est pas un répertoire.\n");
										break;

						case EACCES :	g_print ( "Un élément de chemin d'accès n'est pas consultable,\n");
										break;

						case ENXIO :	g_print ( "Le nombre majeur du périphérique specialfile est invalide.\n");
										break;

						case EMFILE :	g_print ( "Table de montage pleine.\n");
										break;

						default :		g_print ( "Erreur non référencée!!\n");
										break;
					}
				}

				/* If mount failed. */
				g_print ( "Aie!! (bis)\n");
				l_result = -1;

			}
			else
			{
				/* If the mount point is not automatic, the function doesn't try to mount it. */
				l_result = 1;
			}
		}
	}

	/* Closes the /etc/fstab file. */
	endfsent ( );
#endif

	return l_result;
}


gboolean gw_drive_umount ( const gchar *drive_path)
{
	gboolean l_result = FALSE;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *fstab = NULL;
	struct mntent *pm = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	if ( (fstab = setmntent ( "/etc/fstab", "r")) != NULL )
	{
		while ( (pm = getmntent ( fstab)) != NULL)
		{
			if ( (pm->mnt_dir != NULL) && (strcmp ( pm->mnt_dir, drive_path) == 0) )
			{
				if ( umount ( pm->mnt_fsname/*, pm->mnt_dir, pm->mnt_type, 0xc0ed0000|MS_RDONLY, ""*/) == 0 )
				{
					l_result = TRUE;
				}
			}
		}

		/* Closes the /etc/fstab file. */
		endmntent ( fstab);
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct fstab* pm = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (pm = getfsent ( )) != NULL )
	{
		if ( (pm->fs_file != NULL) && (strcmp ( pm->fs_file, drive_path) == 0) )
		{
			if ( unmount ( pm->fs_file, 0) == 0 )
			{
				l_result = TRUE;
				break;
			}
		}
	}

	/* Closes the /etc/fstab file. */
	endfsent ( );
#endif

	return l_result;
}


gchar * gw_drive_get_device_type ( const gchar *drive_path) {
	gchar *device_type = NULL;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *mtab = NULL;
 	FILE *fstab = NULL;
	struct mntent *partition = NULL;
	gchar **options = NULL, **fs_type = NULL, **fs_device = NULL;
	gint i;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/mtab file. */
	if ( (mtab = setmntent ( "/etc/mtab", "r")) != NULL ) {
		while ( ( partition = getmntent ( mtab)) != NULL ) {
			if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) ) {
				if ( (partition->mnt_type != NULL) && ((strncmp ( "supermount", partition->mnt_type, 10) == 0)||(strncmp ( "subfs", partition->mnt_type, 5)==0)) ) {
					/* Gets the mount options and search the option auto. */
					if ( partition->mnt_opts != NULL ) {
						options = g_strsplit ( partition->mnt_opts, ",", 0);

						for ( i = 0; options[i] != NULL; i++) {
							if ( (strncmp ( options[i], "fs=", 3) == 0) && (fs_type == NULL) ) {
								fs_type = g_strsplit ( options[i], "=", 2);
							}

							if ( (strncmp ( options[i], "dev=", 4) == 0) && (fs_device == NULL) ) {
								fs_device = g_strsplit ( options[i], "=", 2);
							}
						}
					} else {
						/* Should we trait this error?? */
					}

					if ( fs_device == NULL && strncmp("subfs",partition->mnt_type,5) == 0 ) {
						fs_device = (gchar**)g_malloc0(3*sizeof(gchar*));
						fs_device[0] = g_strdup("");
						fs_device[1] = g_strdup(partition->mnt_fsname);
						fs_device[2] = NULL;
					}

					device_type = g_strdup_printf ( "%s [ %s ]", fs_device[1], fs_type[1]);

					if ( fs_device != NULL ) {
						g_strfreev ( fs_device);
						fs_device = NULL;
					}

					if ( fs_type != NULL ) {
						g_strfreev ( fs_type);
						fs_type = NULL;
					}

					if ( options != NULL ) {
						g_strfreev ( options);
						options = NULL;
					}
				} else if ( strncmp ( "/dev/hd", partition->mnt_fsname, 7) == 0 ) {
					device_type = g_strdup_printf ( "HD [ %s ]", partition->mnt_type);
				} else if ( strncmp ( "/dev/cdrom", partition->mnt_fsname, 10) == 0 ) {
					device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->mnt_type);
				} else if ( strncmp ( "/dev/scd", partition->mnt_fsname, 8) == 0 ) {
					device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->mnt_type);
				} else if ( strncmp ( "/dev/fd", partition->mnt_fsname, 7) == 0 ) {
					device_type = g_strdup_printf ( "Floppy [ %s ]", partition->mnt_type);
				} else {
					device_type = g_strdup ( partition->mnt_type);
				}
			}
		}

		/* Closes the /etc/mtab file. */
		endmntent ( mtab);
	}

	if ( device_type == NULL ) {
		/* If the disk is not mounted. */
		/* Opens the /etc/fstab file. */
		if ( (fstab = setmntent ( "/etc/fstab", "r")) != NULL ) {
			while ( ( partition = getmntent ( fstab)) != NULL ) {
				if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) ) {
					if ( (partition->mnt_type != NULL) && ((strncmp ( "supermount", partition->mnt_type, 10) == 0)||(strncmp ( "subfs", partition->mnt_type, 5) == 0)) ) {
						/* Gets the mount options and search the option auto. */
						if ( partition->mnt_opts != NULL ) {
							options = g_strsplit ( partition->mnt_opts, ",", 0);

							for ( i = 0; options[i] != NULL; i++) {
								if ( (strncmp ( options[i], "fs=", 3) == 0) && (fs_type == NULL) ) {
									fs_type = g_strsplit ( options[i], "=", 2);
								}

								if ( (strncmp ( options[i], "dev=", 4) == 0) && (fs_device == NULL) ) {
									fs_device = g_strsplit ( options[i], "=", 2);
								}
							}
						} else {
							/* Should we trait this error?? */
						}

						if ( fs_device == NULL && strncmp("subfs",partition->mnt_type,5) == 0 ) {
							fs_device = (gchar**)g_malloc0(3*sizeof(gchar*));
							fs_device[0] = g_strdup("");
							fs_device[1] = g_strdup(partition->mnt_fsname);
							fs_device[2] = NULL;
						}

						device_type = g_strdup_printf ( "%s [ %s ]", fs_device[1], fs_type[1]);

						if ( fs_device != NULL ) {
							g_strfreev ( fs_device);
							fs_device = NULL;
						}

						if ( fs_type != NULL ) {
							g_strfreev ( fs_type);
							fs_type = NULL;
						}

						if ( options != NULL ) {
							g_strfreev ( options);
							options = NULL;
						}
					}
					else if ( strncmp ( "/dev/hd", partition->mnt_fsname, 7) == 0 ) {
						device_type = g_strdup_printf ( "HD [ %s ]", partition->mnt_type);
					} else if ( strncmp ( "/dev/cdrom", partition->mnt_fsname, 10) == 0 ) {
						device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->mnt_type);
					} else if ( strncmp ( "/dev/scd", partition->mnt_fsname, 8) == 0 ) {
						device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->mnt_type);
					} else if ( strncmp ( "/dev/fd", partition->mnt_fsname, 7) == 0 ) {
						device_type = g_strdup_printf ( "Floppy [ %s ]", partition->mnt_type);
					} else if ( strncmp ( "/dev/zip", partition->mnt_fsname, 8) == 0 ) {
						device_type = g_strdup_printf ( "Zip [ %s ]", partition->mnt_type);
					} else {
						device_type = g_strdup ( partition->mnt_type);
					}
				}
			}

			/* Closes the /etc/fstab file. */
			endmntent ( fstab);
		}
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct fstab* partition = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (partition = getfsent ( )) != NULL) {
		if ( (partition->fs_spec != NULL) && (partition->fs_vfstype != NULL) ) {
			if ( strncmp ( "/dev/ad", partition->fs_spec, 7) == 0 ) {
				device_type = g_strdup_printf ( "HD [ %s ]", partition->fs_vfstype);
			} else if ( strncmp ( "/dev/acd", partition->fs_spec, 8) == 0 ) {
				device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->fs_vfstype);
			} else if ( strncmp ( "/dev/scd", partition->fs_spec, 8) == 0 ) {
				device_type = g_strdup_printf ( "CD-ROM [ %s ]", partition->fs_vfstype);
			} else if ( strncmp ( "/dev/fd", partition->fs_spec, 7) == 0 ) {
				device_type = g_strdup_printf ( "Floppy [ %s ]", partition->fs_vfstype);
			} else {
				device_type = g_strdup ( partition->fs_vfstype);
			}
		}
	}

	/* Closes the /etc/fstab file. */
	endfsent ( );
#endif

	return device_type;
}


gchar * gw_drive_get_device_name ( const gchar *drive_path) {
	gchar * device_name = NULL;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;
	gchar **fs_device = NULL;
	gchar **options = NULL;
	int i = 0;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens only the /etc/mtab file because the result must be returned only if the drive is mounted. */
	if ( (tab = setmntent ( "/etc/mtab", "r")) != NULL ) {
		while ( (partition = getmntent ( tab)) != NULL) {
			if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) ) {
//				if ( (partition->mnt_type != NULL) && ((strncmp ( "supermount", partition->mnt_type, 10) == 0)||(strncmp ( "subfs", partition->mnt_type, 5) == 0)) ) {
				if ( (partition->mnt_type != NULL) && (strncmp ( "supermount", partition->mnt_type, 10) == 0)) {
					/* Gets the mount options and search the option auto. */
					if ( partition->mnt_opts != NULL ) {
						options = g_strsplit ( partition->mnt_opts, ",", 0);

						for ( i = 0; options[i] != NULL; i++) {
							if ( strncmp ( options[i], "dev=", 4) == 0 ) {
								if ( (fs_device = g_strsplit ( options[i], "=", 2)) != NULL ) {
									device_name = g_strdup ( fs_device[1]);

									g_strfreev ( fs_device);
									fs_device = NULL;
								}
							}
						}
					} else {
						/* Should we trait this error?? */
					}

					if ( options != NULL ) {
						g_strfreev ( options);
						options = NULL;
					}
				} else {
					device_name = g_strdup ( partition->mnt_fsname);
				}
			}
		}

		/* Closes the /etc/mtab file. */
		endmntent ( tab);
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct statfs* pstats = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Get list of mounted devices. */
	int i, mfs_count = getmntinfo ( &pstats, MNT_WAIT);

	for ( i = 0; i < mfs_count; i++) {
		if ( (pstats[i].f_mntonname != NULL) && (strcmp ( pstats[i].f_mntonname, drive_path) == 0) ) {
			device_name = g_strdup ( pstats[i].f_mntfromname);
			break;
		}
	}
#endif

	return device_name;
}


gboolean gw_drive_is_mounted ( const gchar *drive_path)
{
	gboolean l_result = FALSE;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the file /etc/mtab. */
	if ( (tab = setmntent ( "/etc/mtab", "r")) != NULL )
	{
		while ( (partition = getmntent ( tab)) != NULL)
		{
			if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
			{
				/* If the disk is not in the /etc/mtab then it is mounted. */
				l_result = TRUE;
			}
		}

		/* Closes the /etc/mtab file. */
		endmntent ( tab);
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct statfs* pstats = NULL;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets list of mounted devices. */
	int i, mfs_count = getmntinfo ( &pstats, MNT_WAIT);

	for ( i = 0; i < mfs_count; i++)
	{
		if ( (pstats[i].f_mntonname != NULL) && (strcmp ( pstats[i].f_mntonname, drive_path) == 0) )
		{
			l_result = TRUE;
			break;
		}
	}
#endif

	return l_result;
}


gboolean gw_drive_is_mountable ( const gchar *drive_path)
{
	gboolean l_result = FALSE;
#if !defined ( OS_FREEBSD) && !defined ( OS_OPENBSD) && !defined ( OS_NETBSD) && !defined ( OS_MACOS) && !defined ( OS_MACOSX) && !defined ( OS_DARWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;
	gchar **options = NULL;
	gint i;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/mtab file. */
	if ( (tab = setmntent ( "/etc/fstab", "r")) != NULL )
	{
		while ( (partition = getmntent ( tab)) != NULL)
		{
			if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
			{
				/* If the disk is in the /etc/mtab file then it is mounted. */

				/* Gets the mount options and search the option auto. */
				if ( partition->mnt_opts != NULL )
				{
					options = g_strsplit ( partition->mnt_opts, ",", 0);

					for ( i = 0; options[i] != NULL; i++)
					{
						if ( strncmp ( options[i], "auto", 4) == 0 )
						{
							l_result = TRUE;
						}
					}

					if ( options != NULL )
					{
						g_strfreev ( options);
						options = NULL;
					}
				}
				else
				{
					/* Should we trait this error?? */
				}
			}
		}

		/* Closes the /etc/fstab file. */
		endmntent ( tab);
	}
#elif defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct fstab* pm = NULL;
	gchar **options = NULL;
	gint i;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Opens the /etc/fstab file. */
	setfsent ( );

	while ( (pm = getfsent ( )) != NULL )
	{
		if ( (pm->fs_file != NULL) && (strcmp ( pm->fs_file, drive_path) == 0) )
		{
			/* Gets the mount options and search the option auto. */
			if ( pm->fs_mntops != NULL )
			{
				options = g_strsplit ( pm->fs_mntops, ",", 0);

				for ( i = 0; options[i] != NULL; i++)
				{
					if ( strncmp ( options[i], "auto", 4) == 0 )
					{
						l_result = TRUE;
						break;
					}
				}

				if ( options != NULL )
				{
					g_strfreev ( options);
				}
			}
			else
			{
				/* Should we trait this error?? */
			}
		}
	}

	/* Closes the /etc/fstab file. */
	endfsent ( );
#endif

	return l_result;
}


#endif


#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
/*!
 * @function	gw_drive_get_space_stats
 * @abstract	Gets the space stats of the drive.
 * @discussion	This function gets the space stats of the drive.<br>
 *		Note: for Win/2000 or later, the amount of available
 *		space may be less than the amount of free space if
 *		disk quotas are enabled.<br>
 *		This routine loads GetDiskFreeSpaceEx at run-time to
 *		allow this to work with all 32-bit versions of Windows
 *		(including all versions of Win/95).<br>
 * @param	drive_path	the access path of drive
 * @param	avail_kb	amount of available space for current user (Kb)
 * @param	total_kb	total space on disk (Kb)
 * @param	free_kb		free space on disk (Mb)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>606</i> when it's unable to identify system type.<br>
 *		Returns <i>648</i> when it's unable to load library.<br>
 *		Returns <i>649</i> when disk name may be invalid or Disk not accessible.<br>
 */
int gw_drive_get_space_stats ( const gchar drive_path[], unsigned long *avail_kb, unsigned long *total_kb, unsigned long *free_kb)
{
	ULARGE_INTEGER ul_avail_bytes,ul_free_total_bytes,ul_used_total_bytes;
	HINSTANCE hinst_lib;
	int result = -1;
	int flag_os;
	int sys_version;
	int sys_major;
	int sys_minor;
	int sys_pack;
	DWORD sectors_by_cluster, bytes_per_sector, num_free_clusters, total_clusters;
	FARPROC GWGetDiskFreeSpaceExA = NULL;
#ifdef GW_DEBUG_MODE
	LPVOID msg = NULL;
#endif
	guint errmode;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Determine Windows OS version. */
	if ( (result = gw_win32_get_version ( &sys_version, &sys_major, &sys_minor, &sys_pack)) == 0 )
	{
		/* flag_os=1 for versions before Win95B(OSR2)
		   flag_os=2 for all NT versions, and Win versions Win/95B
		   and higher (i.e. Win/98, Win/ME etc.)
		*/

		flag_os = 1;
		if ( sys_version > 2 )
		{
			flag_os = 2;
		}

		if ( (sys_version == 2) && (sys_pack > 0) )
		{
			flag_os = 2;    /* Win/95(OSR2) */
		}

		/* Case of NT or Windows after and including Win/95(OSR2)
		   Here we can use GetDiskFreeSpaceEx.
		*/

		if ( flag_os == 2 )
		{
			/* Loads the library dynamically. */
			if ( (hinst_lib = LoadLibraryA ( "KERNEL32.DLL")) != NULL )
			{
				/* Get procedure address. */
				GWGetDiskFreeSpaceExA = GetProcAddress ( hinst_lib, "GetDiskFreeSpaceExA");

				errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

				if ( GWGetDiskFreeSpaceExA ( drive_path, &ul_avail_bytes, &ul_used_total_bytes, &ul_free_total_bytes) )
				{
					*total_kb = ul_used_total_bytes.QuadPart / 1024;
					*free_kb = ul_free_total_bytes.QuadPart / 1024;
					*avail_kb = ul_avail_bytes.QuadPart / 1024;

					result = 0;
				}
				else
				{
#ifdef GW_DEBUG
					FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
					g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
					LocalFree( msg );
#endif

					/* If GetDiskFreeSpaceExA failed, most certainly it is because drive name was invalid. */
					result = 649;
				}

				SetErrorMode ( errmode);
				FreeLibrary ( hinst_lib);
			}
			else
			{
#ifdef GW_DEBUG
					FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
					g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
					LocalFree( msg );
#endif

				result = 648;
			}
		}
	
		/* Case of Windows older than Win/95B(OSR2). Here we have to use GetDiskFreeSpace. */
		if ( flag_os == 1 )
		{
			errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);

			if ( GetDiskFreeSpaceA ( drive_path, &sectors_by_cluster, &bytes_per_sector, &num_free_clusters, &total_clusters) )
			{
				*avail_kb = ul_avail_bytes.QuadPart / 1024;
				*total_kb = ul_used_total_bytes.QuadPart / 1024;
				*free_kb = ul_free_total_bytes.QuadPart / 1024;

				result = 0;
			}
			else
			{
#ifdef GW_DEBUG
				FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError ( ), 0, (LPTSTR) &msg, 0, NULL );
				g_print ( "*** GW - %s (%d) :: %s() : an win32 error occured, %s (%d)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, msg, GetLastError ( ));
				LocalFree( msg );
#endif

				result = 649;
			}

			SetErrorMode ( errmode);
		}
	}

	return result;
}
#endif


gulong gw_drive_get_capacity ( const gchar *drive_path)
{
	gulong l_result = 0;
#if defined ( OS_LINUX) || defined ( OS_CYGWIN_DEPRECATED) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct statfs sts;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets rights of the drive. */
	if ( statfs ( drive_path, &sts) != -1 )
	{
		l_result = sts.f_bsize * sts.f_blocks;
	}
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	long total_kb = 0, avail_kb = 0, free_kb = 0;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( gw_drive_get_space_stats ( drive_path, &avail_kb, &total_kb, &free_kb) == 0)
	{
		l_result = total_kb;
	}
#endif

	return l_result;
}


gulong gw_drive_get_free_space ( const gchar *drive_path)
{
	gulong l_result = 0;
#if defined ( OS_LINUX) || defined ( OS_CYGWIN_DEPRECATED) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	struct statfs sts;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets rights of the drive. */
	if ( statfs ( drive_path, &sts) != -1 )
	{
		l_result = sts.f_bsize * sts.f_bfree;
	}
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	long total_kb = 0, avail_kb = 0, free_kb = 0;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( gw_drive_get_space_stats ( drive_path, &avail_kb, &total_kb, &free_kb) == 0)
	{
		l_result = free_kb;
	}
#endif

	return l_result;
}
