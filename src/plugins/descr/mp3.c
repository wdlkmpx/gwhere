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


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tools/gwtools.h"

//#define __DEBUG__ 1

/* ID3 v1 */
typedef struct {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
} stream_id3v1;

/* ID3 v1X */
typedef struct {
    char tag[3];
    char title[90];
    char artist[50];
    char album[50];
    char comment[50];
    unsigned char genre;
} stream_id3v1X;


/* ID3 */
typedef struct {
	char *version;
	char *title;
	char *artist;
	char *album;
	char *year;
	char *comment;
	char *genre;
	char *track;
	char *encoder;
	char *url;
	char *compositer;
	char *copyright;
	int gennum;
	int tracknum;
} id3;


const int genre_largest = 145;
const char * const genres[] =
{
  "Blues",            "Classic Rock",         "Country",           "Dance",
  "Disco",            "Funk",                 "Grunge",            "Hip-Hop",
  "Jazz",             "Metal",                "New Age",           "Oldies",
  "Other",            "Pop",                  "R&B",               "Rap",
  "Reggae",           "Rock",                 "Techno",            "Industrial",
  "Alternative",      "Ska",                  "Death Metal",       "Pranks",
  "Soundtrack",       "Euro-Techno",          "Ambient",           "Trip-Hop",
  "Vocal",            "Jazz+Funk",            "Fusion",            "Trance",
  "Classical",        "Instrumental",         "Acid",              "House",
  "Game",             "Sound Clip",           "Gospel",            "Noise",
  "AlternRock",       "Bass",                 "Soul",              "Punk",
  "Space",            "Meditative",           "Instrumental Pop",  "Instrumental Rock",
  "Ethnic",           "Gothic",               "Darkwave",          "Techno-Industrial",
  "Electronic",       "Pop-Folk",             "Eurodance",         "Dream",
  "Southern Rock",    "Comedy",               "Cult",              "Gangsta",
  "Top 40",           "Christian Rap",        "Pop/Funk",          "Jungle",
  "Native American",  "Cabaret",              "New Wave",          "Psychadelic",
  "Rave",             "Showtunes",            "Trailer",           "Lo-Fi",
  "Tribal",           "Acid Punk",            "Acid Jazz",         "Polka",
  "Retro",            "Musical",              "Rock & Roll",       "Hard Rock",
  "Folk",             "Folk-Rock",            "National Folk",     "Swing",
  "Fast Fusion",      "Bebob",                "Latin",             "Revival",
  "Celtic",           "Bluegrass",            "Avantgarde",        "Gothic Rock",
  "Progressive Rock", "Psychedelic Rock",     "Symphonic Rock",    "Slow Rock",
  "Big Band",         "Chorus",               "Easy Listening",    "Acoustic",
  "Humour",           "Speech",               "Chanson",           "Opera",
  "Chamber Music",    "Sonata",               "Symphony",          "Booty Bass",
  "Primus",           "Porn Groove",          "Satire",            "Slow Jam",
  "Club",             "Tango",                "Samba",             "Folklore",
  "Ballad",           "Power Ballad",         "Rhytmic Soul",      "Freestyle",
  "Duet",             "Punk Rock",            "Drum Solo",         "Acapella",
  "Euro-House",       "Dance Hall",           "Goa",               "Drum & Bass",
  "Club-House",       "Hardcore",             "Terror",            "Indie",
  "BritPop",          "Negerpunk",            "Polsk Punk",        "Beat",
  "Christian Gangsta Rap", "Heavy Metal",     "Black Metal",       "Crossover",
  "Contemporary Christian", "Christian Rock", "Merengue",          "Salsa",
  "Trash Metal",
  "Unknown"
};


#define MASK_SYNC 0xFFE00000

#define MASK_MPEG 0x180000
#define SHIFT_MPEG 19
#define MPEG_VERSION_1 3
#define MPEG_VERSION_2 2
#define MPEG_VERSION_2_5 0

#define MASK_LAYER 0x60000
#define SHIFT_LAYER 17
#define LAYER_VERSION_1 3
#define LAYER_VERSION_2 2
#define LAYER_VERSION_3 1

#define MASK_BITRATE 0xF000
#define SHIFT_BITRATE 12

#define MASK_FREQ 0xC00
#define SHIFT_FREQ 10

#define MASK_CHAN 0xC0
#define SHIFT_CHAN 6

