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


#include "gwicons.h"


/* XPM : New catalog */
static char *New_xpm[]={
"24 24 89 1",
" 	c None",
".	c #000000",
"+	c #ADAD9C",
"@	c #959585",
"#	c #DCDCC5",
"$	c #DFDFC8",
"%	c #242424",
"&	c #A7A796",
"*	c #D7D7C1",
"=	c #D9D9C3",
"-	c #DCDCC4",
";	c #DDDDC7",
">	c #E1E1CA",
",	c #A6A694",
"'	c #D6D6BF",
")	c #D8D8C2",
"!	c #DBDBC4",
"~	c #DFDFC7",
"{	c #E3E3CB",
"]	c #B2B29F",
"^	c #7C7C7C",
"/	c #646464",
"(	c #D5D5BD",
"_	c #D5D5BF",
":	c #D7D7C0",
"<	c #DADAC3",
"[	c #DEDEC6",
"}	c #E1E1C9",
"|	c #E5E5CD",
"1	c #E9E9D1",
"2	c #343434",
"3	c #E7E7E7",
"4	c #373736",
"5	c #B8B8A6",
"6	c #D3D3BC",
"7	c #D9D9C2",
"8	c #DDDDC5",
"9	c #E0E0C8",
"0	c #E8E8D0",
"a	c #ECECD4",
"b	c #EEEED5",
"c	c #ECECEC",
"d	c #EDEDED",
"e	c #3D3D37",
"f	c #CECEB7",
"g	c #E6E6CE",
"h	c #EAEAD2",
"i	c #F1F1D8",
"j	c #A5A594",
"k	c #EEEEE5",
"l	c #3C3C3C",
"m	c #8F8F80",
"n	c #D0D0B9",
"o	c #E4E4CB",
"p	c #EAEAD1",
"q	c #ECECD3",
"r	c #EFEFD6",
"s	c #F2F2D9",
"t	c #F3F3DA",
"u	c #EEEEE6",
"v	c #505050",
"w	c #929282",
"x	c #D1D1B9",
"y	c #E7E7CF",
"z	c #EBEBD2",
"A	c #F4F4DB",
"B	c #F5F5DC",
"C	c #969686",
"D	c #D2D2BC",
"E	c #E0E0C9",
"F	c #E9E9D0",
"G	c #EDEDD4",
"H	c #F0F0D7",
"I	c #BEBEAB",
"J	c #797973",
"K	c #D8D8C1",
"L	c #DDDDC6",
"M	c #98988F",
"N	c #E4E4CC",
"O	c #818174",
"P	c #E2E2CA",
"Q	c #BEBEAE",
"R	c #4E4E4E",
"S	c #828274",
"T	c #EBEBD3",
"U	c #BBBBA8",
"V	c #CDCDB8",
"W	c #4D4D45",
"X	c #A6A696",
"                        ",
"                        ",
"             .          ",
"           ..+.         ",
"         ..@#$%         ",
"       ..&*=-;>.        ",
"     ..,'**)!~{].       ",
"    .^/'(_:<[}|12       ",
"    .3456*789|0ab.      ",
"    .cdef_!9g0hbij.     ",
"    .kklmn9opqrist.     ",
"    .uvwx-}yzbittAB.    ",
"    ..CD!E{FGHtAABBI.   ",
"    .JK7L>ypbitBBBBB).  ",
"    .M!#$NyzbitBBBBBO.  ",
"     .~9P|1qrsABBBB..   ",
"     .Q||0hGHtABB<.     ",
"      R01hGrstAsS.      ",
"      .TaGriss<.        ",
"       .rHis1j.         ",
"       .UstVW.          ",
"        .tX.            ",
"         ..             ",
"                        "};


/* XPM : Open file */
static char *Open_xpm[]={
"24 24 5 1",
" 	c None",
".	c #000000",
"+	c #99907B",
"@	c #FFFEF7",
"#	c #FFFFFF",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"              ..        ",
"           ...++.       ",
"    ..  ...++++@@#...   ",
"   .++..++++@@@@..++.   ",
"   .+++++@@@@@..++++.   ",
"    .++@@@@@..++++++.   ",
"    .++@@@..++++++++.   ",
"     .+@@.++++++++++.   ",
"     .++@.++++++++++.   ",
"      .+@.++++++++++.   ",
"      .++.++++++++..    ",
"       .+.++++++..      ",
"       .+.+++++.        ",
"        ..+++..         ",
"        ..+..           ",
"         ..             ",
"                        ",
"                        ",
"                        "};


