;Language specific include file for GWhere installer
;Created by Sιbastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Dimitris GARANATSIOS (mailto:rs96057@hotmail.com)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_GREEK}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (απαιτείται)"
LangString DESC_SecCopyUI ${CURLANG} "Κυρίως εφαρμογή."
LangString TITLE_SecCopyGTK ${CURLANG} "Περιβάλλον εκτέλεσης GTK+ 2.4 (απαιτείται)"
LangString DESC_SecCopyGTK ${CURLANG} "Βιβλιοθήκες εκτέλεσης του γραφικού περιβάλλοντος."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Plugins για αυτόματη εξαγωγή περιγραφών αρχείων."
LangString TITLE_SecCopyLANG ${CURLANG} "Πολύγλωσση υποστήριξη"
LangString DESC_SecCopyLANG ${CURLANG} "Αρχεία μεταγλώτισης του προγράμματος."
LangString UninstBefore ${CURLANG} "You must uninstall your last version of $(^NameDA)"
LangString InstAlready ${CURLANG} "Installer already running"
LangString InstTypeFull ${CURLANG} "Full"
LangString InstTypeCompact ${CURLANG} "Compact"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Install options"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Which users can run $(^NameDA)?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) install rights access"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) can be installed for all users or only for current user. Select for which you want install $(^NameDA) please."
LangString LIST_SecAllUsersUI ${CURLANG} "All users|Current user"
LangString STATE_SecAllUsersUI ${CURLANG} "All users"


!verbose 4
