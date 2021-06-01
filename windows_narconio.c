
#include "windows_narconio.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        // Versões antigas do MinGW/CYGWIN não definem :
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif


/// ATIVAÇÃO/DESATIVAÇÃO DE PADRÃO INTERNACIONAL ANSI ════════════

static HANDLE stdoutHandle;     // Handle da tela
static DWORD outModeInit;      // Modo de saída original

/** \brief Ativa as sequências de escape ANSI no SO windows
 *
 * \param void
 * \return void
 *
 */

void ativar_es_ANSI_windows( void ){
        DWORD outMode = 0;

        /// Obtenção do handle de saída padrão
        stdoutHandle = GetStdHandle( STD_OUTPUT_HANDLE );

        /// Verificação de validade do handle
        if( stdoutHandle == INVALID_HANDLE_VALUE ) exit( GetLastError() );

        /// Obtenção do modo de saída original
        if( !GetConsoleMode( stdoutHandle , &outMode ) )
                exit( GetLastError() );         // Verificação de Sucesso

        outModeInit = outMode;

        /// Ativar sequencias de escape ANSI
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        /// Atribuir modo de saída modificado à tela
        if( !SetConsoleMode( stdoutHandle , outMode ) )
                exit( GetLastError() );         // Verificação de Sucesso
 }

/** \brief Restaura a saída padrão windows
 *
 * \param void
 * \return void
 *
 */

void restaurar_padrao_windows( void ){
        printf("\x1b[0m");
        /// Restaurar modo de saída original
        if( !SetConsoleMode( stdoutHandle , outModeInit ) )
                exit( GetLastError() );
 }

