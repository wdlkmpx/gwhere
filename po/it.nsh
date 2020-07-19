;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Michele PETRECCA (mailto:petrecca@interfree.it)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_ITALIAN}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (richiesto)"
LangString DESC_SecCopyUI ${CURLANG} "Principale motore dell'applicazione."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 RunTime (richiesto)"
LangString DESC_SecCopyGTK ${CURLANG} "RunTime per l'ambiente GUI."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Plugins per l'estensione delle funzionalità (descrizione dei file e importazione/esportazione dei cataloghi)."
LangString TITLE_SecCopyLANG ${CURLANG} "Pacchetto Lingua"
LangString DESC_SecCopyLANG ${CURLANG} "Tutti i files di linguaggio per la traduzione del programma."
LangString UninstBefore ${CURLANG} "Devi disinstallare l'ultima versione di $(^NameDA)"
LangString InstAlready ${CURLANG} "Installazione in corso..."
LangString InstTypeFull ${CURLANG} "Completo"
LangString InstTypeCompact ${CURLANG} "Compatto"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Installa opzioni"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Quale utente può lanciare $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) installa i diritti d'accesso"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) può essere installato per tutti gli utenti o solo per l'utente corrente. Seleziona per chi vuoi installare $(^NameDA) , per favore."
LangString LIST_SecAllUsersUI ${CURLANG} "Tutti gli utenti|Utente corrente"
LangString STATE_SecAllUsersUI ${CURLANG} "Tutti gli utenti"


!verbose 4