#define INVALID_HEADER 2


int bitrates[2][3][15] = {
{
	/* layer 3 */
	{0, 32, 40, 48, 56, 64, 80,  96, 112, 128, 160, 192, 224, 256, 320},
	/* layer 2 */
	{0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384},
	/* layer 1 */
	{0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448}
},
{
	/* layer 3 */
	{8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160},
	/* layer 2 */
	{8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160},
	/* layer 1 */
	{0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256}
}
};

int freqs[3][3] = {
	/* MPEG 1 */
	{44100, 48000, 32000},
	/* MPEG 2 */
	{22050, 24000, 16000},
	/* MPEG 2.5 */
	{11025, 12000, 8000}
};


struct mp3data {
	int mpeg_version;
	int layer_desc;
	int bitrate;
	int frequency;
	int channels;
};


int file_mp3_get_header ( const char *filename, struct mp3data *mp3) {
	FILE *file = NULL;
	unsigned long int header = 0;
	int c = '\0';
	char chunk[4];
	short size = 0;
	int sample_rate = 0;


	if ( !(file = fopen ( filename, "rb")) )
	{
		perror ( "fopen");

		return 1;
	}

	if ( fread ( &chunk, sizeof ( char) * 4, 1, file) != 1 )
	{
		fclose ( file);
		return INVALID_HEADER;
	}

	if ( strncmp ( chunk, "RIFF", 4) == 0 )
	{
		/* It's a wav file */
		fread ( &chunk, sizeof ( char) * 4, 1, file);
		fread ( &chunk, sizeof ( char) * 4, 1, file);

		if ( strncmp ( chunk, "WAVE", 4) != 0 )
		{
			fclose ( file);
			return INVALID_HEADER;
		}

		fread ( &chunk, sizeof ( char) * 4, 1, file);

		if ( strncmp ( chunk, "fmt ", 4) != 0 )
		{
			fclose ( file);
			return INVALID_HEADER;
		}

		fread ( &chunk, sizeof ( char) * 4, 1, file);
		fread ( &size, sizeof ( short), 1, file);

		if ( size != 0x0055 )
		{
			fclose ( file);
			return INVALID_HEADER;
		}

		mp3->mpeg_version = MPEG_VERSION_1;
		mp3->layer_desc = LAYER_VERSION_3;

		fread ( &size, sizeof ( short), 1, file);
		mp3->channels = size;

		fread ( &sample_rate, sizeof ( int), 1, file);
		mp3->frequency = sample_rate;

		fread ( &sample_rate, sizeof ( int), 1, file);
		mp3->bitrate = (sample_rate&0x00F0);

		fclose ( file);
	}
	else
	{
		/* It's a real MP3 file */
		rewind ( file);

		while ( ((c = fgetc ( file)) != 0xff) && (c != EOF));

	if ( feof ( file) )
	{
		fclose ( file);
		return INVALID_HEADER;
	}

	ungetc ( c, file);
	fread ( &header, 1, sizeof ( header), file);
	fclose ( file);

	header = ntohl ( header);

	if ( (header & MASK_SYNC) != MASK_SYNC )
	{
		return INVALID_HEADER;
	}

	mp3->mpeg_version = ((header & MASK_MPEG) >> SHIFT_MPEG);
	mp3->layer_desc = ((header & MASK_LAYER) >> SHIFT_LAYER);

	/* Causes pain for MPEG_VERSION_2_5. */
	mp3->bitrate = bitrates[(mp3->mpeg_version == MPEG_VERSION_1)?0:1][mp3->layer_desc - 1][((header & MASK_BITRATE) >> SHIFT_BITRATE)];

	switch ( mp3->mpeg_version)
	{
		case MPEG_VERSION_1:	mp3->frequency = freqs[0][((header & MASK_FREQ) >> SHIFT_FREQ)];
					break;

		case MPEG_VERSION_2:	mp3->frequency = freqs[1][((header & MASK_FREQ) >> SHIFT_FREQ)];
					break;

		case MPEG_VERSION_2_5:	mp3->frequency = freqs[2][((header & MASK_FREQ) >> SHIFT_FREQ)];
					break;
	}

	if ( ((header & MASK_CHAN) >> SHIFT_CHAN) == 3)
	{
		mp3->channels = 1;
	}
	else
	{
		mp3->channels = 2;
	}
	}

	return 0;
}


