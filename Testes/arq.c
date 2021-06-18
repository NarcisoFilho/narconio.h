#include <stdio.h>
#include <stdlib.h>

int main(){
        FILE* arq = fopen( "arq_teste.txt" , "w" );
        char ch;
        int i;
        char nmr[ 10 ] = { 0 };
        for( i = 33 ; i < 256 ; i++ ){
                fputc( i , arq );
                fputc( ' ' , arq );
                itoa( ch , nmr , 10 );
                fputs( nmr , arq );
                fputc( '\n' , arq );
                ch = i;
                printf("%3d  |  %c  |  %c\n" , i , i , ch );
        }

        fclose( arq );
        return 0;
}
