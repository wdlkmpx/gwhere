;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Hermann-Josef BECKERS (mailto:hj.beckers@onelinehome.de)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_GERMAN}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (erforderlich)"
LangString DESC_SecCopyUI ${CURLANG} "Hauptanwendung."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 Laufzeit-Umgebung (erforderlich)"
LangString DESC_SecCopyGTK ${CURLANG} "Laufzeit-Umgebung für die grafische Oberfläche."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Erweiterungen"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Erweiterungen für autom. Extraktion der Dateibeschreibungen und Erweiterungen für Katalog-Import/Export."
LangString TITLE_SecCopyLANG ${CURLANG} "Sprachdateien"
LangString DESC_SecCopyLANG ${CURLANG} "Alle Sprachdateien für die Programm-Übersetzung."
LangString UninstBefore ${CURLANG} "Sie müssen die vorherige Version von $(^NameDA) deinstallieren."
LangString InstAlready ${CURLANG} "Installationsprogramm bereits aktiv"
LangString InstTypeFull ${CURLANG} "Voll"
LangString InstTypeCompact ${CURLANG} "Kompakt"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.de"
LangString TITLE_SecAllUsersUI ${CURLANG} "Installations-Optionen"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Welche Benutzer können $(^NameDA) starten ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) Installation der Zugriffsrechte"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) kann für alle oder nur den aktuellen Benutzer installiert werden. Wählen Sie bitte, wie $(^NameDA) installiert werden soll."
LangString LIST_SecAllUsersUI ${CURLANG} "Alle Benutzer|Aktueller Benutzer"
LangString STATE_SecAllUsersUI ${CURLANG} "Alle Benutzer"


!verbose 4
