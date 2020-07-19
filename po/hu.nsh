;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by LAJOSHÁZI László Gergely (mailto:lajoshaz@zeus.iit.uni-miskolc.hu)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_HUNGARIAN}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (nélkülözhetetlen)"
LangString DESC_SecCopyUI ${CURLANG} "Fõbb programrészek."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.4 RunTime (nélkülözhetetlen)"
LangString DESC_SecCopyGTK ${CURLANG} "A grafikus felület megjelenítéséhez használt futtatókörnyezet."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Automatikus leírásgyûjtéshez kiegészítõk. pl. mp3 fájlok szöveges adatainak kinyeréséhez."
LangString TITLE_SecCopyLANG ${CURLANG} "További fordítások"
LangString DESC_SecCopyLANG ${CURLANG} "A használt szövegek magyar adatbázisa mellé minden más támogatott nyelvfájlt is telepít."
LangString UninstBefore ${CURLANG} "You must uninstall your last version of $(^NameDA)"
LangString InstAlready ${CURLANG} "Installer already running"
LangString InstTypeFull ${CURLANG} "Teljes"
LangString InstTypeCompact ${CURLANG} "Minimális"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.hu"
LangString TITLE_SecAllUsersUI ${CURLANG} "Install options"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Which users can run $(^NameDA)?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) install rights access"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) can be installed for all users or only for current user. Select for which you want install $(^NameDA) please."
LangString LIST_SecAllUsersUI ${CURLANG} "All users|Current user"
LangString STATE_SecAllUsersUI ${CURLANG} "All users"


!verbose 4
