/*  GWhere.
 *  Copyright (C) Andree Buschmann and Frank Klemm
 *  Modified Raphael MARINIER
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

//#define _TEST_STANDALONE
//#define __DEBUG__ 1

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "mppdec.h"


/*
 *  List of known Genres. 256 genres are possible with version 1/1.1 tags,
 *  but not yet used.
 */
static const char*  GenreList [] = {
    "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge",
    "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B",
    "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska",
    "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient",
    "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical",
    "Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise",
    "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative",
    "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
    "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream",
    "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap",
    "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave",
    "Psychadelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal",
    "Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll",
    "Hard Rock", "Folk", "Folk/Rock", "National Folk", "Swing", "Fast-Fusion",
    "Bebob", "Latin", "Revival", "Celtic", "Bluegrass", "Avantgarde",
    "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock",
    "Slow Rock", "Big Band", "Chorus", "Easy Listening", "Acoustic", "Humour",
    "Speech", "Chanson", "Opera", "Chamber Music", "Sonata", "Symphony",
    "Booty Bass", "Primus", "Porn Groove", "Satire", "Slow Jam", "Club",
    "Tango", "Samba", "Folklore", "Ballad", "Power Ballad", "Rhythmic Soul",
    "Freestyle", "Duet", "Punk Rock", "Drum Solo", "A capella", "Euro-House",
    "Dance Hall", "Goa", "Drum & Bass", "Club House", "Hardcore", "Terror",
    "Indie", "BritPop", "NegerPunk", "Polsk Punk", "Beat", "Christian Gangsta",
    "Heavy Metal", "Black Metal", "Crossover", "Contemporary C",
    "Christian Rock", "Merengue", "Salsa", "Thrash Metal", "Anime", "JPop",
    "SynthPop"
};


struct APETagFooterStruct {
    Uint8_t   ID       [8];    // should equal 'APETAGEX'
    Uint8_t   Version  [4];    // currently 1000 (version 1.000)
    Uint8_t   Length   [4];    // the complete size of the tag, including this footer
    Uint8_t   TagCount [4];    // the number of fields in the tag
    Uint8_t   Flags    [4];    // the tag flags (none currently defined)
    Uint8_t   Reserved [8];    // reserved for later use
};


char * get_extra_info ( FILE *f, int size);


#ifdef _TEST_STANDALONE
char * plugin_get_file_descr ( const char *filepath, const char *mode);


int main ( int argc, char **argv)
{
	if (argc==1) {
		printf ( "usage: mpc_info file\n");
		return 0;
	}

	for (int i=1;i<argc;i++) {
		printf("\nSTART\n%s\nEND\n" , plugin_get_file_descr ( argv[i],NULL));
	}

	return 0;
}
#endif //_TEST_STANDALONE


char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	printf ( "MPC module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "RaphaÎl Marinier";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract description in MPC file (mpeg+) from version SV4 to SV7";
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
	return "mpc|mpp|mp+";
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	printf ( "MPC module is unloading...\n");
#endif
}


