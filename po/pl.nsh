;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Bogdan MODZELEWSKI (mailto:motzel@panda.bg.univ.gda.pl)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_POLISH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (wymagany)"
LangString DESC_SecCopyUI ${CURLANG} "G³ówne pliki aplikacji."
LangString TITLE_SecCopyGTK ${CURLANG} "Biblioteki uruchomieniowe GTK+ 2.6 (wymagane)"
LangString DESC_SecCopyGTK ${CURLANG} "Biblioteki dla œrodowiska GUI."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Wtyczki"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Wtyczki do automatycznego tworzenia opisów plików i importu/eksportu katalogów."
LangString TITLE_SecCopyLANG ${CURLANG} "Pliki Jêzykowe"
LangString DESC_SecCopyLANG ${CURLANG} "Wszystkie pliki jêzykowe."
LangString UninstBefore ${CURLANG} "Proszê odinstalowaæ wczeœniejsz¹ wersjê $(^NameDA)"
LangString InstAlready ${CURLANG} "Program instalacyjny jest ju¿ uruchomiony"
LangString InstTypeFull ${CURLANG} "Pe³na"
LangString InstTypeCompact ${CURLANG} "Minimalna"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.pl"
LangString TITLE_SecAllUsersUI ${CURLANG} "Opcje instalacji"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Którzy u¿ytkownicy mog¹ uruchamiaæ $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) instaluje prawa dostêpu"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) mo¿e byæ zainstalowany dla wszystkich u¿ytkowników lub tylko dla bie¿¹cego. Proszê wybraæ sposób instalacji $(^NameDA)."
LangString LIST_SecAllUsersUI ${CURLANG} "Wszyscy u¿ytkownicy|Bie¿¹cy u¿ytkownik"
LangString STATE_SecAllUsersUI ${CURLANG} "Wszyscy u¿ytkownicy"


!verbose 4