/* XPM : Save file */
static char *Save_xpm[]={
"24 24 64 1",
" 	c None",
".	c #000000",
"+	c #779FA8",
"@	c #495A5E",
"#	c #BFD1D5",
"$	c #A8C1C5",
"%	c #E4ECED",
"&	c #FFFFFF",
"*	c #EEF3F4",
"=	c #E0E9EB",
"-	c #87AAB2",
";	c #AEC4C9",
">	c #F5F8F9",
",	c #8BADB5",
"'	c #3E4D50",
")	c #94B2B9",
"!	c #CFDCDF",
"~	c #E4ECEE",
"{	c #788A8D",
"]	c #EBF1F2",
"^	c #E8EFF0",
"/	c #F2F6F7",
"(	c #607A7F",
"_	c #F0F4F5",
":	c #536E75",
"<	c #A0BCC1",
"[	c #465E63",
"}	c #4B575A",
"|	c #557278",
"1	c #A4ABAD",
"2	c #EAEAEA",
"3	c #E4E4E4",
"4	c #606364",
"5	c #C6CACC",
"6	c #F3F3F3",
"7	c #F1F1F1",
"8	c #E7E7E7",
"9	c #E1E1E1",
"0	c #A9B2B4",
"a	c #486166",
"b	c #34464A",
"c	c #729096",
"d	c #BCC2C3",
"e	c #F6F6F6",
"f	c #57696D",
"g	c #CFD8DA",
"h	c #DEDEDE",
"i	c #D8D8D8",
"j	c #8C9394",
"k	c #F2F2F2",
"l	c #3A474A",
"m	c #7EA4AC",
"n	c #D5DADA",
"o	c #E0E0E0",
"p	c #B4B4B4",
"q	c #657376",
"r	c #D0D5D6",
"s	c #E9E9E9",
"t	c #A7B0B2",
"u	c #D2D4D5",
"v	c #899293",
"w	c #484848",
"x	c #DDDDDD",
"y	c #8F9A9B",
"                        ",
"                        ",
"                        ",
"              ..        ",
"            ..+@.       ",
"          ..#$%+.       ",
"        ..#$#&*+@.      ",
"      ..#$#&&&&=+.      ",
"    ..-;#&&&&&&>,'.     ",
"   .);!&&&&&&&&&~+.     ",
"   .{)]&&&&&&&&&^+@.    ",
"    .$=&&&&&&&/=+++.    ",
"    .(-]&&&&_=++::+@.   ",
"     .<=&&_=++[}|+:+.   ",
"     .(-^=++[1234+:+@.  ",
"      .)++:567890a+[b.  ",
"      .c-+defg3hij+'..  ",
"       .)+:klmnopq..    ",
"       .|++rstuvw.      ",
"        .a+:xy..        ",
"         .....          ",
"                        ",
"                        ",
"                        "};


/* XPM : Close file */
static char *Close_xpm[]={
"24 24 4 1",
"a c #7f7f7f",
"b c #000000",
"  c None",
"# c #ff0000",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"               #        ",
"       ##a    ###       ",
"        ##a  #####      ",
"         #######bb      ",
"          #####b        ",
"          ####b         ",
"         ######         ",
"         ##b ###        ",
"        ##b   ###       ",
"        #b     ##a      ",
"       #b       #b      ",
"       b         b      ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        "};


/* XPM : Catalog icon */
static char * catalog_xpm [] = {
"16 16 16 1",
". c #808080",
"# c #a0a0a0",
"a c #c3c3c3",
"b c #c0c000",
"c c #00ff00",
"d c #00ffff",
"e c #000000",
"f c #c0ffc0",
"g c #ffff00",
"h c #303030",
"i c #ffffc0",
"  c None",
"k c #c0ffff",
"l c #585858",
"m c #dcdcdc",
"n c #ffffff",
" hh             ",
" heehnn...nne   ",
" hhhhndgaaane   ",
" hhhhbbbaabbe   ",
" hhhhmmkbnmme   ",
" hhhhmmn.kmme   ",
" hhhh#nmmik.e   ",
" hhhhmmmmfime   ",
" heehmm##..gaae ",
" he.e    .dgaane",
"   aae   acdanaa",
"   a .   aac aaa",
"    .    aaangaa",
"         .aaagde",
"          .aace ",
"                "};



/* XPM : file icon */
static char * file_xpm [] = {
"16 16 7 1",
"# c #000000",
"b c #ffffff",
"e c #000000",
"d c #404000",
"c c #c0c000",
"a c #ffffc0",
"  c None",
"                ",
"         #      ",
"      # #a##    ",
"     #b#bbba##  ",
"    #b#bbbabbb# ",
"   #b#bba##bb#  ",
"  #b#abb#bb##   ",
" #a#aab#bbbab## ",
"#a#aaa#bcbbbbbb#",
"#ccdc#bcbbcbbb# ",
" ##c#bcbbcabb#  ",
"   #acbacbbbe   ",
"  #aaaacaba#    ",
"   ##aaaaa#     ",
"     ##aa#      ",
"       ##       "};