char * plugin_get_file_descr ( const char *filepath, const char *mode) {
	char *tmp = NULL, *descr = NULL;
	TagInfo_t tag;
	gboolean presence_tag = FALSE;
	FILE *f = NULL;


	if ( (filepath != NULL) && (f = fopen ( filepath, "rb")) != NULL ) {
		tag.Title = NULL;
		tag.Artist = NULL;
		tag.Album = NULL;
		tag.Track = NULL;
		tag.Genre = NULL;
		tag.Year = NULL;
		tag.Comment = NULL;

#ifdef __DEBUG__
		g_print("File is %s\n",filepath);
#endif

		if ( !(presence_tag = Read_ID3V1_Tags ( f, &tag)) ) {
			if ( !(presence_tag = Read_APE_Tags ( f, &tag)) ) {
#ifdef __DEBUG__
				g_print("No tag was founded\n");
#endif
			} else {
#ifdef __DEBUG__
				g_print("APE tag was founded\n");
#endif
			}
		} else {
#ifdef __DEBUG__
			g_print("ID3V1 tag was founded\n");
#endif
		}


		if ( presence_tag == TRUE ) {
			if ( (descr = get_extra_info ( f, tag.FileSize)) == NULL ) {
				descr = g_strdup ( "");
			}

			if ( tag.Title != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Title:", tag.Title, "\n", NULL);
				g_free ( tmp);
			}

			if ( tag.Artist != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Artist:", tag.Artist, "\n", NULL);
				g_free ( tmp);
			}

			if ( tag.Album != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Album:", tag.Album, "\n", NULL);
				g_free ( tmp);
			}

			if ( tag.Genre != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Genre:", tag.Genre, NULL);
				g_free ( tmp);
			}

			if ( tag.Title != NULL) free ( tag.Title);
			if ( tag.Artist != NULL) free ( tag.Artist);
			if ( tag.Album != NULL) free ( tag.Album);
			if ( tag.Track != NULL) free ( tag.Track);
			if ( tag.Genre != NULL) free ( tag.Genre);
			if ( tag.Year != NULL) free ( tag.Year);
			if ( tag.Comment != NULL) free ( tag.Comment);

		}

		fclose ( f);
	}

#ifdef __DEBUG__
	g_print("description :\n%s\n",descr);
#endif

	return descr;
}


/*
 *  Copies src to dst. Copying is stopped at `\0' char is detected or if
 *  len chars are copied.
 *  Trailing blanks are removed and the string is `\0` terminated.
 */
static void memcpy_crop ( char* dst, const char* src, size_t len ) {
	size_t  i;


	for ( i = 0; i < len; i++ ) {
		if ( src[i] != '\0' ) {
            		dst[i] = src[i];
	 	} else {
			break;
		}
	}

	/* dst[i] points behind the string contents. */
	while ( (i > 0)  &&  (dst [i-1] == ' ') ) {
		i--;
	}

	dst [i] = '\0';
}


/*
 *  Evaluate ID version 1/1.1 tags of a file given by 'fp' and fills out Tag
 *  information in 'tip'. Tag information also contains the effective file
 *  length (without the tags if tags are present). Return 1 if there is
 *  usable information inside the file. Note there's also the case possible
 *  that the file contains empty tags, the the file size is truncated by the
 *  128 bytes but the function returns 0.
 *
 *  If there're no tags, all strings containing '\0', the Genre pointer is
 *  NULL and GenreNo and TrackNo are -1.
 *
 *  Returns 0 if there is no tag or invalid tag
 *  Returns 1 if there is a tag
 *
 */
int Read_ID3V1_Tags ( FILE_T fp, TagInfo_t* tip )
{
    Uint8_t      tmp [128];
    OFF_T        file_pos;
    const char*  q;

    memset ( tip, 0, sizeof(*tip) );
    tip->GenreNo = -1;
    tip->TrackNo = -1;

    if ( -1 == (file_pos = FILEPOS (fp)) )
        return 0;
    if ( -1 == SEEK ( fp, -128L, SEEK_END ) )
        return 0;

    tip->FileSize = FILEPOS (fp);
    if ( 128 != READ ( fp, tmp, 128 ) )
        return 0;
    SEEK ( fp, file_pos, SEEK_SET );

    if ( 0 != memcmp ( tmp, "TAG", 3 ) ) {
        tip->FileSize += 128;
        return 0;
    }

    if ( !tmp[3]  &&  !tmp[33]  &&  !tmp[63]  &&  !tmp[93]  &&  !tmp[97] )
        return 0;

    memcpy_crop  ( tip->Title   =(char*) realloc (tip->Title  , 31),(const char*) tmp +  3, 30 );
    memcpy_crop  ( tip->Artist  =(char*) realloc (tip->Artist , 31),(const char*) tmp + 33, 30 );
    memcpy_crop  ( tip->Album   =(char*) realloc (tip->Album  , 31),(const char*) tmp + 63, 30 );
    memcpy_crop  ( tip->Year    = (char*)realloc (tip->Year   ,  5),(const char*) tmp + 93,  4 );
    memcpy_crop  ( tip->Comment =(char*) realloc (tip->Comment, 31),(const char*) tmp + 97, 30 );

    q = tmp[127] < sizeof(GenreList)/sizeof(*GenreList)  ?
                         GenreList [tip->GenreNo = tmp[127]]  :  "???";
    strcpy ( tip->Genre = (char*)realloc (tip->Genre, strlen(q)+1), q );

    // Index 0 may be true if file is very short
    tip->Track =(char*) realloc (tip->Track, 6);
    if ( tmp[125] == 0  &&  (tmp[126] != 0  ||  tip->FileSize < 66000 ) )
        sprintf ( tip->Track, "[%02d]", tip->TrackNo = tmp[126] );
    else
        strcpy ( tip->Track, "    " );

    return 1;
}