int file_read_id3v1 ( FILE *file, id3 *id3tag) {
	int temp;
	stream_id3v1 id3;
	stream_id3v1X id3x;
	char *buffer;

#ifdef __DEBUG__
	g_print ( "read id3v1\n");
#endif

	fseek ( file, -128, SEEK_END);
	if ( (temp = fread ( &id3, 128, 1, file)) == 1 )
	{
		if (!strncmp ( id3.tag, "TAG", 3)) {
			id3tag->title = (char*)g_malloc ( sizeof ( char) * 31);
			memset ( id3tag->title, '\0', 31);
			/* str_kept_ascii ( id3.title, 30); */
			strncpy ( id3tag->title, id3.title, 30);
			gw_str_trim ( id3tag->title);
			if ( strlen ( id3tag->title) == 0)
			{
				g_free ( id3tag->title);
				id3tag->title = NULL;
			}
			id3tag->artist = (char*)g_malloc ( sizeof ( char) * 31);
			memset ( id3tag->artist, '\0', 31);
			/* str_kept_ascii ( id3.artist, 30); */
			strncpy ( id3tag->artist, id3.artist, 30);
			gw_str_trim ( id3tag->artist);
			if ( strlen ( id3tag->artist) == 0)
			{
				g_free ( id3tag->artist);
				id3tag->artist = NULL;
			}
			id3tag->album = (char*)g_malloc ( sizeof ( char) * 31);
			memset ( id3tag->album, '\0', 31);
			/* str_kept_ascii ( id3.album, 30); */
			strncpy ( id3tag->album, id3.album, 30);
			gw_str_trim ( id3tag->album);
			if ( strlen ( id3tag->album) == 0)
			{
				g_free ( id3tag->album);
				id3tag->album = NULL;
			}
			id3tag->year = (char*)g_malloc ( sizeof ( char) * 5);
			memset ( id3tag->year, '\0', 5);
			/* str_kept_ascii ( id3.year, 4); */
			strncpy ( id3tag->year, id3.year, 4);
			gw_str_trim ( id3tag->year);
			if ( strlen ( id3tag->year) == 0)
			{
				g_free ( id3tag->year);
				id3tag->year = NULL;
			}
			if ( (id3.comment[28] == 0x00) && (id3.comment[29] != 0x00) )
			{
					id3tag->comment = (char*)g_malloc ( sizeof ( char) * 29);
					memset ( id3tag->comment, '\0', 29);
					/* str_kept_ascii ( id3.comment, 30); */
					strncpy ( id3tag->comment, id3.comment, 28);
					gw_str_trim ( id3tag->comment);
					if ( strlen ( id3tag->comment) == 0)
					{
						g_free ( id3tag->comment);
						id3tag->comment = NULL;
					}

					id3tag->tracknum = id3.comment[29] & 0xFF;
					id3tag->tracknum++;
					id3tag->track = (char*)g_malloc ( sizeof ( char) * 4);
					memset ( id3tag->track, '\0', 4);
					snprintf ( id3tag->track, 3, "%d", id3tag->tracknum);
					id3tag->version = g_strdup ( "1.1");
			} else {
					id3tag->comment = (char*)g_malloc ( sizeof ( char) * 31);
					memset ( id3tag->comment, '\0', 31);
					/* str_kept_ascii ( id3.comment, 30); */
					strncpy ( id3tag->comment, id3.comment, 30);
					gw_str_trim ( id3tag->comment);
					if ( strlen ( id3tag->comment) == 0)
					{
						g_free ( id3tag->comment);
						id3tag->comment = NULL;
					}

					id3tag->version = g_strdup ( "1.0");
			}

			id3tag->gennum = id3.genre & 0xFF;
			if ((id3tag->gennum < 0) || (id3tag->gennum >= genre_largest)) {
				id3tag->gennum = 255;
			}

			id3tag->genre = (char*)g_malloc ( sizeof ( char) * 31);
			memset ( id3tag->genre, '\0', 31);
			strcpy ( id3tag->genre, genres[(id3tag->gennum<=genre_largest)?id3tag->gennum:genre_largest]);
			/* str_kept_ascii ( id3tag->genre); */
			if ( strlen ( id3tag->genre) == 0)
			{
				g_free ( id3tag->genre);
				id3tag->genre = NULL;
			}

			return 0;
		}
	}

#ifdef __DEBUG__
	g_print ( "readed %d\n", temp);
#endif

#ifdef __DEBUG__
	g_print ( "read id3v1x\n");
#endif

	if ( fseek ( file, -384, SEEK_END) != -1) {
		if ( (temp = fread ( &id3x, 256, 1, file)) == 1 )
		{
			if ( !strncmp ( id3x.tag, "TXG", 3)) {
				buffer = (char*)g_malloc ( sizeof ( char) * 121);
				strncpy ( buffer, id3tag->title, 30);
				strncat ( buffer, id3x.title, 90);
				g_free ( id3tag->title);
				id3tag->title = buffer;
				id3tag->title[strlen(id3tag->title)]='\0';
				gw_str_trim ( id3tag->title);
				if ( strlen ( id3tag->title) == 0)
				{
					g_free ( id3tag->title);
					id3tag->title = NULL;
				}
	
				buffer = (char*)g_malloc ( sizeof ( char) * 81);
				strncpy ( buffer, id3tag->artist, 30);
				strncat ( buffer, id3x.artist, 50);
				g_free ( id3tag->artist);
				id3tag->artist = buffer;
				id3tag->artist[strlen(id3tag->artist)]='\0';
				gw_str_trim ( id3tag->artist);
				if ( strlen ( id3tag->artist) == 0)
				{
					g_free ( id3tag->artist);
					id3tag->artist = NULL;
				}
	
				buffer = (char*)g_malloc ( sizeof ( char) * 81);
				strncpy ( buffer, id3tag->album, 30);
				strncat ( buffer, id3x.album, 50);
				g_free ( id3tag->album);
				id3tag->album = buffer;
				id3tag->album[strlen(id3tag->album)]='\0';
				gw_str_trim ( id3tag->album);
				id3tag->album[strlen(id3tag->album)]='\0';
				if ( strlen ( id3tag->album) == 0)
				{
					g_free ( id3tag->album);
					id3tag->album = NULL;
				}
	
				buffer = (char*)g_malloc ( sizeof ( char) * 81);
				strncpy ( buffer, id3tag->comment, 30);
				strncat ( buffer, id3x.comment, 50);
				g_free ( id3tag->comment);
				id3tag->comment = buffer;
				id3tag->comment[strlen(id3tag->album)]='\0';
				gw_str_trim ( id3tag->comment);
				id3tag->comment[strlen(id3tag->comment)]='\0';
				if ( strlen ( id3tag->comment) == 0)
				{
					g_free ( id3tag->comment);
					id3tag->comment = NULL;
				}
	
				buffer = (char*)g_malloc ( sizeof ( char) * 5);
				strncpy ( buffer, id3tag->version, 4);
				strncat ( buffer, "X", 1);
				g_free ( id3tag->version);
				id3tag->version = buffer;
				id3tag->version[strlen(id3tag->version)]='\0';
			}
		}

#ifdef __DEBUG__
		g_print ( "readed %d\n", temp);
#endif
	}

	return 1;
}


