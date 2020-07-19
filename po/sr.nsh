;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_SERBIAN}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (obavezno)"
LangString DESC_SecCopyUI ${CURLANG} "Glavni deo aplikacije."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 RunTime (obavezno)"
LangString DESC_SecCopyGTK ${CURLANG} "Biblioteke za Graficki Interfejs (GUI)."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Dodaci"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Dodaci za automatsko izdvajanje opisa i dodaci za uvoz/izvoz kataloga."
LangString TITLE_SecCopyLANG ${CURLANG} "Prevodi"
LangString DESC_SecCopyLANG ${CURLANG} "Svi fajlovi za prevod programa na druge jezike."
LangString UninstBefore ${CURLANG} "Morate deinstalirati prethodnu verziju $(^NameDA)-a"
LangString InstAlready ${CURLANG} "Instaler je vec startovan"
LangString InstTypeFull ${CURLANG} "Cela instalacija"
LangString InstTypeCompact ${CURLANG} "Kompaktna instalacija"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Opcije instalacije"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Koji korisnici mogu pokretati $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) instalacija prava pristupa"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) moze biti instaliran za sve korisnike ili samo za trenutnog korisnika. Izaberite kako zelite da instalirate $(^NameDA)."
LangString LIST_SecAllUsersUI ${CURLANG} "Svi korisnici|Trenutni korisnik"
LangString STATE_SecAllUsersUI ${CURLANG} "Svi korisnici"


!verbose 4
