;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Thomas NAVARA (mailto:navara@shalmirane.net)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_CZECH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (vy¾adován)"
LangString DESC_SecCopyUI ${CURLANG} "Aplikace."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 knihovny (vy¾adovány)"
LangString DESC_SecCopyGTK ${CURLANG} "Knihovny pro GUI prostøedí."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Pluginy"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Pluginy pro extrakci informací ze souborù."
LangString TITLE_SecCopyLANG ${CURLANG} "Jazyky prostøedí"
LangString DESC_SecCopyLANG ${CURLANG} "V¹ecny jazykové soubory pro pøeklad."
LangString UninstBefore ${CURLANG} "You must uninstall your last version of $(^NameDA)"
LangString InstAlready ${CURLANG} "Installer already running"
LangString InstTypeFull ${CURLANG} "Plný"
LangString InstTypeCompact ${CURLANG} "Kompaktní"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Install options"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Which users can run $(^NameDA)?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) install rights access"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) can be installed for all users or only for current user. Select for which you want install $(^NameDA) please."
LangString LIST_SecAllUsersUI ${CURLANG} "All users|Current user"
LangString STATE_SecAllUsersUI ${CURLANG} "All users"


!verbose 4