unsigned int file_read_size ( const unsigned char *size_stream, const int length) {
	unsigned int tag_size = 0;
	int i;
	const int SHIFT = (length - 1) * 7; /* Starting value in order to shift. */


	/* Decodes number. */
	for (i = 0; i < length; i++)
	{
		tag_size |= (unsigned int)size_stream[i] << (SHIFT - (i * 7));
	}

	return tag_size;
}


void file_read_string_from_id3v2 ( FILE* file, const unsigned int size, char** value)
{
	char buffer[size];
	char *tmp = NULL;
	int i,j;


	if ( size > 0 ) {
		*value = (char*)g_malloc ( sizeof ( char) * (size + 1));
		memset ( *value, '\0', size + 1);
		tmp = *value;

		/* Reads the data. */
		fread ( buffer, size, 1, file);

		/* Adds data to the temporary stream. */
		for (i = 0, j = 0; i < size; i++)
		{
			/* Filters the undisplayable data. */
			if ( (buffer[i] >= 32) && (buffer[i] <= 126) )
			{
				tmp[j] = buffer[i];
				j++;
			}
		}

		/* Checks if data is empty. */
		if ( j == 0 )
		{
			g_free ( *value);
			*value = NULL;
		}
		else
		{
			/* Completes the stream by 0 character (it is really mandatory thanks memset?). */
			while ( j <= size )
			{
				tmp[j++] = '\0';
			}

			/* Removes all leading and endind spaces. */
			gw_str_trim ( &tmp[0]);

			/* Checks if data is empty. */
			if ( strlen ( *value) == 0 )
			{
				g_free ( *value);
				*value = NULL;
			}
		}
	}

	return;
}


