;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_DUTCH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (vereist)"
LangString DESC_SecCopyUI ${CURLANG} "Hoofdtoepassing."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6-runtime (vereist)"
LangString DESC_SecCopyGTK ${CURLANG} "GUI-uitvoertoepassing."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plug-ins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Modules om automatisch bestandsbeschrijvingen te extraheren en voor import/export van catalogi."
LangString TITLE_SecCopyLANG ${CURLANG} "Taalbestanden"
LangString DESC_SecCopyLANG ${CURLANG} "Alle taalbestanden voor de vertaling van het programma."
LangString UninstBefore ${CURLANG} "U dient de nieuwste versie van $(^NameDA) te verwijderen"
LangString InstAlready ${CURLANG} "De installatie loopt al"
LangString InstTypeFull ${CURLANG} "Volledig"
LangString InstTypeCompact ${CURLANG} "Compact"
LangString TITLE_SecAllUsersUI ${CURLANG} "Installatie-opties"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Welke gebruikers mogen $(^NameDA) starten?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "Installatie-toegangsrechten voor $(^NameDA)"
LangString ASK_SecAllUsersUI ${CURLANG} "U kunt $(^NameDA) installeren voor alle gebruikers of alleen voor de huidige gebruiker. Geef aan voor wie u GWhere wilt installeren."
LangString LIST_SecAllUsersUI ${CURLANG} "Alle gebruikers|Huidige gebruiker"
LangString STATE_SecAllUsersUI ${CURLANG} "Alle gebruikers"


!verbose 4