static Uint32_t Read_LE_Uint32 ( const Uint8_t* p )
{
    return ((Uint32_t)p[0] <<  0) |
           ((Uint32_t)p[1] <<  8) |
           ((Uint32_t)p[2] << 16) |
           ((Uint32_t)p[3] << 24);
}


#define TAG_ANALYZE(item,elem)                      \
    if ( 0 == memcmp (p, #item, sizeof #item ) ) {  \
        p += sizeof #item;                          \
        tip->elem = (char*)realloc (tip->elem, len+1);     \
        memcpy ( tip->elem, p, len );               \
        tip->elem [len] = '\0';                     \
        p += len;                                   \
    } else


Int Read_APE_Tags ( FILE_T fp, TagInfo_t* tip ) {
	OFF_T file_pos = 0;
	Uint32_t len = 0;
	Uint32_t flags = 0;
	unsigned char buff [8192];
	unsigned char *p = NULL;
	unsigned char *end = NULL;
	struct APETagFooterStruct T;
	Uint32_t TagLen = 0;
	Uint32_t TagCount = 0;
	Uint32_t tmp = 0;


	memset(buff,0,8192);
	memset(tip,0,sizeof(*tip));
	tip->GenreNo = -1;
	tip->TrackNo = -1;

	if ( -1 == (file_pos = FILEPOS (fp)) ) {
		goto notag;
	}

	if ( -1 == SEEK ( fp, 0L, SEEK_END ) ) {
		goto notag;
	}
	tip->FileSize = FILEPOS (fp);

	if ( -1 == SEEK ( fp, -(long)sizeof T, SEEK_END ) ) {
        	goto notag;
	}

	if ( sizeof(T) != READ ( fp, &T, sizeof T ) ) {
        	goto notag;
	}

	if ( memcmp ( T.ID, "APETAGEX", sizeof(T.ID) ) != 0 ) {
		goto notag;
	}

	tmp = Read_LE_Uint32(T.Version);
	if (  tmp != 1000  &&  tmp != 2000 ) {
        	goto notag;
	}

	TagLen = Read_LE_Uint32 (T.Length);
    	if ( TagLen <= sizeof(T) ) {
		goto notag;
	}

	if ( -1 == SEEK ( fp, -(long)TagLen, SEEK_END ) ) {
		goto notag;
	}
	tip->FileSize = FILEPOS (fp);

//	memset ( buff, 0, sizeof(buff) );
	if ( TagLen - sizeof(T) != READ ( fp, buff, TagLen - sizeof(T)) ) {
		goto notag;
	}
	SEEK ( fp, file_pos, SEEK_SET );

	TagCount = Read_LE_Uint32 (T.TagCount);
	end = buff + TagLen - sizeof(T);

	for ( p = buff; p < end  &&  TagCount--; ) {
        	len = Read_LE_Uint32 ( p );
		p += 4;
        	flags = Read_LE_Uint32 ( p );
		p += 4;
#ifdef __DEBUG__
		g_print("buff[%d]=%s\n",p-buff,p);
#endif
        	TAG_ANALYZE(Title,Title)
        	TAG_ANALYZE(Album,Album)
        	TAG_ANALYZE(Artist,Artist)
        	TAG_ANALYZE(Album,Album)
        	TAG_ANALYZE(Comment,Comment)
        	TAG_ANALYZE(Track,Track)
        	TAG_ANALYZE(Year,Year)
        	TAG_ANALYZE(Genre,Genre)
        	{
            		p += strlen((const char*)p) + 1 + len;
        	}
	}

    if ( tip->Track != NULL  &&  tip->Track[0] != '\0' ) {
        tip->TrackNo = atoi (tip->Track);
        tip->Track   =(char*) realloc (tip->Track, 13 );
        sprintf ( tip->Track, "[%02d]", tip->TrackNo );
    }
    else {
        tip->Track   =(char*) realloc (tip->Track, 5 );
        strcpy ( tip->Track, "    " );
    }

    /* Genre wird noch nicht ausdekodiert */
    return 1;

notag:
    SEEK ( fp, file_pos, SEEK_SET );
    return 0;
}


/***** extra info ********/

//fonction pour lire le fichier mpc.
void DecodeFile ( FILE_T InputFile,int FileSize , int *bitrate_ret,char **time_ret, char **streamversion_ret, char **profile_ret );
static const char* EncoderName ( int encoderno );
static Int32_t JumpID3v2 ( void );
static const char* PrintTime ( Double samples, char sign );
static const char* ProfileName ( Uint profile );        // profile is 0...15, where 1, 5...15 is used

// global du dÈcodeur :
static Ulong      InputBuffRead;
static Uint       StreamVersion;
Bool_t            TrueGaplessPresent =  0;  // is true gapless used?
Int               LastValidSamples   =  0;  // number of valid samples within last frame
Uint              DUMPSELECT         =  0;
unsigned int      SampleFreq         =  44100;
static int        Channels           =  2;
static const Uint16_t sftable [4] = { 44100, 48000, 37800, 32000 };
Int Bitrate;

Bool_t            MS_used            =  0;  // 0: all is LR coded, 1: MS or LR coding per subband
Bool_t            IS_used            =  0;  // is IS used (if yes, a fixed number of subbands is IS coded)
//static Float      Scale              =  1.; // user defined scale factor
//static Bool_t     ClipPrev           =  0;  // if set, clipping is prevented if needed information is available
//static int        ReplayGainType     =  0;  // 0: no additional gain, 1: CD based gain correction, 2: title based gain correction

//globales de decode.c :

#define BITS     (CHAR_BIT * sizeof(*InputBuff))      // Bits per InputBuff-Word

Ibuf_t           InputBuff [IBUFSIZE /* +128 */ ];  // enth‰lt den Lese-Puffer
static Uint32_t  mask      [32 + 1];
size_t           InputCnt;             // aktuelle Position im Lese-Puffer
static Ibuf_t    dword;                // BITS Bit-Wort f¸r Bitstrom-I/O
static Uint      pos;                  // Position im aktuell decodierten BITS-bit-Wort
static size_t    LastInputCnt = 0;
static Uint      Wraps        = 0;


//fonction d'ajout des infos
char * get_extra_info ( FILE *f, int size)
{
	int bitrate;
	char *descr = NULL, *tmp = NULL;
	char *temps = NULL, *streamversion = NULL, *profile = NULL;


	if ( (f != NULL) && (size > 0) )
	{
		DecodeFile ( f, size, &bitrate, &temps, &streamversion, &profile);

		if ( streamversion && bitrate && temps && profile )
		{
			if ( streamversion != NULL ) {
				descr = g_strdup_printf ( "MPC file (MPEG+%s)\n", streamversion);
				free ( streamversion);
			} else {
				descr = g_strdup ( "MPC file (MPEG+)\n");
			}

			if ( bitrate != 0 ) {
				descr = g_strdup_printf ( "%sBitrate: %d\n", (tmp = descr), bitrate);
				g_free ( tmp);
			}

			if ( temps != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Length: ", temps, "\n", NULL);
				g_free ( tmp);
				free ( temps);
			}

			if ( profile != NULL ) {
				descr = g_strconcat ( (tmp = descr), "Profile: ", profile, "\n", NULL);
				g_free ( tmp);
				free ( profile);
			}

		}
	}

	return descr;
}


void DecodeFile ( FILE_T InputFile, int FileSize, int *bitrate_ret,char **time_ret, char **streamversion_ret, char **profile_ret )
{
    Int        MaxBandDesired = 0;
    Uint32_t   TotalFrames    = 0;
//    Double     DecodedSamples = 0.;
    Uint       Profile        = (Uint)-1;
    Double     AverageBitrate;
//    clock_t    T;
    Int32_t    ID3v2;
    Uint16_t   PeakTitle = 0;
    Uint16_t   PeakAlbum = 0;
//    Uint16_t   Peak;
    Uint16_t   tmp;
    Int16_t    GainTitle = 0;
    Int16_t    GainAlbum = 0;
//    Int16_t    Gain;
    int        Encoder;
    Bool_t     SecurePeakTitle = 0;
//    Float      ReplayGain;       // 0...1...+oo
//    Float      ClipCorr;         // 0...1
    size_t     HeaderLen;

    // Fill the bitstream buffer for the first time
resume:
    Bitstream_init ();
    InputBuffRead = Read_LittleEndians ( InputFile, InputBuff, IBUFSIZE );

    // Test the first 4 bytes ("MP+": SV7+, "ID3": ID3V2, other: may be SV4...6)
    switch ( Bitstream_preview(32) ) {
    case (Uint32_t)0x01334449L:                                         /* ID3 V2.1...2.4 */
    case (Uint32_t)0x02334449L:
    case (Uint32_t)0x03334449L:
    case (Uint32_t)0x04334449L:
#ifdef __DEBUG__
       fprintf(stderr, "\n"PROG_NAME": Stream was corrupted by an ID3 Version 2 tagger\n\n" );
#endif
        ID3v2 = JumpID3v2 ();
        if ( SEEK ( InputFile, ID3v2, SEEK_SET ) < 0 ) {
#ifdef __DEBUG__
            fprintf(stderr, "\n\nSorry, recovering fails.\n\a" );
#endif
            return ;
        }
//        sleep (1);
#ifdef __DEBUG__
        fprintf(stderr,"\b\b\b\b, ignore %lu words and %u bits ...\n\a", (unsigned long)ID3v2 >> 2, (int)(ID3v2&3) << 3 );
#endif
        goto resume;

    case (Uint32_t)0x072B504DL:                                         /* MP+ SV7 */
    case (Uint32_t)0x172B504DL:                                         /* MP+ SV7.1 */
    case (Uint32_t)0xF72B504DL:                                         /* MP+ SV7.F */
    case (Uint32_t)0xFF2B504DL:                                         /* MP+ SVF.F */
        StreamVersion  = (Int) Bitstream_read (8);
        (void) Bitstream_read (24);
        break;

    case (Uint32_t)0x2043414DL:                                         /* MAC  */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "Monkey's Audio" );
#endif
        return;

    case (Uint32_t)0x7961722E:                                         /* Real Audio */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "Real Audio" );
#endif
        return;

    case (Uint32_t)0x46464952L:                                         /* WAV  */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "Microsoft WAVE" );
