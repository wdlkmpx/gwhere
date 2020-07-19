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
#include "gwdevicemanager.h"


/* To open and close files */
#include <unistd.h> /* lseek read close */
#include <fcntl.h> /* open */

#include <stdlib.h> /* exit */
#include <errno.h> /* errno */
#include <string.h> /* strncmp malloc */
#include <stdio.h> /* perror */
#include <ctype.h> /* toupper */

/* To mount device */
#include <sys/stat.h> /* stat */

#if defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	#include <sys/wait.h>
	#include <sys/param.h>
	#include <sys/mount.h>
#endif


#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
	#include <mntent.h> /* setmntent getmntent endmntent */
	#include <sys/mount.h> /* mount umount */
	#include <sys/wait.h>
	#define EXT_SUPER_MAGIC 0x137d
	#define EXT2_OLD_SUPER_MAGIC 0xEF51
	#define EXT2_SUPER_MAGIC 0xEF53
	#define ISOFS_SUPER_MAGIC 0x9660
	#define MSDOS_SUPER_MAGIC 0x4d44
#endif

/* To get information on the file system */
#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
	#include <sys/vfs.h> /* statfs */
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
	#define VWIN32_DIOC_DOS_INT13 4
	#define VWIN32_DIOC_DOS_IOCTL 1

	typedef struct _DIOC_REGISTERS {
		DWORD reg_EBX;
		DWORD reg_EDX;
		DWORD reg_ECX;
		DWORD reg_EAX;
		DWORD reg_EDI;
		DWORD reg_ESI;
		DWORD reg_Flags;
	} DIOC_REGISTERS, *PDIOC_REGISTERS;
	#endif   /* VWIN32_DIOC_DOS_IOCTL */

	/* Intel x86 processor status flags */
	#define CARRY_FLAG 0x0001
#endif

#include "tools/gwtools.h"

#include "gwapplicationmanager.h"
#include "gwsupermount.h"


gint gw_dm_device_load_to_vfs_stats ( struct vfs_stats *p, gchar *dir)
{
	/* This function loads all information about a file system designed by
	   his full path name (stored in the parameter "dir") as "/mnt/cdrom".
	   Theses information are stored in a structure called vfs_stats.
	*/
#if defined ( OS_CYGWIN) || defined ( OS_WIN32)
	gchar *device_name = NULL;
	gchar *volume_name = NULL;
	gchar *serial_number = NULL;
	gchar *device_type = NULL;
	gulong nb = 0;
	guint errmode;
#endif


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( p == NULL )
	{
		/* The virtual file system hasn't been allocated */
#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "VFS is null");
#endif

		return -1;
	}

	if ( dir == NULL )
	{
		/* The file system path is NULL */
#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "filesystem path is null");
#endif

		return -1;
	}

#if defined ( OS_LINUX)
	/* Checks if the device is in the mounted device table (/etc/mtab) */
	if ( gw_dm_search_disk_in_tab_file_to_vfs_stats ( p, "/etc/mtab", dir) == 0 )
	{
		return 0;
	}

	/* Checks if the device is in the mountabled device table (/etc/fstab) */
	if ( gw_dm_search_disk_in_tab_file_to_vfs_stats ( p, "/etc/fstab", dir) == 0 )
	{
		return 0;
	}
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	errmode = SetErrorMode ( SEM_FAILCRITICALERRORS );

	device_name = g_strdup_printf ( "\\\\.\\%s", dir);

	vfs_stats_set_name ( p , device_name);
	vfs_stats_set_dir ( p, g_strdup ( dir));
	vfs_stats_set_options ( p, NULL);

	if ( gw_dm_is_disk_in_drive ( dir) )
	{
		gw_fs_get_type ( device_name, &device_type);
		if ( device_type == NULL )
		{
			switch ( GetDriveType ( dir))
			{
				case DRIVE_UNKNOWN:

							break;

				case DRIVE_NO_ROOT_DIR:

							break;

				case DRIVE_REMOVABLE:	switch ( toupper ( dir[0]))
							{
								case 'A':	g_strdup ( "/dev/fd0");break;
								case 'B':	g_strdup ( "/dev/fd1");break;
							}

							break;

				case DRIVE_FIXED:

							break;

				case DRIVE_REMOTE:

							break;

				case DRIVE_CDROM:	device_type = g_strdup ( "iso9660");

							break;

				case DRIVE_RAMDISK:

							break;

				default : break;
			}
		}

		vfs_stats_set_type ( p , device_type);
		vfs_stats_set_ismounted ( p, TRUE);
		/* FIX BUG : how to know how many files contains a disk? */
		/*vfs_stats_set_nb_files ( p, 0);*/
		vfs_stats_set_blocks_size ( p, 1024L);
		nb = gw_drive_get_capacity ( dir);
		vfs_stats_set_blocks ( p, nb);
		nb = gw_drive_get_free_space ( dir);
		vfs_stats_set_blocks_free ( p, nb);
		gw_fs_get_serial_number ( device_name, &serial_number);
		vfs_stats_set_serial_number ( p, serial_number);
		gw_fs_get_volume_name ( device_name, &volume_name);
		vfs_stats_set_label ( p, volume_name);
	}
	else
	{
		vfs_stats_set_ismounted ( p, FALSE);
	}

	SetErrorMode ( errmode );

	return 0;
#endif

	/* If the path file system doesn't exist */
	return -1;
}