void file_read_id3v24 ( FILE* file, id3 *id3tag)
{
	char tag_stream[5];
	unsigned char size[4];
	unsigned int field_size;
	int tag_size;
	long pos = 0;


#ifdef __DEBUG__
	g_print ( "read id3v24\n");
#endif

	/* Checks the size of id3 tag. */
	fseek ( file, 6L, SEEK_SET);
	fread ( size, 4, 1, file);
	tag_size = file_read_size ( size, 4);

	while ( pos < tag_size )
	{
		/* Reads the field name. */
		fread ( tag_stream, 4, 1, file);
		tag_stream[4] = '\0';

		/* Reads the field size. */
		fread ( size, 4, 1, file);
		field_size = file_read_size ( size, 4);
		fseek ( file, 2L, SEEK_CUR);

		/* Checks if the size tag is always valid. */
		if ( pos + 4 + 4 + field_size > tag_size)
		{
			return;
		}

		/* Chooses the good informations. */
		if ( tag_stream != NULL )
		{
			if ( !strcmp ( tag_stream, "TOAL") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->album);
			}
			else if (!strcmp(tag_stream, "TPE1") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->artist);
			}
			else if ( !strcmp ( tag_stream, "TYER") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->year);
			}
			else if ( !strcmp ( tag_stream, "TIT2") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->title);
			}
			else if ( !strcmp ( tag_stream, "COMM") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->comment);
			}
			else if ( !strcmp ( tag_stream, "TRCK") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->track);
			}
			else if ( !strcmp ( tag_stream, "TENC") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->encoder);
			}
			else if ( !strcmp ( tag_stream, "WXXX") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->url);
			}
			else if ( !strcmp ( tag_stream, "TCOP") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->copyright);
			}
			else if ( !strcmp ( tag_stream, "TCOM") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->compositer);
			}
			else if ( !strcmp ( tag_stream, "TCON") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->genre);
			}
			else
				fseek ( file, field_size, SEEK_CUR);
		}

		/* Gets the current position in the file. */
		pos = ftell ( file);
	}

	return;
}


void file_read_id3v23 ( FILE* file, id3 *id3tag)
{
	char tag_stream[5];
	unsigned char size[4];
	unsigned int field_size;
	int tag_size;
	long pos = 0;


#ifdef __DEBUG__
	g_print ( "read id3v23\n");
#endif

	/* Checks the size of id3 tag. */
	fseek ( file, 6L, SEEK_SET);
	fread ( size, 4, 1, file);
	tag_size = file_read_size ( size, 4);

	while ( pos < tag_size )
	{
		/* Reads the field name. */
		fread ( tag_stream, 4, 1, file);
		tag_stream[4] = '\0';

		/* Reads the field size. */
		fread ( size, 4, 1, file);
		field_size = file_read_size ( size, 4);

		/* Checks if the size tag is always valid. */
		if ( pos + 4 + 4 + field_size > tag_size)
		{
			return;
		}

		fseek ( file, 2L, SEEK_CUR);

		/* Chooses the good informations. */
		if ( tag_stream != NULL )
		{
			if ( !strcmp ( tag_stream, "TALB") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->album));
			}
			else if ( !strcmp ( tag_stream, "TPE1") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->artist));
			}
			else if ( !strcmp ( tag_stream, "TYER") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->year));
			}
			else if ( !strcmp ( tag_stream, "TIT2"))
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->title));
			}
			else if ( !strcmp ( tag_stream, "COMM") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->comment));
			}
			else if ( !strcmp ( tag_stream, "TRCK") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->track));
			}
			else if ( !strcmp ( tag_stream, "TENC") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->encoder));
			}
			else if ( !strcmp ( tag_stream, "WXXX") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->url));
			}
			else if ( !strcmp ( tag_stream, "TCOP") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->copyright));
			}
			else if ( !strcmp ( tag_stream, "TCOM") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->compositer));
			}
			else if ( !strcmp ( tag_stream, "TCON") )
			{
				file_read_string_from_id3v2 ( file, field_size, &(id3tag->genre));
			}
			else
			{
				fseek ( file, field_size, SEEK_CUR);
			}
		}

		/* Gets the current position in the file. */
		pos = ftell ( file);
	}

	return;
}