#endif
        return;

    case (Uint32_t)0x43614C66L:                                         /* FLAC */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "FLAC" );
#endif
        return;

    case (Uint32_t)0x4341504CL:                                         /* LPAC */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "LPAC" );
#endif
        return;

    case (Uint32_t)0x37414B52L:                                         /* RKAU */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "RKAU" );
#endif
        return;

    case (Uint32_t)0x676B6A61L:                                         /* Shorten */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "Shorten" );
#endif
        return;

    case (Uint32_t)0x040A5A53L:                                         /* SZIP 1.12 */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "szip" );
#endif
        return;

    case (Uint32_t)0x5367674FL:                                         /* OggS */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "Ogg Stream" );
#endif
        return;

    case (Uint32_t)0x46494441L:                                         /* AAC-ADIF */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "AAC Audio Data Interchange Format" );
#endif
        return;

    case (Uint32_t)0x75B22630L:                                         /* MS WMA */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "MS Windows Media Audio" );
#endif
        return;

    case (Uint32_t)0xBA010000L:                                         /* MPEG system stream */
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "MPEG system stream/VOB" );
#endif
        return;

    default:
        StreamVersion = (Uint32_t) Bitstream_preview (32);
        if ( ( StreamVersion & 0x00FFFFFF ) == (Uint32_t)0x002B504DL ) {
            StreamVersion >>= 24;
#ifdef __DEBUG__
            fprintf(stderr, "\n"PROG_NAME": Input File seems to be a MPC file StreamVersion %u.%u\nVisit http://www.uni-jena.de/~pfk/mpc/ and update your software.\n\n", StreamVersion & 15, StreamVersion >> 4 );
#endif
            return;
        }

        if ( ( (Bitstream_preview (32)) & 0x0000FFFF ) == (Uint32_t)0x0000770BL ) {
#ifdef __DEBUG__
    	    fprintf(stderr,"\n"PROG_NAME": Input File is a %s file\n", "AC3/Dolby Digital" );
#endif
    	    return;
	}

        StreamVersion = (Int) (Bitstream_preview (21) & 0x3FF);
        if ( StreamVersion < 4  ||  StreamVersion > 6 ) {
#ifdef __DEBUG__
            fprintf(stderr,"\n"PROG_NAME": Input File is not a MPC file, neither SV 4...6 nor SV 7 (SV %u)\n", StreamVersion );
#endif
            return;
        }
        break;
    }


    // decode the header for SV4...6 or SV7 or SV8
    switch ( StreamVersion ) {
    case 0x04:
    case 0x05:
    case 0x06:
        Bitrate        = (Int) Bitstream_read (9);
        IS_used        = (Int) Bitstream_read (1);
        MS_used        = (Int) Bitstream_read (1);
        StreamVersion  = (Int) Bitstream_read(10);
        MaxBandDesired = (Int) Bitstream_read (5);
        if ( Bitstream_read (6) != 1 ) {
#ifdef __DEBUG__
	    fprintf ( stderr, "Blocksize of != 1 is not supported any longer\n" );
#endif
	    return ;
	}
        TotalFrames    = Bitstream_read ( StreamVersion < 5  ?  16  :  32 );
        SampleFreq     = 44100;
        Encoder        = -1;
        Channels       =  2;

        if ( StreamVersion >= 4  &&  StreamVersion <= 6 )
            break;

    default:  // it should be impossible to execute the following code
#ifdef __DEBUG__
        fprintf(stderr,"\n"PROG_NAME": Internal error\n" );
        fprintf(stderr,"\n"PROG_NAME": Not a MPC file, neither SV 4...6 nor SV 7 (SV %u.%u)\n", StreamVersion & 15, StreamVersion >> 4 );
#endif
        return ;

    case 0x07:
    case 0x17:
        Bitrate        = 0;
        Channels       = 2;
        TotalFrames    = Bitstream_read (32);
        IS_used        = (Int) Bitstream_read (1);
        MS_used        = (Int) Bitstream_read (1);
        MaxBandDesired = (Int) Bitstream_read (6);

        // reading the profile
        Profile = (Int) Bitstream_read (4);
        (void) Bitstream_read ( 2);
        SampleFreq = sftable [ Bitstream_read ( 2) ];

        // reading peak and gain values from the file (or use useful values if they are absent)
        PeakTitle = (Uint16_t)(1.18 * (Uint32_t)Bitstream_read (16));
        GainTitle = Bitstream_read (16);
        tmp       = Bitstream_read (16);
        if ( (SecurePeakTitle = (tmp != 0)) )
            PeakTitle = tmp;
        GainAlbum = Bitstream_read (16);
        PeakAlbum = Bitstream_read (16);
        if ( PeakAlbum == 0 )
            PeakAlbum = PeakTitle;

        // reading true gapless
        TrueGaplessPresent = Bitstream_read ( 1);
        LastValidSamples   = Bitstream_read (11);
        (void) Bitstream_read (20);

        // reserved bytes for future use
        Encoder = Bitstream_read ( 8);
        break;

    case 0xF7:
    case 0xFF:
        Bitrate            = 0;
        TrueGaplessPresent = 1;

        HeaderLen        = (Uint16_t) Bitstream_read (16);
        Profile          = (Uint8_t)  Bitstream_read ( 8);
        Encoder          = (Uint8_t)  Bitstream_read ( 8);

        TotalFrames      = (Uint32_t) Bitstream_read (32);

        // reading peak and gain values from the file (or use useful values if they are absent)
        SecurePeakTitle  = 1;

        PeakTitle        = (Uint16_t) Bitstream_read (16);
        GainTitle        = (Int16_t)  Bitstream_read (16);

        PeakAlbum        = (Uint16_t) Bitstream_read (16);
        GainAlbum        = (Int16_t)  Bitstream_read (16);
        if ( PeakAlbum == 0 )
            PeakAlbum = PeakTitle;

        MaxBandDesired   = (Uint)     Bitstream_read ( 6);
        MS_used          = (Bool_t)   Bitstream_read ( 1);
                           (void)     Bitstream_read ( 9);
        LastValidSamples = (Uint)     Bitstream_read (16);

        Channels         = (Uint8_t)  Bitstream_read ( 8);
                           (void)     Bitstream_read (24);

        SampleFreq       = (Uint16_t) Bitstream_read (16);
                           (void)     Bitstream_read (16);

        for ( ; HeaderLen > 26; HeaderLen-- )
                           (void)     Bitstream_read ( 8);
        break;
    }

    // calculate bitrate for informational purpose
    if ( Bitrate == 0 ) {
        AverageBitrate = ( SampleFreq / 1000. / BLK_SIZE * 8 ) * FileSize / TotalFrames  ;
    }
    else {
        AverageBitrate = Bitrate;
    }