gboolean gw_dm_disk_try_mount_from_vfs_stats ( struct vfs_stats *p)
{
/*
// First methode failed : single user cannot use mount()

	if ( mount ( vfs_stats_get_name ( p), vfs_stats_get_dir ( p), vfs_stats_get_type ( p), 0xc0ed0000|MS_RDONLY, "") == -1 )
	{
		if ( errno == EBUSY )
		{
g_print ( "try_mount : device busy\n");
			return TRUE;
		}
		else
		{
g_print ( "try_mount : cannot mount\n");
			return FALSE;
		}
	}
	else
	{
		umount ( vfs_stats_get_dir ( p));

g_print ( "try_mount : can mount\n");
		return TRUE;
	}
*/
/*
// Second methode failed : cannot detect if the device is allready mounted
	if ( gw_dm_disk_mount_from_vfs_stats ( p) == TRUE )
	{
		gw_dm_disk_umount_from_vfs_stats ( p);

		return TRUE;
	}

	return FALSE;
*/
/*
// Third methode failed : umount an umounted device doesn't failed
	if ( gw_dm_disk_umount_from_vfs_stats ( p) == TRUE )
	{
		gw_dm_disk_mount_from_vfs_stats ( p);

		return TRUE;
	}
	else
	{
		if ( gw_dm_disk_mount_from_vfs_stats ( p) == TRUE )
		{
			gw_dm_disk_umount_from_vfs_stats ( p);

			return TRUE;
		}

	return FALSE;
	}

	return FALSE;
*/
	/* This function should not be used. It checks if the file
	   system can be mounted in order to know if there is any
	   disk in drive.
	 */
	struct stat statbuf;
	guint fic;


#ifdef GW_DEBUG_MODE
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Gets rights of the disk */
	if ( stat ( vfs_stats_get_name ( p), &statbuf) == -1 )
	{
		perror ( "stat");

		return FALSE;
	}

	/* If it's a regular file */
	if ( S_ISREG ( statbuf.st_mode) )
	{
		perror ( "S_ISREG");

		return FALSE;
	}

	/* Cannot read only the file */
	if ( access ( vfs_stats_get_name ( p), R_OK) != 0 )
	{
		perror ( "access");

        		return FALSE;
	}

	/* Opens the device */
	if ( ( fic = open ( vfs_stats_get_name ( p), O_RDONLY ) ) == -1 )
	{
		perror ( "open");

		return FALSE;
	}

	/* Closes the device file system */
	close ( fic);

	return TRUE;
}


