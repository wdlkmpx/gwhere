;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Victor G. MARIMON (mailto:vgmarimon@terra.es)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_SPANISH}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (requerido)"
LangString DESC_SecCopyUI ${CURLANG} "Motor aplicacion principal."
LangString TITLE_SecCopyGTK ${CURLANG} "GTK+ 2.6 Runtime (requerido)"
LangString DESC_SecCopyGTK ${CURLANG} "Runtime para entorno GUI."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Plugins para autoextracción de las descripciones de fichero y plugins para/importar y exportar catálogos."
LangString TITLE_SecCopyLANG ${CURLANG} "Ficheros de idioma"
LangString DESC_SecCopyLANG ${CURLANG} "Todos los ficheros de idioma para la traduccion del programa."
LangString UninstBefore ${CURLANG} "Debes desinstalar tu ultima version de $(^NameDA)"
LangString InstAlready ${CURLANG} "Instalador ya funcionando"
LangString InstTypeFull ${CURLANG} "Completo/a"
LangString InstTypeCompact ${CURLANG} "Compacto/a"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.es"
LangString TITLE_SecAllUsersUI ${CURLANG} "Opciones de Instalacion"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Que usuarios pueden ejecutar $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "$(^NameDA) instalar derechos de acceso"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) puede ser instalado para todos los usuarios o solamente para el usuario actual. Selecciona para cual quieres instalarlo $(^NameDA) por favor."
LangString LIST_SecAllUsersUI ${CURLANG} "Todos los usuarios|Solo para mi"
LangString STATE_SecAllUsersUI ${CURLANG} "Todos los usuarios"


!verbose 4