/* XPM : Floppy icon */
static char * floppy_disk_xpm[]={
"16 16 7 1",
"c c #808080",
"d c #000000",
". c None",
"a c #bdbebd",
"b c #ffffff",
"e c #ff0000",
"# c #7b797b",
"................",
".........#######",
"........#abbbbb#",
"........#abbbbb#",
"........#abbbbb#",
"........#abbbba#",
"........#aa###a#",
".#cccccc#aad#db#",
"#bbbbbbb###ddd##",
"#aaaaaaaaaaea##.",
"#aaaa####aaaa##.",
"#abbbddddbbba##.",
"#aaaaaaaaaaaa#d.",
".ddddddddddddd..",
"................",
"................"};



/* XPM : Hard disk icon */
static char * harddrive_disk_xpm[]={
"16 16 6 1",
"a c #c6c6c6",
"b c #000000",
"# c #848484",
". c None",
"d c #008400",
"c c #ffffff",
"................",
"................",
"................",
"................",
"..#############.",
".#aaaaaaaaaaaa#b",
"#cccccccccccc##b",
"#aaaaaaaaaada##b",
"#aaaaaaaaaaaa##b",
"#a##########a##b",
"#acccccccccca##b",
"##############b.",
".bbbbbbbbbbbbb..",
"................",
"................",
"................"};



/* XPM : Disk icon */
static char * cdrom_disk_xpm[] =  {
"17 17 30 1",
" 	c None",
".	c #737173",
"+	c #96CB96",
"@	c #CDCA62",
"#	c #BDBABD",
"$	c #299194",
"%	c #62CA94",
"&	c #ACB2AC",
"*	c #293029",
"=	c #CDCA94",
"-	c #DEDADE",
";	c #838183",
">	c #2991CD",
",	c #6291CD",
"'	c #62CACD",
")	c #D5D2D5",
"!	c #949194",
"~	c #9C99A4",
"{	c #629194",
"]	c #000000",
"^	c #CDCACD",
"/	c #EEEAEE",
"(	c #DEE2DE",
"_	c #E6EAE6",
":	c #FFFAFF",
"<	c #E6E6E6",
"[	c #CDFAFF",
"}	c #0091CD",
"|	c #00FA00",
"1	c #007900",
"                 ",
"         ...     ",
"       ..+@#..   ",
"      .$%+@&##*  ",
"     .%%$%=#&-&* ",
"     ;>,%';&)#&* ",
"    .!~{';];~&^^*",
"    .&&^;]/];^^^*",
"    .(/(&;];&_/^*",
"  ;;;;~&~~;$-(:* ",
" ;<<<.~~&)=%>[&* ",
" ;<###.~&^=+}}]  ",
" ;<****;;^=+**]  ",
" ;<|1<<##***#.]  ",
" .;;;;;;;;;;;;]  ",
"  ]]]]]]]]]]]]   ",
"                 "};



/* XPM : ZIP icon */
static char *zip_disk_xpm[] = {
"16 16 24 1",
"  c none",
"# c #040404",
"a c #a0a0a4",
"b c #868686",
"c c #ffffff",
"d c #b2b2b2",
"e c #d7d7d7",
"f c #666666",
"g c #333333",
"h c #1c1c1c",
"i c #4d4d4d",
"j c #0000cc",
"k c #3333cc",
"l c #0099cc",
"m c #0066ff",
"n c #3333ff",
"o c #0000ff",
"p c #ccffff",
"q c #99ffff",
"r c #00ff00",
"s c #ff9900",
"t c #3366cc",
"u c #0099ff",
"v c #0066cc",
"     ########## ",
"    ##bagceddg##",
"    dgaaeggggggf",
"    dibbbbbbbbif",
"    di########if",
"    diccccccccif",
"    diccccccccif",
"    diccccccccif",
"    diccccccccif",
"    diccccccccif",
"  llmmnnnnoooojf",
" lmnnnnoooooojj#",
"kmmmmmmmmmnnnjjh",
"kmoooooooommmjjh",
"kmmmuuuvmmmfmji ",
" ############i  "
};



/* XPM : Folder icon */
static char * folder_xpm[] = {
"16 16 8 1",
" 	c None",
".	c #909000",
"+	c #000000",
"@	c #EFE8EF",
"#	c #FFF8CF",
"$	c #FFF890",
"%	c #CFC860",
"&	c #FFC890",
"                ",
"  .....+        ",
" .@##$$.+       ",
".%%%%%%%......  ",
".###########$%+ ",
".#$$$$$$$$$$&%+ ",
".#$$$$$$$&$&$%+ ",
".#$$$$$$$$&$&%+ ",
".#$$$$$&$&$&$%+ ",
".#$$$$$$&$&$&%+ ",
".#$$$&$&$&$&&%+ ",
".#&$&$&$&$&&&%+ ",
".%%%%%%%%%%%%%+ ",
" ++++++++++++++ ",
"                ",
"                "};