#ifdef __DEBUG__
    g_print ( "0\n");
    fprintf(stderr,"\n");
    if ( AverageBitrate > 0. )
        fprintf(stderr,"%7.1f kbps,", AverageBitrate );

    // Output total time, Streamversion, Profile
    fprintf(stderr,"%s, SV %u.%u, Profile %s%s", PrintTime (TotalFrames * (double)BLK_SIZE, ' ') + 1, StreamVersion & 15, StreamVersion >> 4, ProfileName(Profile), EncoderName(Encoder) );
    g_print ( "1\n");
#endif

    //on rËgle les infos :
    *bitrate_ret=(int)AverageBitrate;

    *time_ret=(char*)malloc(strlen(PrintTime (TotalFrames * (double)BLK_SIZE, ' ') + 1)+1);
    if (!*time_ret) return;
    strcpy(*time_ret,PrintTime (TotalFrames * (double)BLK_SIZE, ' ') + 1);
    *streamversion_ret=(char*)malloc(10);
    if (!*streamversion_ret) return;
    snprintf(*streamversion_ret,9," SV %u.%u", StreamVersion & 15, StreamVersion >> 4);
    (*streamversion_ret)[9]=0;

    *profile_ret=(char*)malloc(100);
    if (!*profile_ret) return;
    snprintf(*profile_ret,99,"%s%s", ProfileName(Profile), EncoderName(Encoder) );
    (*profile_ret)[99]=0;


}


