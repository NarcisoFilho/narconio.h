/**< TESTE DAS FUNÇÕES */
#include "narconio.h"
//#include "ativar_ansi_windows.h"
//#include "locale.h"
int main(){
        int espacamento = 3;
        FONTE fonte[ 10 ];
        fonte[ 0 ] = carregarFonte("Fonte/Big.txt");
        fonte[ 1 ] = carregarFonte("Fonte/Small.txt");
        fonte[ 2 ] = carregarFonte("Fonte/StarWars.txt");

        int qtd_fontes = 3;

        inicializarJanela();

        int i = 0;
        for( ; ; ){
                printFonte("#0177 2 ! @$%" , fonte[ i ] , (PONTO){ 2 , 4 } , espacamento , AZUL , PRETO );
                printFonte("aBcD TESTE!" , fonte[ i ] , (PONTO){ 2 , 4 + 2 + fonte[ i ].altu } , espacamento , AZUL , PRETO );
                printFonte("M Narciso F 77" , fonte[ i ] , (PONTO){ 2 , 4 + 4 + 2 * fonte[ i ].altu } , espacamento , AZUL , PRETO );
                pausaMS( 500 );
                LMPTELA;
                i++;
                if( i == qtd_fontes ) i = 0;
        }

        finalizarJanela();

        return 0;
}