/* XPM : Parent folder icon */
static char * parent_folder_xpm[] = {
"16 16 8 1",
" 	c None",
".	c #909000",
"+	c #000000",
"@	c #EFE8EF",
"#	c #FFF8CF",
"$	c #FFF890",
"%	c #CFC860",
"&	c #FFC890",
"                ",
"  .....+        ",
" .@##$$.+       ",
".%%%%%%%......  ",
".###########$%+ ",
".#$$$$$$$$$$&%+ ",
".#$$$+$$$&$&$%+ ",
".#$$+++$$$&$&%+ ",
".#$$$+$.$&$&$%+ ",
".#$$$+$$&$&$&%+ ",
".#$$$++++++&&%+ ",
".#&$&$&$&$&&&%+ ",
".%%%%%%%%%%%%%+ ",
" ++++++++++++++ ",
"                ",
"                "};


/* XPM : Open folder icon */
static char * open_folder_xpm[] = {
"16 16 12 1",
" 	c None",
".	c #808080",
"+	c #E0E0D0",
"@	c #4F484F",
"#	c #909000",
"$	c #FFF8EF",
"%	c #CFC860",
"&	c #003090",
"*	c #7F7800",
"=	c #FFC890",
"-	c #FFF890",
";	c #2F3000",
"        .       ",
"       .+@      ",
"   ###.$$+@     ",
"  #%%.$$$$+@    ",
"  #%.$$$&$$+@** ",
"  #.+++&+&+++@* ",
"############++@ ",
"#$$$$$$$$$=%#++@",
"#$-------=-=#+; ",
" #---=--=-==%#; ",
" #-----=-=-==#; ",
" #-=--=-=-=-=#; ",
"  #=-=-=-=-==#; ",
"  ############; ",
"   ;;;;;;;;;;;  ",
"                "};


/* XPM : Locked folder icon */
static char * locked_folder_xpm[]={
"16 16 20 1",
"q c #808080",
"o c #c3c3c3",
"j c #d6d384",
"m c #a5a263",
"a c #cecbb5",
"n c #efeb42",
"c c #c05800",
"g c #efefd6",
"f c #efefe7",
"p c #000000",
"# c #400000",
"h c #303030",
"r c #efef29",
"b c #a5a694",
"e c #ffffc0",
"i c #efeb4a",
". c None",
"l c #dedb73",
"k c #dedf42",
"d c #ffffff",
"................",
"......###.......",
"aaaaaa###aaaaa..",
"bbbbbbcccbbbbba.",
"bdefefcccggggbh.",
"bdijklccclklkmh.",
"bdjnjopppqlklbh.",
"bdnjnooooqklkmh.",
"bdarjoqpqqlklbh.",
"bdrjroqoqqklkmh.",
"bdarjqpopplklbh.",
"bfraracc#jkjkmh.",
"mmmmmmcccmmmmmh.",
".pppppcccpppppp.",
"......###.......",
"................"};


	
gint icons_load_catalog ( GtkWindow *w)
{
	GdkColor transparent = { 0 };


	if ( w != NULL )
	{
		PixCDRomDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskCDRomDisk, &transparent, cdrom_disk_xpm);
		PixFloppyDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFloppyDisk, &transparent, floppy_disk_xpm);
		PixHardDriveDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskHardDriveDisk, &transparent, harddrive_disk_xpm);
		PixZipDisk = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskZipDisk, &transparent, zip_disk_xpm);
		PixFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFolder, &transparent, folder_xpm);
		PixParentFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskParentFolder, &transparent, parent_folder_xpm);
		PixLockedFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskLockedFolder, &transparent, locked_folder_xpm);
		PixOpenFolder = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskOpenFolder, &transparent, open_folder_xpm);
		PixFile = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskFile, &transparent, file_xpm);
		PixCatalog = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskCatalog, &transparent, catalog_xpm);

		return 0;
	}

	return -1;
}


gint icons_load_toolbar ( GtkWindow *w)
{
	GdkColor transparent = { 0 };


	if ( w != NULL )
	{
		PixNew = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskNew, &transparent, New_xpm);
		PixOpen = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskOpen, &transparent, Open_xpm);
		PixSave = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskSave, &transparent, Save_xpm);
		PixClose = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( w)->window, &MskClose, &transparent, Close_xpm);
		return 0;
	}

	return -1;
}