static const char* EncoderName ( int encoderno )
{
    static char Name [32];

    if ( encoderno <= 0 )
        Name [0] = '\0';
    else if ( encoderno % 10 == 0 )
        sprintf ( Name, " (Release %u.%u)", encoderno/100, encoderno/10%10 );
    else if ( (encoderno & 1) == 0 )
        sprintf ( Name, " (Beta %u.%02u)", encoderno/100, encoderno%100 );
    else
        sprintf ( Name, " (--Alpha-- %u.%02u)", encoderno/100, encoderno%100 );
    return Name;
}


//   0: No ID3v2 tag
//  >0: ID2v2 tag with this length
static Int32_t JumpID3v2 ( void )
{
    Int32_t   ret = 10;

    if ( (Bitstream_read (32) & 0xFFFFFF) != 0x334449L )
        return 0;

    if ( Bitstream_read (1) )
        return 0;
    ret += Bitstream_read (7) << 14;
    if ( Bitstream_read (1) )
        return 0;
    ret += Bitstream_read (7) << 21;
    Bitstream_read (1);
    if ( Bitstream_read (1) )
        ret += 10;
    Bitstream_read (14);
    Bitstream_read (16);
    if ( Bitstream_read (1) )
        return 0;
    ret += Bitstream_read (7) <<  0;
    if ( Bitstream_read (1) )
        return 0;
    ret += Bitstream_read (7) <<  7;

    return ret;
}


