;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_DUTCH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (vereist)"
LangString DESC_SecCopyUI ${CURLANG} "Hoofdprogramma."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 RunTime (vereist)"
LangString DESC_SecCopyGTK ${CURLANG} "GUI uitvoeringsprogramma."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Modules om automatisch bestandsbeschrijvingen te extraheren en voor import/export van catalogen."
LangString TITLE_SecCopyLANG ${CURLANG} "Taalbestanden"
LangString DESC_SecCopyLANG ${CURLANG} "Alle taalbestanden voor de vertaling van het programma."
LangString UninstBefore ${CURLANG} "Je moet je laatste versie van $(^NameDA) verwijderen"
LangString InstAlready ${CURLANG} "Installeren is al bezig"
LangString InstTypeFull ${CURLANG} "Volledig"
LangString InstTypeCompact ${CURLANG} "Compact"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Installatie opties"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Welke gebruiker kunnen $(^NameDA) starten ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "Installatie toegangsrechten voor $(^NameDA)"
LangString ASK_SecAllUsersUI ${CURLANG} "Je kunt $(^NameDA) installeren voor alle gebruikers of alleen voor de huidige gebruiker. Selecteer waarvoor je GWhere wil installeren."
LangString LIST_SecAllUsersUI ${CURLANG} "Alle gebruikers|Huidige gebruiker"
LangString STATE_SecAllUsersUI ${CURLANG} "Alle gebruikers"


!verbose 4