gint gw_dm_search_disk_in_tab_file_to_vfs_stats ( struct vfs_stats *p, const gchar *file_tab, const gchar *dir)
{
	/* This function is used only on mount support systems.
	   It searches all information about the file system
	   designed by his full path name (stored in the parameter
	   "dir") as "/mnt/cdrom" in the designed "mount table"
	   (stored in the parameter "file_tab").
	*/
#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;
	struct statfs sts;
	gchar *volume_name = NULL;
	gulong size = 0;
	gboolean has_mounted = FALSE;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( p == NULL )
	{
		/* The virtual file system hasn't been allocated */
		return -1;
	}

	if ( dir == NULL )
	{
		/* The file system path is NULL */
		return -1;
	}

	/* Opens the device table file */
	if ( (tab = setmntent ( file_tab, "r")) != NULL )
	{
		while ( (partition = getmntent ( tab)) != NULL)
		{
			if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, dir) == 0) )
			{
				/* Bug to fix : must free all data before set new informations */
				vfs_stats_set_name ( p , g_strdup ( partition->mnt_fsname));
				vfs_stats_set_dir ( p, g_strdup ( partition->mnt_dir));
				vfs_stats_set_options ( p, g_strsplit ( partition->mnt_opts, ",", 0));
				vfs_stats_set_type ( p , g_strdup ( partition->mnt_type));

				if ( strncmp ( file_tab, "/etc/mtab", 9) == 0 )
				{
					/* If the device table file is /etc/mtab */
					vfs_stats_set_ismounted ( p, TRUE);
				}
				else if ( strncmp ( file_tab, "/etc/fstab", 10) == 0 )
				{
					/* If the device table file is /etc/fstab */
					vfs_stats_set_ismounted ( p, FALSE);
				}

				if ( gw_dm_disk_can_mounted_from_vfs_stats ( p) )
				{
					if ( !gw_dm_disk_is_mounted_from_vfs_stats ( p) )
					{
						has_mounted = gw_dm_disk_mount_from_vfs_stats ( p);
					}

					if ( statfs ( dir, &sts) != -1 )
					{
						size = sts.f_files;
						vfs_stats_set_nb_files ( p, size);
						vfs_stats_set_blocks_size ( p, sts.f_bsize);
						size = sts.f_blocks;
						vfs_stats_set_blocks ( p, size);
						size = sts.f_bfree;
						vfs_stats_set_blocks_free ( p, size);
						/* FIX BUG : how to get serial number? */
						/*vfs_stats_set_serial_number ( p, g_strdup_printf ( "%d", sts.f_fsid);*/

						if ( vfs_stats_get_type ( p) != NULL )
						{
							if ( sts.f_type == EXT_SUPER_MAGIC )
							{
								vfs_stats_set_type ( p, g_strdup ( "ext"));
							}
							else if ( sts.f_type == EXT2_OLD_SUPER_MAGIC || sts.f_type == EXT2_SUPER_MAGIC )
							{
								vfs_stats_set_type ( p, g_strdup ( "ext2"));
							}
							else if ( sts.f_type == ISOFS_SUPER_MAGIC )
							{
								vfs_stats_set_type ( p, g_strdup ( "iso9660"));
							}
							else if ( sts.f_type == MSDOS_SUPER_MAGIC )
							{
								vfs_stats_set_type ( p, g_strdup ( "vfat"));
							}
							else
							{
							}
						}
					}

					if ( (vfs_stats_get_type ( p) != NULL) && (strcmp ( vfs_stats_get_type ( p), "iso9660") == 0) )
					{
						volume_name = gw_fs_iso9660_get_volume_name ( vfs_stats_get_name ( p));
					}
					else
					{
						gw_fs_get_volume_name ( vfs_stats_get_name ( p), &volume_name);
					}

					/* Why this following code??
					volume must be different to NULL or equals to NULL??
					*//*
					if ( (volume_name != NULL) && (vfs_stats_get_type ( p) != NULL) && ( strcmp ( vfs_stats_get_type ( p), "vfat") == 0) )
					{
						volume_name = gw_fs_fat16_get_volume_name ( vfs_stats_get_name ( p));
					}*/

					vfs_stats_set_label ( p, volume_name);

					if ( !vfs_stats_get_ismounted ( p) && has_mounted )
					{
						gw_dm_disk_umount_from_vfs_stats ( p);
					}
				}
				else
				{
					/* The virtual file system cannot be mounted */
					vfs_stats_set_ismounted ( p, FALSE);
				}

#ifdef GW_DEBUG_MODE
				vfs_stats_display ( p);
#endif

				/* Closes the /ect/fstab or /etc/mtab file. */
				endmntent ( tab);

				return 0;
			}
		}

		/* Closes the /ect/fstab or /etc/mtab file. */
		endmntent ( tab);
	}
#endif

	return -1;
}