/*
 *  Print out the time to stderr with a precision of 10 ms always using 12 characters.
 *  Time is represented by the sample count. An additional prefix character
 *  (normally ' ' or '-') is prepended before the first digit.
 */
static const char* PrintTime ( Double samples, char sign )
{
    static char  ret [16];
    Ulong        tmp  = (Ulong)( samples * 100.f / SampleFreq + 0.5 );	// unit: 1/100th second
    Uint         hour = (Uint) ( tmp / 360000       );
    Uint         min  = (Uint) ( tmp /   6000 %  60 );
    Uint         sec  = (Uint) ( tmp /    100 %  60 );
    Uint         csec = (Uint) ( tmp          % 100 );

    if      ( hour > 9 )
        sprintf ( ret,  "%c%2u:%02u", sign, hour, min );
    else if ( hour > 0 )
        sprintf ( ret, " %c%1u:%02u", sign, hour, min );
    else if ( min  > 9 )
        sprintf ( ret,    "   %c%2u", sign,       min );
    else
        sprintf ( ret,   "    %c%1u", sign,       min );

    sprintf ( ret + 6,   ":%02u.%02u", sec, csec );
    return ret;
}


static const char* ProfileName ( Uint profile )        // profile is 0...15, where 1, 5...15 is used
{
    static const char   na    [] = "n.a.";
    static const char*  Names [] = {
        na, "Unstable/Experimental", na, na,
        na, "below 'Telephone'", "below 'Telephone'", "'Telephone'",
        "'Thumb'", "'Radio'", "'Standard'", "'Xtreme'",
        "'Insane'", "'BrainDead'", "above 'BrainDead'", "above 'BrainDead'"
    };

    return profile >= sizeof(Names)/sizeof(*Names)  ?  na  :  Names [profile];
}


