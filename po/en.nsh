;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_ENGLISH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (requiered)"
LangString DESC_SecCopyUI ${CURLANG} "Main engine application."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 RunTime (required)"
LangString DESC_SecCopyGTK ${CURLANG} "RunTime for GUI environment."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Plugins for auto extraction of file descriptions and plugins for importation/exportation of catalogs."
LangString TITLE_SecCopyLANG ${CURLANG} "Languages Files"
LangString DESC_SecCopyLANG ${CURLANG} "All languages files for the program translation."
LangString UninstBefore ${CURLANG} "You must uninstall your last version of $(^NameDA)"
LangString InstAlready ${CURLANG} "Installer already running"
LangString InstTypeFull ${CURLANG} "Full"
LangString InstTypeCompact ${CURLANG} "Compact"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Install options"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Which users can run $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) install rights access"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) can be installed for all users or only for current user. Select for which you want install $(^NameDA) please."
LangString LIST_SecAllUsersUI ${CURLANG} "All users|Current user"
LangString STATE_SecAllUsersUI ${CURLANG} "All users"


!verbose 4