gboolean gw_dm_disk_mount_from_vfs_stats ( struct vfs_stats *p) {
	/* This function mount a file system with the external program "mount". */
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	int pid;		/* pid number		*/
	int status;		/* process status	*/
	int fd[2];		/* pipe descriptor	*/
	char *argv[4] = {"mount", vfs_stats_get_dir ( p), 0};
 	char retour[201];
	struct statfs stat_fs;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	/* To prevent unexpected mount with supermount on Mandrake or submount on SuSe. */
	if ( vfs_stats_get_type ( p) != NULL &&
		((strncmp ( vfs_stats_get_type ( p), "supermount", 10) == 0 ) || (strncmp ( vfs_stats_get_type ( p), "subfs", 5) == 0 )) ) {
		return statfs ( vfs_stats_get_dir ( p), &stat_fs);
	}

	/* Creates pipe */
	if ( pipe ( fd) != 0 ) {
		/* Cannot create pipe */
		perror ( "pipe");
		return FALSE;
	}

	/* Creates a fork */
	pid = fork (  );

	if ( pid == 0 ) {
		/* If it's the child */
		close ( fd[0]);
		close ( 2);
		close ( 1);

		/* Redirect the output error to the pipe */
		dup2 ( fd[1], 2);
		close ( fd[1]);

		if ( execv ( GW_PROG_PATH_MOUNT, argv) == -1 ) {
			perror ( "execv");
		}

		exit ( 127);
	} else {
		/* If it's the parent */
		if ( pid == -1 ) {
			perror ( "fork");
		}
	}

	close ( fd[1]);

	/* Gets the pipe data */
	gw_pipe_get_data ( fd[0], retour);

	if ( waitpid ( pid, & status, 0) == -1 ) {
		perror ( "waitpid");
	}

	 if ( WEXITSTATUS ( status) != 0 ) {
		 return FALSE;
	 }
#endif
	 return TRUE;
}


gboolean gw_dm_disk_umount_from_vfs_stats ( struct vfs_stats *p) {
#if defined ( OS_LINUX) || defined ( OS_CYGWIN) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	/* This function try to unmount the file system with the externalm program "umount". */
	gint pid;		/* pid number		*/
	gint status;		/* process status	*/
	gint fd[2];		/* pipe descriptor	*/
	gchar *argv[4] =  {"umount", vfs_stats_get_dir ( p), 0};
 	gchar retour[201];
	struct statfs stat_fs;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	/* To prevent unexpected mount with supermount on Mandrake or submount on SuSe. */
	if ( (vfs_stats_get_type ( p) != NULL) &&
		((strncmp ( vfs_stats_get_type ( p), "supermount", 10) == 0 ) || (strncmp ( vfs_stats_get_type ( p), "subfs", 5) == 0 )) ) {
		return statfs ( vfs_stats_get_dir ( p), &stat_fs);
	}

	/* Creates pipe */
	if ( pipe ( fd) != 0 ) {
		perror ( "pipe");

		return FALSE;
	}

	/* Creates fork */
	pid = fork ( );
	if ( pid == 0 ) {
		/* If it's the child */
		close ( fd[0]);
		close ( 2);
		close ( 1);

		/* Redirect the output error to the pipe */
		dup2 ( fd[1], 2);
		close ( fd[1]);

		if ( execv ( GW_PROG_PATH_UMOUNT, argv) == -1 ) {
			perror ( "execv");
		}

		exit ( 127);
	} else {
		/* If it's the parent */
		if ( pid == -1 ) {
			perror ( "fork");
		}
	}

	close ( fd[1]);

        	/* Gets the pipe data */
	gw_pipe_get_data ( fd[0], retour);

	/* Waits the child process end */
	if ( waitpid ( pid, & status, 0) == -1 ) {
		perror ( "waitpid");
	}

	 if ( WEXITSTATUS ( status) != 0 ) {
		 return FALSE;
	 }

#endif
	return TRUE;
}


gint gw_pipe_get_data ( gint entry, gchar * line)
{
	gint nb;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	while ( (nb = read ( entry, line, 200)) > 0 )
	{
		line[nb] = '\0';
	};

	if ( nb < 0 )
	{
		perror ( "read");
	};

 	return 0;
}