//fonction de decode.c
void Bitstream_init ( void )
{
    Int       i;
    Uint32_t  val;

    InputCnt     = (size_t)-1;
    pos          = BITS;
    dword        = 0;     // Werte werden so initialisiert, daﬂ beim n‰chsten Lesen von mindestens 1 bit das erste dword automatisch eingezogen wird
    LastInputCnt = 0;
    Wraps        = 0;

    for ( val = 0, i = 0; i <= 32; i++, val += val+1 )
        mask [i] = val;
}


Uint32_t Bitstream_read ( Int bits )
{
    Uint32_t  ret;


    ret = dword;
    if ( (pos += bits) < BITS ) {
        ret >>= BITS - pos;
    } else {
        pos  -= BITS;
        dword = InputBuff [InputCnt = (InputCnt+1) & IBUFMASK];
        if ( pos > 0 ) {
            ret <<= pos;
            ret  |= dword >> (BITS - pos);
        }
    }
    ret &= mask [bits];


    return ret;
}


Uint32_t Bitstream_preview ( Int bits )
{
    Uint      new_pos = pos + bits;
    Uint32_t  ret     = dword;

    if ( new_pos < BITS ) {
        ret >>= BITS - new_pos;
    } else if ( new_pos > BITS ) {
        ret <<= new_pos - BITS;
        ret  |= InputBuff [(InputCnt+1) & IBUFMASK] >> (2*BITS - new_pos);
    }
    return ret /* & mask[bits] */;
}


//de tools.c
size_t Read_LittleEndians ( FILE_T fp, Uint32_t* dst, size_t words32bit )
{
    size_t  wordsread;

    wordsread = READ ( fp, dst, words32bit * sizeof(*dst) ) / sizeof(*dst);

    /*#if ENDIAN == HAVE_BIG_ENDIAN
    Change_Endian32 ( dst, wordsread );
#endif
    */

    return wordsread;
}
