#ifndef __ATIVAR_ANSI_WINDOWS_H_
#define __ATIVAR_ANSI_WINDOWS_H_

         void ativarANSIConsole(void);
         void restaurarPadrao(void);

        #ifdef _WIN32
                #include <windows.h>
        #endif

        #include <stdio.h>
        #include "ativar_ansi_windows.h"
        #ifdef _WIN32

                // Versoes antigas do MinGW/CYGWIN nao definem:
                 #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
                 #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
                 #endif

                 static HANDLE stdoutHandle;
                 static DWORD outModeInit;

                 void ativarANSIConsole(void) {
                        DWORD outMode = 0;
                        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

                        if(stdoutHandle == INVALID_HANDLE_VALUE) {
                                exit(GetLastError());
                        }

                        if(!GetConsoleMode(stdoutHandle, &outMode)) {
                                exit(GetLastError());
                        }

                        outModeInit = outMode;

                        // Ativar sequencias de escape ANSI
                        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

                        if(!SetConsoleMode(stdoutHandle, outMode)) {
                                exit(GetLastError());
                        }
                 }

                 void restaurarPadrao(void) {
                        // Restaurar cores
                        printf("\x1b[0m");

                        // Restaurar padrao windows
                        if(!SetConsoleMode(stdoutHandle, outModeInit)) {
                                exit(GetLastError());
                        }
                 }
         #else
                 void ativarANSIConsole(void) {}

                 void restaurarPadrao(void) {
                     // Restaurar cores
                     printf("\x1b[0m");
                 }
         #endif


#endif // __ATIVAR_ANSI_WINDOWS_H_
