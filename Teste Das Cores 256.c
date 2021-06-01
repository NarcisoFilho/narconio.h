/**< TESTE DAS CORES */

#include <stdio.h>
#include <windows.h>

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

int main(){
        ativarANSIConsole();

        printf("1-texto , 2- fundo do texto , 3-ambos");
        switch( getchar() ){
                case '1':
                        for( int i = 0 ; i < 256 ; i++ ){
                                printf("\x1b[38;5;%dm" , i );
                                printf("This is a test! : %d\n" , i);
                                Sleep( 25 );
                        }
                        break;
                case '2':
                        for( int i = 0 ; i < 256 ; i++ ){
                                printf("\x1b[48;5;%dm" , i );
                                printf("This is a test! : %d\n" , i);
                                Sleep( 25 );
                        }
                        break;
                case '3':
                        for( int i = 0 ; i < 256 ; i++ ){
                                printf("\x1b[48;5;%dm" , i );
                                for( int j = 0 ; j < 256 ; j++ ){
                                        printf("\x1b[38;5;%dm" , j );
                                        printf("This is a test! : fundo-%d  texto-%d\n" , i , j);
                                        Sleep( 25 );
                                }
                        }
                        break;

        }

        Sleep( 100000 );
        getchar();
        return 0;
}

