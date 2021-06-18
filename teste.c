#include "narconio.h"
#include "limits.h"

typedef struct{
        char nome_jogador[ 15 ];
        int pontos;
}HIGHSCORES; /* Registro das pontuações mais altas carregadas de arquivo .bin */

int main(){
//        FONTE fonte = carregarFonte("Fonte/big.txt");
        inicializarJanela();

        HIGHSCORES highscores[ 15 ][ 5 ];
        for( int i = 0 ; i <= 14 ; i++ )
                for( int j = 0 ; j < 5 ; j++ ){
                        highscores[ i ][ j ].pontos = 0;
                        strcpy( highscores[ i ][ j ].nome_jogador , "-------\0" );
                }

        FILE* arq = fopen( "highscores.bin" , "wb" );
        if( arq == NULL ) ErroFatal( FALHA_AUTORIZACAO_ABERTURA_ARQ );

        for( int i = 0 ; i <= 14 ; i++ )
                for( int j = 0 ; j < 5 ; j++ )
                        fwrite( &highscores[ i ][ j ] , sizeof( HIGHSCORES ) , 1 , arq );

        fclose( arq );


        pausaS( 2 );
        return 0;
}