void file_read_id3v22 ( FILE* file, id3 *id3tag)
{
	char tag_stream[4];
	unsigned char size[4];
	unsigned int field_size;
	int tag_size;
	long pos = 0;


#ifdef __DEBUG__
	g_print ( "read id3v22\n");
#endif

	/* Checks the size of id3 tag. */
	fseek ( file, 6L, SEEK_SET);
	fread ( size, 4, 1, file);
	tag_size = file_read_size ( size, 4);

	while ( pos < tag_size)
	{
		/* Reads the field name. */
		fread ( tag_stream, 3, 1, file);
		tag_stream[3] = '\0';

		/* Reads the field size. */
		fread ( size, 3, 1, file);
		field_size = file_read_size ( size, 3);

		/* Checks if the size tag is always valid. */
		if ( pos + 4 + 4 + field_size > tag_size)
		{
			return;
		}

		/* Reads the good informations. */
		if ( tag_stream != NULL )
		{
			if ( !strcmp ( tag_stream, "TAL") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->album);
			}
			else if ( !strcmp ( tag_stream, "TP1") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->artist);
			}
			else if ( !strcmp ( tag_stream, "TYE") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->year);
			}
			else if ( !strcmp ( tag_stream, "TT2") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->title);
			}
			else if ( !strcmp ( tag_stream, "TRK") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->track);
			}
			else if ( !strcmp ( tag_stream, "TYE") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->year);
			}
			else if ( !strcmp ( tag_stream, "TCM") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->compositer);
			}
			else if ( !strcmp ( tag_stream, "TCO") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->genre);
			}
			else if ( !strcmp ( tag_stream, "WXX") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->url);
			}
			else if ( !strcmp ( tag_stream, "TEN") )
			{
				file_read_string_from_id3v2 ( file, field_size, &id3tag->encoder);
			}
			else
			{
				fseek ( file, field_size, SEEK_CUR);
			}
		}

		/* Gets the current position in the file. */
		pos = ftell ( file);
	}

	return;
}


void file_read_id3v2_version ( FILE* file, char *version)
{
	fseek ( file, 3L, SEEK_SET);
	fread ( version, 1, 1, file);

	return;
}


void file_read_id3v2 ( FILE* file, id3 *id3tag)
{
	char version;


#ifdef __DEBUG__
	g_print ( "read id3v2\n");
#endif

	/* Reads the size of the tag. */
	file_read_id3v2_version ( file, &version);

	/* Chooses the good version. */
	if (version == 2)
	{
		id3tag->version = g_strdup ( "2.2");
		file_read_id3v22 ( file, id3tag);
	}
	else if (version == 3)
	{
		id3tag->version = g_strdup ( "2.3");
		file_read_id3v23 ( file, id3tag);
	}
	else if (version == 4)
	{
		id3tag->version = g_strdup ( "2.4");
		file_read_id3v24 ( file, id3tag);
	}

	return;
}


char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	g_print ( "MP3 module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "Sébastien LECACHEUR";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract description in MP3 file from ID3 Tag version 1.0, 1.0x, 1.1, 1.1x, 2.2, 2.3, 2.4.";
}


const char * plugin_get_version ( void)
{
	return "1.0.0";
}


const char * plugin_get_help ( void)
{
	return "No help at time";
}


const char * plugin_get_allowed_ext ( void)
{
	return "mp1|mp2|mp3";
}


