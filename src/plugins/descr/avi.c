/*  GWhere.
 *  Copyright (C) 2003 by Sébastien LECACHEUR
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


/* WAVE form IDs */
#define WAVE_FORMAT_UNKNOWN					0x0000 /* Microsoft Corporation */
#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM						0x0001 /* PCM -> "PCM" */
#endif
#define WAVE_FORMAT_ADPCM					0x0002 /* Microsoft Corporation -> "MS ADPCM" */
#define WAVE_FORMAT_IEEE_FLOAT				0x0003 /* Microsoft Corporation */
#define WAVE_FORMAT_VSELP					0x0004 /* Compaq Computer Corp. -> "Ima-0ADPCM VSELP" */
#define WAVE_FORMAT_IBM_CVSD				0x0005 /* IBM Corporation */
#define WAVE_FORMAT_ALAW					0x0006 /* Microsoft Corporation -> "A-Law" */
#define WAVE_FORMAT_MULAW					0x0007 /* Microsoft Corporation  -> "u-Law" */
#define WAVE_FORMAT_DTS						0x0008 /* Microsoft Corporation */
#define WAVE_FORMAT_OKI_ADPCM				0x0010 /* OKI */
#define WAVE_FORMAT_DVI_ADPCM				0x0011 /* Intel Corporation -> "IMA ADPCM" */
#define WAVE_FORMAT_IMA_ADPCM				(WAVE_FORMAT_DVI_ADPCM) /*  Intel Corporation */
#define WAVE_FORMAT_MEDIASPACE_ADPCM		0x0012 /* Videologic */
#define WAVE_FORMAT_SIERRA_ADPCM			0x0013 /* Sierra Semiconductor Corp */
#define WAVE_FORMAT_G723_ADPCM 				0x0014 /* Antex Electronics Corporation */
#define WAVE_FORMAT_DIGISTD					0x0015 /* DSP Solutions, Inc. */
#define WAVE_FORMAT_DIGIFIX					0x0016 /* DSP Solutions, Inc. */
#define WAVE_FORMAT_DIALOGIC_OKI_ADPCM 		0x0017 /* Dialogic Corporation */
#define WAVE_FORMAT_MEDIAVISION_ADPCM		0x0018 /* Media Vision, Inc. */
#define WAVE_FORMAT_CU_CODEC				0x0019 /* Hewlett-Packard Company */
#define WAVE_FORMAT_YAMAHA_ADPCM			0x0020 /* Yamaha Corporation of America */
#define WAVE_FORMAT_SONARC					0x0021 /* Speech Compression */
#define WAVE_FORMAT_DSPGROUP_TRUESPEECH		0x0022 /* DSP Group, Inc */
#define WAVE_FORMAT_ECHOSC1					0x0023 /* Echo Speech Corporation */
#define WAVE_FORMAT_AUDIOFILE_AF36			0x0024 /* Virtual Music, Inc. */
#define WAVE_FORMAT_APTX					0x0025 /* Audio Processing Technology */
#define WAVE_FORMAT_AUDIOFILE_AF10			0x0026 /* Virtual Music, Inc. */
#define WAVE_FORMAT_PROSODY_1612			0x0027 /* Aculab plc */
#define WAVE_FORMAT_LRC						0x0028 /* Merging Technologies S.A. */
#define WAVE_FORMAT_DOLBY_AC2				0x0030 /* Dolby Laboratories */
#define WAVE_FORMAT_GSM610					0x0031 /* Microsoft Corporation -> "MS GSM 6.10" */
#define WAVE_FORMAT_MSNAUDIO				0x0032 /* Microsoft Corporation -> "MSN Audio" */
#define WAVE_FORMAT_ANTEX_ADPCME			0x0033 /* Antex Electronics Corporation */
#define WAVE_FORMAT_CONTROL_RES_VQLPC		0x0034 /* Control Resources Limited */
#define WAVE_FORMAT_DIGIREAL				0x0035 /* DSP Solutions, Inc. */
#define WAVE_FORMAT_DIGIADPCM				0x0036 /* DSP Solutions, Inc. */
#define WAVE_FORMAT_CONTROL_RES_CR10		0x0037 /* Control Resources Limited */
#define WAVE_FORMAT_NMS_VBXADPCM			0x0038 /* Natural MicroSystems */
#define WAVE_FORMAT_CS_IMAADPCM				0x0039 /* Crystal Semiconductor IMA ADPCM */
#define WAVE_FORMAT_ECHOSC3					0x003A /* Echo Speech Corporation */
#define WAVE_FORMAT_ROCKWELL_ADPCM			0x003B /* Rockwell International */
#define WAVE_FORMAT_ROCKWELL_DIGITALK		0x003C /* Rockwell International */
#define WAVE_FORMAT_XEBEC					0x003D /* Xebec Multimedia Solutions Limited */
#define WAVE_FORMAT_G721_ADPCM 				0x0040 /* Antex Electronics Corporation */
#define WAVE_FORMAT_G728_CELP				0x0041 /* Antex Electronics Corporation */
#define WAVE_FORMAT_MSG723					0x0042 /* Microsoft Corporation */
#define WAVE_FORMAT_MPEG					0x0050 /* Microsoft Corporation -> "MPEG Layer-1/2" */
#define WAVE_FORMAT_RT24					0x0052 /* InSoft, Inc. */
#define WAVE_FORMAT_PAC						0x0053 /* InSoft, Inc. */
#define WAVE_FORMAT_MPEGLAYER3 				0x0055 /* ISO/MPEG Layer3 Format Tag -> "MPEG Layer-3" */
#define WAVE_FORMAT_LUCENT_G723				0x0059 /* Lucent Technologies */
#define WAVE_FORMAT_CIRRUS					0x0060 /* Cirrus Logic */
#define WAVE_FORMAT_ESPCM					0x0061 /* ESS Technology */
#define WAVE_FORMAT_VOXWARE					0x0062 /* Voxware Inc */
#define WAVE_FORMAT_CANOPUS_ATRAC			0x0063 /* Canopus, co., Ltd. */
#define WAVE_FORMAT_G726_ADPCM 				0x0064 /* APICOM */
#define WAVE_FORMAT_G722_ADPCM 				0x0065 /* APICOM */
#define WAVE_FORMAT_DSAT_DISPLAY			0x0067 /* Microsoft Corporation */
#define WAVE_FORMAT_VOXWARE_BYTE_ALIGNED	0x0069 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_AC8				0x0070 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_AC10			0x0071 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_AC16			0x0072 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_AC20			0x0073 /* Voxware Inc */
#define WAVE_FORMAT_VOXWARE_RT24			0x0074 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_RT29			0x0075 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_RT29HW			0x0076 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_VR12			0x0077 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_VR18			0x0078 /* Voxware Inc -> "Voxware Metasound" */
#define WAVE_FORMAT_VOXWARE_TQ40			0x0079 /* Voxware Inc */
#define WAVE_FORMAT_SOFTSOUND				0x0080 /* Softsound, Ltd. */
#define WAVE_FORMAT_VOXWARE_TQ60			0x0081 /* Voxware Inc */
#define WAVE_FORMAT_MSRT24					0x0082 /* Microsoft Corporation */
#define WAVE_FORMAT_G729A					0x0083 /* AT&T Labs, Inc. */
#define WAVE_FORMAT_MVI_MVI2				0x0084 /* Motion Pixels */
#define WAVE_FORMAT_DF_G726					0x0085 /* DataFusion Systems (Pty) (Ltd) */
#define WAVE_FORMAT_DF_GSM610				0x0086 /* DataFusion Systems (Pty) (Ltd) */
#define WAVE_FORMAT_ISIAUDIO				0x0088 /* Iterated Systems, Inc. */
#define WAVE_FORMAT_ONLIVE					0x0089 /* OnLive! Technologies, Inc. */
#define WAVE_FORMAT_SBC24					0x0091 /* Siemens Business Communications Sys */
#define WAVE_FORMAT_DOLBY_AC3_SPDIF			0x0092 /* Sonic Foundry */
#define WAVE_FORMAT_MEDIASONIC_G723			0x0093 /* MediaSonic */
#define WAVE_FORMAT_PROSODY_8KBPS			0x0094 /* Aculab plc */
#define WAVE_FORMAT_ZYXEL_ADPCM				0x0097 /* ZyXEL Communications, Inc. */
#define WAVE_FORMAT_PHILIPS_LPCBB			0x0098 /* Philips Speech Processing */
#define WAVE_FORMAT_PACKED					0x0099 /* Studer Professional Audio AG */
#define WAVE_FORMAT_MALDEN_PHONYTALK		0x00A0 /* Malden Electronics Ltd. */
#define WAVE_FORMAT_RHETOREX_ADPCM			0x0100 /* Rhetorex Inc. */
#define WAVE_FORMAT_IRAT					0x0101 /* BeCubed Software Inc. */
#define WAVE_FORMAT_VIVO_G723				0x0111 /* Vivo Software */
#define WAVE_FORMAT_VIVO_SIREN 				0x0112 /* Vivo Software */
#define WAVE_FORMAT_DIGITAL_G723			0x0123 /* Digital Equipment Corporation */
#define WAVE_FORMAT_SANYO_LD_ADPCM			0x0125 /* Sanyo Electric Co., Ltd. */
#define WAVE_FORMAT_SIPROLAB_ACEPLNET		0x0130 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_SIPROLAB_ACELP4800 		0x0131 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_SIPROLAB_ACELP8V3		0x0132 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_SIPROLAB_G729			0x0133 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_SIPROLAB_G729A			0x0134 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_SIPROLAB_KELVIN			0x0135 /* Sipro Lab Telecom Inc. -> "ACELP.net" */
#define WAVE_FORMAT_G726ADPCM				0x0140 /* Dictaphone Corporation */
#define WAVE_FORMAT_QUALCOMM_PUREVOICE 		0x0150 /* Qualcomm, Inc. */
#define WAVE_FORMAT_QUALCOMM_HALFRATE		0x0151 /* Qualcomm, Inc. */
#define WAVE_FORMAT_TUBGSM					0x0155 /* Ring Zero Systems, Inc. */
#define WAVE_FORMAT_MSAUDIO1				0x0160 /* Microsoft Corporation -> "DivX WMA" */
#define WAVE_FORMAT_DIVXWMA					0x0161 /* -> "DivX WMA" */
#define WAVE_FORMAT_CREATIVE_ADPCM			0x0200 /* Creative Labs, Inc */
#define WAVE_FORMAT_CREATIVE_FASTSPEECH8	0x0202 /* Creative Labs, Inc */
#define WAVE_FORMAT_CREATIVE_FASTSPEECH10	0x0203 /* Creative Labs, Inc */
#define WAVE_FORMAT_UHER_ADPCM 				0x0210 /* UHER informatic GmbH */
#define WAVE_FORMAT_QUARTERDECK				0x0220 /* Quarterdeck Corporation */
#define WAVE_FORMAT_ILINK_VC				0x0230 /* I-link Worldwide */
#define WAVE_FORMAT_RAW_SPORT				0x0240 /* Aureal Semiconductor */
#define WAVE_FORMAT_IPI_HSX					0x0250 /* Interactive Products, Inc. */
#define WAVE_FORMAT_IPI_RPELP				0x0251 /* Interactive Products, Inc. */
#define WAVE_FORMAT_CS2						0x0260 /* Consistent Software */
#define WAVE_FORMAT_SONY_SCX				0x0270 /* Sony Corp. */
#define WAVE_FORMAT_FM_TOWNS_SND			0x0300 /* Fujitsu Corp. */
#define WAVE_FORMAT_BTV_DIGITAL				0x0400 /* Brooktree Corporation */
#define WAVE_FORMAT_INTEL_MUSIC_CODER		0x0401 /* -> "Intel Music Coder" */
#define WAVE_FORMAT_QDESIGN_MUSIC			0x0450 /* QDesign Corporation */
#define WAVE_FORMAT_VME_VMPCM				0x0680 /* AT&T Labs, Inc. */
#define WAVE_FORMAT_TPC						0x0681 /* AT&T Labs, Inc. */
#define WAVE_FORMAT_OLIGSM					0x1000 /* Ing C. Olivetti & C., S.p.A. */
#define WAVE_FORMAT_OLIADPCM				0x1001 /* Ing C. Olivetti & C., S.p.A. */
#define WAVE_FORMAT_OLICELP					0x1002 /* Ing C. Olivetti & C., S.p.A. */
#define WAVE_FORMAT_OLISBC					0x1003 /* Ing C. Olivetti & C., S.p.A. */
#define WAVE_FORMAT_OLIOPR					0x1004 /* Ing C. Olivetti & C., S.p.A. */
#define WAVE_FORMAT_LH_CODEC				0x1100 /* Lernout & Hauspie */
#define WAVE_FORMAT_NORRIS					0x1400 /* Norris Communications, Inc. */
#define WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS	0x1500 /* AT&T Labs, Inc. */
#define WAVE_FORMAT_DVM						0x2000 /* FAST Multimedia AG -> "AC3 DVM" */
#ifndef WAVE_FORMAT_EXTENSIBLE
#define WAVE_FORMAT_EXTENSIBLE 				0xFFFE /* Microsoft -> "Extended Wave header" */
#endif
#define WAVE_FORMAT_DEVELOPMENT 			0xFFFF /* the WAVE_FORMAT_DEVELOPMENT format tag can be used during the development phase of a new wave format.  Before shipping, you MUST acquire an official format tag from Microsoft. */


