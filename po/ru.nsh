;Language specific include file for GWhere installer
;Created by S�bastien LECACHEUR (mailto:zero@gwhere.org)
;

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_RUSSIAN}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (требуется)"
LangString DESC_SecCopyUI ${CURLANG} "Главное прилжение"
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 RunTime (необходимо)"
LangString DESC_SecCopyGTK ${CURLANG} "RunTime для GUI окружения."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Плагины"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Плагины для автоматического извлеченияописаний файлов и плагины для импорта/экспорта каталогов."
LangString TITLE_SecCopyLANG ${CURLANG} "Языковые файлы"
LangString DESC_SecCopyLANG ${CURLANG} "Все языковые файлы для перевода программы."
LangString UninstBefore ${CURLANG} "Вы должны деинсталировать вашу последнюю версию $(^NameDA)"
LangString InstAlready ${CURLANG} "Инсталяция уже запущена"
LangString InstTypeFull ${CURLANG} "Полный"
LangString InstTypeCompact ${CURLANG} "Сжатый"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Настройки инсталятора"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Какие пользователи могут запускать $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) установит права доступа"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) может быть установлен для всех пользователей или только для текущего пользователя. Укажите, пожалуйста, как вы хотите установить $(^NameDA)."
LangString LIST_SecAllUsersUI ${CURLANG} "Все пользователллли|Текущий пользователь"
LangString STATE_SecAllUsersUI ${CURLANG} "Все пользователи"


!verbose 4