char * plugin_get_file_descr ( const char *filepath, const char *mode) {
	struct mp3data mp3;
	id3 tag;
	float ver = 0;
	int layer = 0, err = 1;
	FILE *file = NULL;
	char id3indentifier[4] = "";
	gchar *descr = NULL, *tmp = NULL;


	if ( filepath != NULL )	{
#ifdef __DEBUG__
		g_print ( "\nStarting extraction of %s :\n", filepath);
#endif
	
		if ( !(err = file_mp3_get_header ( filepath, &mp3))) {
			if (mp3.mpeg_version == MPEG_VERSION_1) {
				ver = 1;
			}
		
			if (mp3.mpeg_version == MPEG_VERSION_2) {
				ver = 2;
			}
		
			if (mp3.mpeg_version == MPEG_VERSION_2_5) {
				ver = 2.5;
			}
		
			if (mp3.layer_desc == LAYER_VERSION_1) {
				layer = 1;
			}
		
			if (mp3.layer_desc == LAYER_VERSION_2) {
				layer = 2;
			}
		
			if (mp3.layer_desc == LAYER_VERSION_3) {
				layer = 3;
			}
		} else {
#ifdef __DEBUG__
			if ( err == INVALID_HEADER ) {
				g_print ( "- Invalid header!!\n");
			}
#endif
		}

		tag.version = NULL;
		tag.title = NULL;
		tag.artist = NULL;
		tag.album = NULL;
		tag.year = NULL;
		tag.comment = NULL;
		tag.genre = NULL;
		tag.track = NULL;
		tag.url = NULL;
		tag.compositer = NULL;
		tag.copyright = NULL;
		tag.tracknum = -1;
		tag.gennum = -1;
	
		if ( (file = fopen ( filepath, "rb")) != NULL ) {
			fread ( id3indentifier, sizeof ( char) * 3, 1, file);
			id3indentifier[3] = '\0';
	
			if ( !( strncmp ( id3indentifier, "ID3", 3))) {
				file_read_id3v2 ( file, &tag);
			} else {
				file_read_id3v1 ( file, &tag);
			}

			fclose ( file);

#ifdef __DEBUG__
			if ( tag.version != NULL) {
				g_print ( "- Version : id3v%s\n", tag.version);
				g_print ( "- Title : %s\n", tag.title);
				g_print ( "- Artist : %s\n", tag.artist);
				g_print ( "- Album : %s\n", tag.album);
				g_print ( "- Year : %s\n", tag.year);
				g_print ( "- Comment : %s\n", tag.comment);
				g_print ( "- Genre : %s\n", tag.genre);
				g_print ( "- Track : %s\n", tag.track);
				g_print ( "- URL : %s\n", tag.url);
				g_print ( "- Compositer : %s\n", tag.compositer);
				g_print ( "- Copyright : %s\n", tag.copyright);
			}
#endif
	
			if ( !err) {
				if ( mp3.mpeg_version != MPEG_VERSION_2_5 ) {
					descr = g_strdup_printf ( "MPEG Version %.0f, Layer %i\nBitrate:%i KBit/s\nFrequency:%i Hz\nMode:%s\n",ver, layer, mp3.bitrate, mp3.frequency,  ((mp3.channels == 2)?"Stereo":"Mono"));
				} else {
					descr = g_strdup_printf ( "MPEG Version %.0f, Layer %i\nFrequency:%i Hz\nMode:%s\n",ver, layer, mp3.frequency, ((mp3.channels == 2)?"Stereo":"Mono"));
				}
			}

			if ( tag.version != NULL ) {
				if ( descr == NULL ) {
					descr = g_strdup ( "");
				}

				if ( tag.title != NULL ) {
					descr = g_strconcat ( (tmp = descr), "Title:", tag.title, "\n", NULL);
					g_free ( tmp);
			}
	
				if ( tag.artist != NULL ) {
					descr = g_strconcat ( (tmp = descr), "Artist:", tag.artist, "\n", NULL);
					g_free ( tmp);
				}
	
				if ( tag.album != NULL ) {
					descr = g_strconcat ( (tmp = descr), "Album:", tag.album, "\n", NULL);
					g_free ( tmp);
				}
	
				if ( tag.genre != NULL ) {
					descr = g_strconcat ( (tmp = descr), "Genre:", tag.genre, "\n", NULL);
					g_free ( tmp);
				}
			}
	
			if ( tag.version != NULL ) {
				if ( tag.version != NULL) g_free ( tag.version);
				if ( tag.title != NULL) g_free ( tag.title);
				if ( tag.artist != NULL) g_free ( tag.artist);
				if ( tag.album != NULL) g_free ( tag.album);
				if ( tag.year != NULL) g_free ( tag.year);
				if ( tag.comment != NULL) g_free ( tag.comment);
				if ( tag.genre != NULL) g_free ( tag.genre);
				if ( tag.track != NULL) g_free ( tag.track);
				if ( tag.url != NULL) g_free ( tag.url);
				if ( tag.compositer != NULL) g_free ( tag.compositer);
				if ( tag.copyright != NULL) g_free ( tag.copyright);
			}
		}
	
#ifdef __DEBUG__
		g_print ( "Extracted description is :\nSTART\n%s\nEND\n", descr);
#endif
	}

	return descr;
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	g_print ( "MP3 module is unloading...\n");
#endif
}