struct main_avi_header {
	int micro_sec_per_frame;
	int max_bytes_per_sec;
	int reserved1;
	int flag;
	int frames;
	int initiale_frames;
	int streams;
	int suggested_buffer_size;
	int xres;
	int yres;
	int scale;
	int rate;
	int start;
	int length;
};

struct  avi_stream_header {
    char codec[4];
    int flags;
    int reserved1;
    int initial_frames;
    int scale;
    int rate;
    int start;
    int length;
    int suggested_buffer_size;
    int quality;
    int sample_size;
};

struct avi_stream_header_extended {
	char flux[16];
	char divx_tag[4];
};


struct avi_tag_list {
	char strl[4];
	char strh[4];
	int length_strh;
	char type[4]; /* vids=video auds=audio */
};


struct avi_audio_header {
	struct avi_tag_list tag;
	struct avi_stream_header avi_audio_header;
};

struct avi_audio_header_extended {
	char flux[7];
	short wav_tag;
};


struct avi_list_header {
	char id[4]; /* RIFF */
	char f0[4];
	char avi_list[8]; /* AVI LIST */
};


struct avi_video_1 {
	struct avi_list_header avi_list;
	char f1[4];
	char hdrl[4];
	char avih[4];
	int length; /* length of main_avi_header, should be equal to 0x38 */
	struct main_avi_header header;
	char list_1[4];
	int length_list_1; /* length of first stream LIST */
	struct avi_tag_list tag;
	struct avi_stream_header avi_video_header;
};

