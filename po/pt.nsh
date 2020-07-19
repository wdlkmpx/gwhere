;Language specific include file for GWhere installer
;Created by Sébastien LECACHEUR (mailto:zero@gwhere.org)
;This file has been translated by Paulo ANDRE' (mailto:l16083@alunos.uevora.pt)

!verbose 3

!ifdef CURLANG
  !undef CURLANG
!endif
!define CURLANG ${LANG_PORTUGUESE}


LangString TITLE_SecCopyUI ${CURLANG} "$(^NameDA) (obrigatório)"
LangString DESC_SecCopyUI ${CURLANG} "Motor principal da aplicação."
LangString TITLE_SecCopyGTK ${CURLANG} "RunTime GTK+ 2.6 (obrigatório)"
LangString DESC_SecCopyGTK ${CURLANG} "RunTime para o ambiente GUI."
LangString TITLE_SecCopyPLUGINS ${CURLANG} "Plugins"
LangString DESC_SecCopyPLUGINS ${CURLANG} "Plugins para extracção automática de descritores e plugins paraimportação/exportação de catálogos."
LangString TITLE_SecCopyLANG ${CURLANG} "Ficheiros de Linguagem"
LangString DESC_SecCopyLANG ${CURLANG} "Todos os ficheiros de linguagem para a tradução do programa."
LangString UninstBefore ${CURLANG} "Terá de desinstalar a sua última versão de $(^NameDA)"
LangString InstAlready ${CURLANG} "O instalar já está em execução"
LangString InstTypeFull ${CURLANG} "Completo"
LangString InstTypeCompact ${CURLANG} "Compacto"
LicenseLangString URL_License ${CURLANG} "${MUI_BUILD_DIR}\..\doc\license\license.en"
LangString TITLE_SecAllUsersUI ${CURLANG} "Opções de instalação"
LangString SUBTITLE_SecAllUsersUI ${CURLANG} "Que utilizadores podem executar $(^NameDA) ?"
LangString SUBSUBTITLE_SecAllUsersUI ${CURLANG} "Direitos de acesso à instalação de $(^NameDA)"
LangString ASK_SecAllUsersUI ${CURLANG} "$(^NameDA) poderá ser instalado para todos os utilizadores ou apenas para o utilizador actual. Seleccione para quem deseja instalar $(^NameDA) por favor."
LangString LIST_SecAllUsersUI ${CURLANG} "Todos os utilizadores|Utilizador actual"
LangString STATE_SecAllUsersUI ${CURLANG} "Todos os utilizadores"


!verbose 4