gint gw_dm_disk_get_device_name ( const gchar *mount_point, gchar **device_name)
{
	gint result = -1;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( mount_point != NULL )
	{
		if ( strlen ( mount_point) > 10 )
		{
			switch ( mount_point[10])
			{
				case 'a' : 	*device_name = g_strdup ( "/dev/fd0");
						result = 0;

						break;

				case 'b' : 	*device_name = g_strdup ( "/dev/fd1");
						result = 0;

						break;

				case 'c' : 	*device_name = g_strdup ( "/dev/sda1");
						result = 0;

						break;

				case 'd' : 	*device_name = g_strdup ( "/dev/sda2");
						result = 0;

						break;

				default :	break;

			}
		}
	}

	return result;
}


gboolean gw_dm_disk_is_mounted_from_vfs_stats ( struct vfs_stats *p)
{
	/* This function checks if the file system is already mounted. */
	gboolean success = FALSE;
#if defined ( OS_LINUX) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	gchar *type = NULL;
#endif


#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( p != NULL )
	{
#if defined ( OS_LINUX) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
		type = vfs_stats_get_type ( p);

		/* If the supermount is activated under Mandrake system or submount is activated under SuSe,
		   a mount test is needed. */
		if ( (type != NULL) && ((strncmp ( type, "supermount", 10) == 0) || (strncmp ( type, "subfs", 5) == 0)) ) {
			/* If the device is in supermount mode, try to acces it */
			success = gw_dm_disk_try_mount_from_vfs_stats ( p);
//			success = gw_dm_is_disk_in_drive ( vfs_stats_get_dir ( p));
		} else {
			/* Returns the mount state */

			success = vfs_stats_get_ismounted ( p);
		}
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
		success = gw_dm_is_disk_in_drive ( vfs_stats_get_dir ( p));
#endif
	}

	return success;
}


gboolean gw_dm_disk_can_mounted_from_vfs_stats ( struct vfs_stats *p)
{
	/* This function checks if a file system can be mounted,
	   without mount it.
	*/
#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( p != NULL )
	{
		if ( vfs_stats_get_ismounted ( p) == TRUE )
		{
			return TRUE;
		}
		else
		{
			return gw_dm_disk_try_mount_from_vfs_stats ( p);
		}
	}

	return FALSE;
}


gboolean gw_dm_is_disk_in_drive ( const gchar *drive_path)
{
	/* This function checks if there is a disk in the drive
	   designed by the full path name (stored in the parameter
	   "drive_path").
	*/
	gboolean result = FALSE;
#if defined ( OS_LINUX) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;
	gchar *device_path = NULL;
	struct stat statbuf;
	guint fic;
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	guint errmode;
	DWORD max_file_len;
	DWORD system_flags;
#endif


#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( drive_path != NULL )
	{
/* How to detect if a disk is present in a drive under BSD system? */
#if defined ( OS_LINUX) /*|| defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD)*/

		/* Opens the device table file */
		if ( (tab = setmntent ( "/etc/mtab", "r")) != NULL )
		{
			while ( ((partition = getmntent ( tab)) != NULL) && (device_path == NULL))
			{
				if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
				{
					device_path = g_strdup ( partition->mnt_fsname);
				}
			}

			/* Closes the device table file */
			endmntent ( tab);
		}

		if ( device_path == NULL )
		{
			/* Opens the device table file */
			if ( (tab = setmntent ( "/etc/fstab", "r")) != NULL )
			{
				while ( ((partition = getmntent ( tab)) != NULL) && (device_path == NULL))
				{
					if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
					{
						device_path = g_strdup ( partition->mnt_fsname);
					}
				}

				/* Closes the device table file */
				endmntent ( tab);
			}
		}

		if ( device_path != NULL )
		{
			/* Gets rights of the disk */
			if ( stat ( device_path, &statbuf) != -1 )
			{
				/* If it's a regular file */
				if ( !S_ISREG ( statbuf.st_mode) )
				{
					/* Cannot read only the file */
					if ( access ( device_path, R_OK) == 0 )
					{
						/* Opens the device */
						if ( ( fic = open ( device_path, O_RDONLY ) ) != -1 )
						{
							result = TRUE;
						}

						/* Closes the device file system */
						close ( fic);
					}
				}
			}

			g_free ( device_path);
		}

#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);
		result = GetVolumeInformation ( drive_path, NULL, 0, NULL, &max_file_len, &system_flags, NULL, 0);
		SetErrorMode ( errmode);
#endif
	}

#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "%s is %savailable", drive_path,result?"":"un");
#endif

	return result;
}