struct avi_video_2 {
	char list_2[4]; /* JUNK, strd, LIST */
	int length_list_2;
	struct avi_audio_header avi_audio_header;
	struct avi_audio_header_extended avi_audio_header_ext;
};

struct avi_audio {
	char f1[128];
	int rate;
};


struct avi {
	struct avi_video_1 video;
	struct avi_stream_header_extended avi_video_ext;
	struct avi_video_2 audio;
};



char * g_module_check_init ( void)
{
#ifdef __DEBUG__
	printf ( "AVI module is loading...\n");
#endif

	return NULL;
}


const char * plugin_get_author ( void)
{
	return "Sébastien LECACHEUR";
}


const char * plugin_get_info ( void)
{
	return "This plugin allow to extract title from AVI file.";
}


const char * plugin_get_version ( void)
{
	return "1.0.0";
}


const char * plugin_get_help ( void)
{
	return NULL;
}


const char * plugin_get_allowed_ext ( void)
{
	return "avi";
}


char * plugin_get_file_descr ( const char *filepath, const char *mode)
{
	char *descr = NULL;
	FILE *file = NULL;
	char codec_video_name[21];
	char codec_audio_name[21];
	char codec_tag1[5];
	char codec_tag2[5];
	struct avi a;
	char *ret = NULL;


	if ( filepath != NULL )
	{
		if ( (file = fopen ( filepath, "rb")) != NULL ) {
			fseek(file,0,SEEK_SET);
			fread(&(a.video),sizeof(a.video),1,file);

			if ( (strncmp ( "RIFF", a.video.avi_list.id, 4) == 0) && (strncmp ( "AVI LIST", a.video.avi_list.avi_list, 8) == 0) ) {
				fseek(file,a.video.tag.length_strh-(sizeof(struct avi_stream_header)+4),SEEK_CUR);
				fread(&(a.video.tag.strh),sizeof(char)*4,1,file);
				fread(&(a.video.tag.length_strh),sizeof(int),1,file);
				fread(&(a.avi_video_ext),sizeof(struct avi_stream_header_extended),1,file);
				fseek(file,a.video.tag.length_strh-sizeof(struct avi_stream_header_extended),SEEK_CUR);
				fread(&(a.audio.list_2),sizeof(a.audio.list_2),1,file);

				ret = (char*) malloc(1024);
				if((a.video.header.frames<=0)||(a.video.header.xres<=0)||(a.video.header.yres<=0)) {
					sprintf ( ret, "Unrecognised AVI format");
				} else {
					strncpy ( codec_tag1, a.video.avi_video_header.codec, 4);
					codec_tag1[4] = '\0';
					strncpy ( codec_tag2, a.avi_video_ext.divx_tag, 4);
					codec_tag2[4] = '\0';
					g_strdown ( codec_tag1);
					g_strdown ( codec_tag2);

					if ( a.video.header.streams >= 2 ) {
						while ( ((a.audio.list_2[0] != 'L') || (a.audio.list_2[1] != 'I') || (a.audio.list_2[2] != 'S') || (a.audio.list_2[3] != 'T')) && (!feof ( file)) ) {
							a.audio.list_2[0] = a.audio.list_2[1];
							a.audio.list_2[1] = a.audio.list_2[2];
							a.audio.list_2[2] = a.audio.list_2[3];
							fread(&(a.audio.list_2[3]),sizeof(a.audio.list_2[3]),1,file);
						}

						if ( (a.audio.list_2[0] == 'L') && (a.audio.list_2[1] == 'I') && (a.audio.list_2[2] == 'S') && (a.audio.list_2[3] == 'T') && (!feof ( file)) ) {
							fread(&(a.audio.length_list_2),sizeof(a.audio.length_list_2),1,file);
							fread(&(a.audio.avi_audio_header),sizeof(struct avi_audio_header),1,file);

							fseek(file,a.audio.avi_audio_header.tag.length_strh-(sizeof(struct avi_audio_header)-12),SEEK_CUR);
							fread(&(a.audio.avi_audio_header_ext),sizeof(struct avi_audio_header_extended),1,file);

							switch ( a.audio.avi_audio_header_ext.wav_tag ) {
								case WAVE_FORMAT_PCM :					strncpy ( codec_audio_name, "PCM", 3);
																		codec_audio_name[3] = '\0';
																		break;

								case WAVE_FORMAT_ADPCM :				strncpy ( codec_audio_name, "MS ADPCM", 8);
																		codec_audio_name[8] = '\0';
																		break;

								case WAVE_FORMAT_VSELP :				strncpy ( codec_audio_name, "Ima-0ADPCM VSELP", 16);
																		codec_audio_name[16] = '\0';
																		break;

								case WAVE_FORMAT_ALAW :					strncpy ( codec_audio_name, "A-Law", 5);
																		codec_audio_name[5] = '\0';
																		break;

								case WAVE_FORMAT_MULAW :				strncpy ( codec_audio_name, "u-Law", 5);
																		codec_audio_name[5] = '\0';
																		break;

								case WAVE_FORMAT_DVI_ADPCM :			strncpy ( codec_audio_name, "IMA ADPCM", 9);
																		codec_audio_name[9] = '\0';
																		break;

								case WAVE_FORMAT_GSM610 :				strncpy ( codec_audio_name, "MS GSM 6.10", 11);
																		codec_audio_name[11] = '\0';
																		break;

								case WAVE_FORMAT_MSNAUDIO :				strncpy ( codec_audio_name, "MSN Audio", 9);
																		codec_audio_name[9] = '\0';
																		break;

								case WAVE_FORMAT_MPEG :					strncpy ( codec_audio_name, "MPEG Layer-1/2", 14);
																		codec_audio_name[14] = '\0';
																		break;

								case WAVE_FORMAT_MPEGLAYER3 :			strncpy ( codec_audio_name, "MPEG Layer-3", 12);
																		codec_audio_name[12] = '\0';
																		break;

								case WAVE_FORMAT_VOXWARE_BYTE_ALIGNED :
								case WAVE_FORMAT_VOXWARE_AC8 :
								case WAVE_FORMAT_VOXWARE_AC10 :
								case WAVE_FORMAT_VOXWARE_AC16 :
								case WAVE_FORMAT_VOXWARE_RT24 :
								case WAVE_FORMAT_VOXWARE_RT29HW :
								case WAVE_FORMAT_VOXWARE_VR12 :
								case WAVE_FORMAT_VOXWARE_VR18 :
								case WAVE_FORMAT_VOXWARE_RT29 :			strncpy ( codec_audio_name, "Voxware Metasound", 17);
																		codec_audio_name[17] = '\0';
																		break;

								case WAVE_FORMAT_SIPROLAB_ACELP4800 :
								case WAVE_FORMAT_SIPROLAB_ACELP8V3 :
								case WAVE_FORMAT_SIPROLAB_G729 :
								case WAVE_FORMAT_SIPROLAB_G729A :
								case WAVE_FORMAT_SIPROLAB_KELVIN :
								case WAVE_FORMAT_SIPROLAB_ACEPLNET :	strncpy ( codec_audio_name, "ACELP.net", 9);
																		codec_audio_name[9] = '\0';
																		break;

								case WAVE_FORMAT_MSAUDIO1 :
								case WAVE_FORMAT_DIVXWMA :				strncpy ( codec_audio_name, "DivX WMA", 8);
																		codec_audio_name[8] = '\0';
																		break;

								case WAVE_FORMAT_INTEL_MUSIC_CODER :	strncpy ( codec_audio_name, "Intel Music Coder", 17);
																		codec_audio_name[17] = '\0';
																		break;

								case WAVE_FORMAT_DVM :					strncpy ( codec_audio_name, "AC3 DVM", 7);
																		codec_audio_name[7] = '\0';
																		break;

								case WAVE_FORMAT_EXTENSIBLE :			strncpy ( codec_audio_name, "Extended Wave header", 20);
																		codec_audio_name[20] = '\0';
																		break;

								default :								strncpy ( codec_audio_name, "unknown audio codec", 19);
																		codec_audio_name[19] = '\0';
																		break;
							}
						}
					} else {
						strncpy ( codec_audio_name, "no audio", 8);
						codec_audio_name[8] = '\0';
					}

					if ( a.video.header.streams >= 1 ) {
						if ( (strcmp(codec_tag1,"div3") == 0) && (strcmp(codec_tag2,"div3") == 0) ) {
							strncpy ( codec_video_name, "DivX 3 Low-Motion", 17);
							codec_video_name[17] = '\0';
						} else if ( (strcmp(codec_tag1,"div4") == 0) && (strcmp(codec_tag2,"div3") == 0) ) {
							strncpy ( codec_video_name, "DivX 3 Fast-Motion", 18);
							codec_video_name[18] = '\0';
						} else if ( ((strcmp(codec_tag1,"xvid") == 0) || (strcmp(codec_tag1,"divx") == 0)) && (strcmp(codec_tag2,"divx") == 0) ) {
							strncpy ( codec_video_name, "DivX 4 (OpenDivX)", 17);
							codec_video_name[17] = '\0';
						} else if ( (strcmp(codec_tag1,"divx") == 0) && (strcmp(codec_tag2,"dx50") == 0) ) {
							strncpy ( codec_video_name, "DivX 5.0", 8);
							codec_video_name[8] = '\0';
						} else if ( (strcmp(codec_tag1,"xvid") == 0) && (strcmp(codec_tag2,"xvid") == 0) ) {
							strncpy ( codec_video_name, "XviD", 4);
							codec_video_name[4] = '\0';
						} else if ( (strcmp(codec_tag1,"iv31") == 0) && (strcmp(codec_tag2,"iv31") == 0) ) {
							strncpy ( codec_video_name, "Indeo Interactive", 17);
							codec_video_name[17] = '\0';
						} else if ( (strcmp(codec_tag1,"iv32") == 0) && (strcmp(codec_tag2,"iv32") == 0) ) {
							strncpy ( codec_video_name, "Indeo Interactive", 17);
							codec_video_name[17] = '\0';
						} else if ( (strcmp(codec_tag1,"iv41") == 0) && (strcmp(codec_tag2,"iv41") == 0) ) {
							strncpy ( codec_video_name, "Indeo Interactive", 17);
							codec_video_name[17] = '\0';
						} else if ( (strcmp(codec_tag1,"iv50") == 0) && (strcmp(codec_tag2,"iv50") == 0) ) {
							strncpy ( codec_video_name, "Indeo Interactive", 17);
							codec_video_name[17] = '\0';
						} else if ( strcmp(codec_tag1,"rle ") == 0 ) {
							strncpy ( codec_video_name, "RLE", 3);
							codec_video_name[3] = '\0';
						} else {
							strncpy ( codec_video_name, "Unknown video codec", 19);
							codec_video_name[19] = '\0';
						}
					} else {
						strncpy ( codec_video_name, "No video", 8);
						codec_video_name[8] = '\0';
					}

					sprintf ( ret, "%s (%d x %d), %s", codec_video_name, a.video.header.xres, a.video.header.yres, codec_audio_name);
				}
			}

			descr = ret;

			fclose ( file);
		}
	}

	return descr;
}


void g_module_unload ( void)
{
#ifdef __DEBUG__
	printf ( "AVI module is unloading...\n");
#endif
}
