
#include "narconio.h"
#include "narconio_interno.h"

/// INICIALIZAÇÃO ═══════════════════════════════════════════════════

/** \brief Inicializa a janela de saída
 *
 * \param void
 * \return void
 *
 * @attention Sempre inclua essa função antes de usar outros comandos da narconio.h
 * @see finalizarJanela()
 */
void inicializarJanela( void ){

        /// Procedimentos exclusivos para o windows
        #ifdef _WIN32
                ativar_es_ANSI_windows();        // Ativa as sequências de escape padrão ANSI no windows
        #endif
}
//###########################################################


/** \brief Restaura modo de janela padrão
 *
 *      Restaura o console padrão no windows e simplesmente restaura cores em outros sistemas
 *      operacionais
 * \param void
 * \return void
 * \bug No momento em que é usado no window todo o texto estilizado é transforamado em texto padrão
 * mesmo o texto que tenha sido impresso na tela antes do comando.
 * \note Caso deseje-se visualizar texto estilizado após o encerramento da execução recomenda-se
 * não usar a função finalizarJanela();
 * \note Em alguns SO's esse comando simplesmente restaura as cores padrões.
 */

void finalizarJanela( void ){

        /// Restaurar cores
        printf("\x1b[0m");

        /// Procedimentos exclusivos para o windows
        #ifdef _WIN32
                restaurar_padrao_windows();
        #endif
}
//###########################################################



/// INTERAÇÃO COM O USUÁRIO ══════════════════════════════════════════

/// SISTEMA ------------------------------------------------------------------------------
/** \brief Pausa a execução por alguns Milisegundos
 *
 * \param int : O tempo em milisegundos
 * \return void
 *
 */

void pausaMS( int tempoMS ){
        long int tempoInicial = clock();
        while( clock() < tempoInicial + tempoMS );
}
//###########################################################



/** \brief Pausa a execução por alguns segundos
 *
 * \param int : O tempo em segundo
 * \return void
 *
 */

void pausaS( float tempoS ){
        long int tempoInicial = time( NULL );
        while( time( NULL ) < tempoInicial + tempoS );
}
//###########################################################



/** \brief Pausa a execução até o usuário pressionar enter
 *
 * \param void
 * \return void
 *
 */
void pausaE( void ){
        fgetc( stdin );
}
//###########################################################



/** \brief Pausa a execução até o usuário pressionar enter, com limpeza prévia de buffer e micro pausa prévia
 *
 * \param void
 * \return void
 *        MANTÉM o programa em suspensão até o usuário pressionar enter. Realiza previamente uma
 *      limpeza de buffer e aplica uma pausa para evitar que o pressionamento do enter interfira em
 *      outro procedimento
 */
void pausaE_PRO( void ){
        char str[ 500 ];

        pausaMS( 250 );

        fgets( str , 490 , stdin );

        pausaMS( 50 );
}
//###########################################################



/** \brief Limpa o Buffer do teclado
 *
 * \param void
 * \return void
 *
 */
void limpaBuffer( void ){
        char c;

        if( !feof( stdin ) )
                while( ( c = getchar() ) != '\n'  &&  c != EOF );
}
//###########################################################



/** \brief Limpa o Buffer do teclado com garantia de não alterar cursor
 *
 * \param void
 * \return void
 *      Salva a posição do cursor e restaura após limpeza do buffer. Não recomendada se houver uso do
 *      do comando salvarCursor  no programa
 */
void limpaBuffer_PRO( void ){
        salvarPosCursor();
        limpaBuffer();
        carregarPosCursor();
}
//###########################################################



/** \brief Encerra sistema e exibe mensagem de erro
 *
 * \param int : Código do erro ( consultar narconio.h )
 * \return void
 *
 */
void ErroFatal( int cod ){
        char lista_erros[  ][ 200 ] = {
                "Problemas de autoriza\207\306o de abertura de arquivos.",      // FALHA_AUTORIZACAO_ABERTURA_ARQ
                "Problemas na alocação de memória."                                       // FALHA_ALOCACAO_MEM
        };

        char lista_sugests[  ][ 200 ] = {
                "Verifique, no seu SO, as permiss\344es de leitura e grava\207\306o do compilador",     // FALHA_AUTORIZACAO_ABERTURA_ARQ
                "Verifique as configura\207\344es de acesso \205 mem\162ria do compilador"               // FALHA_ALOCACAO_MEM
        };

        /// TELA AZUL
        defCorTxtFundo( AZUL );
        LMPTELA;
        cursorHome();
        for( int i = 700 ; i ; i-- )
                printf(" ");
        cursorHome();
        /// Aviso geral de erro fatal visual e sonoro
        printSublinhadoXY( "\aERRO FATAL!! ENCERRANDO SISTEMA >>" , 30 , 3 );
        for( int repete = 3 ; repete ; repete-- ){
                pausaS( 0.5 );          // Pausa por meio segundo
                printf("\a");
        }

        /// Mensagem de erro específico e sugestão de solução
        printColoridoXY("ERRO 100: " , 10 , 9 ,  BRANCO  );
        printf( "%s " , lista_erros[ cod - 100 ] );
        printColoridoXY("Sugest\306o: " , 10 , 15  , BRANCO );
        printf( "%s " , lista_sugests[ cod - 100 ] );
        avancarCursorLins( 3 );
        pausaS( 5 );
        exit( cod );
}
//###########################################################


/// TELA ═════════════════════════════════════════════════════

/// DESIGN --------------------------------------------------------------------------------


/** \brief Saída de caractere nas coordenadas ( x , y )
 *
 * \param char : Caractere
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \return void
 *
 */

void putcXY( char caractere , int x , int y  ){
        cursorXY( x , y );
        printf("%c" , caractere );
}
//###########################################################



/** \brief Saída de caractere colorido
 *
 * \param char : Caractere
 * \param COR : Cor do caractere
 * \return void
 *
 */

void putcColorido( char caractere , COR cor ){
        printf("\x1b[3%dm%c" , cor , caractere );
        RESET_PADRAO;
}
//###########################################################



/** \brief Saída de caractere colorido nas coordenadas ( x , y )
 *
 * \param char : Caractere
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \param COR : Cor do caractere
 * \return void
 *
 */

void putcColoridoXY( char caractere , int x , int y , COR cor ){
        defCorTxt( cor );
        putcXY( caractere , x , y );
        RESET_PADRAO;
}
//###########################################################



/** \brief Saída de caractere PRO
 *
 * \param char : Caractere
 * \param PONTO : Ponto de inserção do caractere
 * \param COR : Cor do caractere
 * \return void
 *
 */

void putc_PRO( char caractere , PONTO ponto , COR cor_text ,  COR cor_fundo , int estilo  ){
        defCorTxt_PRO( cor_text , cor_fundo , estilo );
        putcXY( caractere , ponto.x , ponto.y );

        RESET_PADRAO;
}
//###########################################################



/** \brief Saída de texto nas coordenadas ( x , y )
 *
 * \param char* : Texto
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \return void
 *
 */
void printXY( char* texto , int x , int y  ){
        cursorXY( x , y );
        printf("%s" , texto );
}
//###########################################################



/** \brief Saída de texto formatado colorido
 *
 * \param char* : Texto
 * \param COR : Cor do texto
 * \return void
 *
 */
void printfColorido( char* texto , COR cor ){

        // Em construção

}
//###########################################################


/** \brief Saída de texto colorido
 *
 * \param char* : Texto
 * \param COR : Cor do texto
 * \return void
 *
 */
void printColorido( char* texto , COR cor ){
        defCorTxt( cor );
        printf( "%s" , texto );
        RESET_PADRAO;
}
//###########################################################


/** \brief Saída de texto colorido nas coordenadas ( x , y )
 *
 * \param char* : Texto
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \param COR : Cor do texto
 * \return void
 *
 */
void printColoridoXY( char* texto , int x , int y , COR cor ){
        cursorXY( x , y );
        defCorTxt( cor );
        printf( "%s" , texto );
        RESET_PADRAO;
}
//###########################################################



/** \brief Saída de texto sublinhado
 *
 * \param char* : Texto
 * \return void
 *
 */
void printSublinhado( char* texto ){
        defEstiloTxt( SUBLINHADO );
        printf( "%s" , texto );
        RESET_PADRAO;
}
//###########################################################



/** \brief  Saída de texto sublinhado em posição (x , y )
 *
 * \param char* : Texto
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \return void
 *
 */
void printSublinhadoXY( char* texto , int x , int y ){
        cursorXY( x , y );
        printSublinhado( texto );
        RESET_PADRAO;
}
//###########################################################



/** \brief  Saída de texto sublinhado e colorido em posição (x , y )
 *
 * \param char* : Texto
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \param COR : Cor do texto
 * \return void
 *
 */
void printSubliColorXY( char* texto , int x , int y , COR cor ){
        defCorTxt( cor );
        printSublinhadoXY( texto , x , y );
        RESET_PADRAO;
}
//###########################################################



/** \brief Saída de texto PRO
 *
 * \param char* : Texto
 * \param PONTO : Ponto de inserção do texto
 * \param ESTILO : Ponto de inserção do texto
 * \param COR : Cor do texto
 * \return void
 *
 */
void print_PRO( char* texto , PONTO ponto , ESTILO estilo , COR cor_text , COR cor_fundo ){
        defCorTxt_PRO( cor_text , cor_fundo , estilo );
        cursorP( ponto );
        printf( "%s" , texto );
        RESET_PADRAO;
}
//###########################################################


/** \brief Carrega uma Fonte de algum arquivo de texto
 *
 * \param char* : Nome do arquivo de texto
 * \return FONTE : Fonte carregada e calibrada
 *
 */
FONTE carregarFonte( char* nome ){
        FONTE fonte_retorno;
        char altura[ 3 ];
        int i , j;      // Contador Interno do Arquivo
        int letra , largura;

        // Inicialização dos campos da fonte
        for( letra = 0 ; letra < 256 ; letra++ )
                fonte_retorno.caracs_dispon[ letra ] = false;

        fonte_retorno.qtd_caract = 0;

        strcpy( fonte_retorno.arq_fonte , nome);

        fonte_retorno.ptr = fopen( nome  , "r");

        // Extração do Arquivo texto
        i = j = 0;

        while( !feof( fonte_retorno.ptr )  &&  i < MAX_LINHAS_FONTE ){
                fonte_retorno.matriz[ i ][ j ] = fgetc( fonte_retorno.ptr );

                if( fonte_retorno.matriz[ i ][ j ] == '\n'   ||  j >= MAX_COLUNAS_FONTE - 10 ){
                        fonte_retorno.matriz[ i ][ j ] = '\0';
                        j = -1;
                        i++;
                }
                j++;
        }

        // Fechamento do Arquivo
        fclose( fonte_retorno.ptr );


        // Atribuição da altura das letras
        sscanf( fonte_retorno.matriz[ 0 ] , "%s" , altura  );
        fonte_retorno.altu = atoi( altura );

        // Atribuição da largura das letras
        i = 1;
        j = 0;
        largura = 0;
        do{
                do{
                        if( fonte_retorno.matriz[ i ][ j ] != ' ' ){
                                letra = fonte_retorno.matriz[ i ][ j ];

//                                printf("%c" , letra );                // Ative para testar mapeamento da fonte
                                fonte_retorno.larg[ letra ] = largura;

                                fonte_retorno.xf_letra[ letra ] = j;

                                fonte_retorno.x0_letra[ letra ] = j - largura + 1;

                                fonte_retorno.y0_letra[ letra ] = i;

                                largura = 0;



                                if( fonte_retorno.caracs_dispon[ letra ] == false ){
                                        fonte_retorno.qtd_caract++;
                                        fonte_retorno.caracs_dispon[ letra ] = true;
                                }

                        }
                        j++;
                        largura++;
                        if( fonte_retorno.matriz[ i ][ j - 1 ] == 'e'  &&  fonte_retorno.matriz[ i ][ j ] == 'e'  ) j++;

                }while( !( fonte_retorno.matriz[ i ][ j ] == '#'  &&  fonte_retorno.matriz[ i ][ j + 1 ] == '#' )  &&  j < MAX_COLUNAS_FONTE - 10 );
                j = 0;
                i += fonte_retorno.altu + 2;
        }while( i < MAX_LINHAS_FONTE  &&  !( fonte_retorno.matriz[ i ][ 0 ] == '$'  &&  fonte_retorno.matriz[ i ][ 1 ] == '$'  &&  fonte_retorno.matriz[ i ][ 2 ] == '$'  &&  fonte_retorno.matriz[ i ][ 2 ] == '$' )  );

        // Retorno
        return fonte_retorno;
}
//###########################################################

/** \brief Saída de texto com fonte personalizada
 *
 * \param char* : Texto
 * \param FONTE : Fonte a ser usada
 * \param PONTO : Ponto de inserção do texto ( Quina Superior Esquerda )
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \return void
 *
 */
void printFonte( char* texto , FONTE fonte , PONTO ponto , int espacamento , COR cor_text , COR cor_fundo ){
        int x , y;      // Contador para a tela
        int xg = 0 , uxg;      // Contador para a tela
        int i , j;      // Contador Interno do Arquivo
        int letra;      // Contador Interno do String
        int letra_imp;

        defCorTxt_PRO( cor_text , cor_fundo , PADRAO );

        cursorP( ponto );

        x = y = 0;
        for( letra = 0 ; letra < strlen( texto ) ; letra++ ){

                if( fonte.caracs_dispon[ texto[ letra ] ] == true )
                        letra_imp = (int)texto[ letra ];
                else
                        letra_imp = (int)'?';

                if( texto[ letra ] != ' ' ){
                        for( i = fonte.y0_letra[ letra_imp ] + 1 ; i < fonte.y0_letra[ letra_imp ] + fonte.altu + 1 ; i++ ){
                                for( j = fonte.x0_letra[ letra_imp ] ; j <= fonte.xf_letra[ letra_imp ] ; j++ ){
                                        putcXY( fonte.matriz[ i ][ j ] , ponto.x + xg + x , ponto.y + y );
                                        x++;
                                }
                                y++;
                                uxg = x;
                                x = 0;
                        }
                        xg += uxg;
                        y = 0;
                }else{
                        for( i = fonte.y0_letra[ letra_imp ] + 1 ; i < fonte.y0_letra[ letra_imp ] + fonte.altu + 1 ; i++ ){
                                for( j = 0 ; j < espacamento ; j++ ){
                                        putcXY( ' ' , ponto.x + xg + x , ponto.y + y );
                                        x++;
                                }
                                y++;
                                uxg = x;
                                x = 0;
                        }
                        xg += uxg;
                        y = 0;


                }
        }

        RESET_PADRAO;
}
//###########################################################



/** \brief Define COR do texto de saída, compatível com pcs muito antigos
 *
 * \param COR
 * \return void
 *
 */
void defCorTxt_OLD( COR cor ){
        printf("\x1b[3%dm" , cor);
}
//###########################################################



/** \brief Define COR do fundo do texto, compatível com pcs muito antigos
 *
 * \param COR
 * \return void
 *
 */
void defCorTxtFundo_OLD( COR cor ){
        printf("\x1b[4%dm" , cor);
}
//###########################################################



/** \brief Define COR do texto de saída
 *
 * \param COR
 * \return void
 *
 */
void defCorTxt( COR cor ){
        printf("\x1b[38;5;%dm" , cor );
}
//###########################################################



/** \brief Define COR do fundo do texto
 *
 * \param COR
 * \return void
 *
 */
void defCorTxtFundo( COR cor ){
        printf("\x1b[48;5;%dm" , cor );
}
//###########################################################



/** \brief Define ESTILO de saída do texto
 *
 * \param ESTILO : Estilo do texto
 * \return void
 *
 */
void defEstiloTxt( ESTILO estilo_do_texto ){
        printf("\x1b[%dm" , estilo_do_texto );
}
//###########################################################



/** \brief Define COR do texto de saída PRO
 *
 * \param COR : Cor do texto
 * \param COR : Cor do fundo do texto
 * \param int : Estilo do texto
 * \return void
 *
 */
void defCorTxt_PRO( COR cor_texto , COR cor_fundo , ESTILO estilo ){
        defEstiloTxt( estilo );
        defCorTxt( cor_texto );
        defCorTxtFundo( cor_fundo );
}
//###########################################################



/** \brief Limpa toda a Tela
 *
 * \param void
 * \return void
 *
 */

void limpaTela( void ){
        printf("\x1b[2J");
}

/** \brief Limpa toda a Tela com uma cor
 *
 * \param void
 * \return void
 *
 */

void limpaTela_PRO( COR cor ){
        defCorTxt_PRO( PRETO , cor , PADRAO );

        char linha[ 1000 ] = { 0 };

        for( int x = 1 ; x < 1000 ; x++ )
                strcat( linha , " " );

        for( int y = 1 ; y < 80 ; y++ )
                        printXY( linha , 1 , y );

        cursorHome();
}

/** \brief Limpa um Linha
 *
 * \param int : Número da linha
 * \return void
 *
 */
void limpaLinha( int linha ){
        cursorXY( 0 , linha );
        printf("\x1b[2K");
}



/// CURSOR ----------------------------------------------------------

/** \brief Posiciona o cursor na coluna x e na linha y
 *
 * \param int : x
 * \param int : y
 * \return void *
 */
void cursorXY( int x , int y ){
        printf("\x1b[%d;%dH" , y , x);
}
//###########################################################



/** \brief Posiciona o cursor no PONTO ponto
 *
 * \param PONTO : ponto
 * \param
 * \return
 *
 */

void cursorP( PONTO ponto ){
        printf("\x1b[" "%d" ";" "%d" "H" , ponto.y , ponto.x );
}
//###########################################################



/** \brief Posiciona o cursor no ponto incial ( 0 , 0 )
 *
 * \param void
 * \return void
 *
 */

void cursorHome( void ){
        printf("\x1b[H");
}
//###########################################################



/** \brief Posiciona o cursor em uma linha
 *
 * \param int : linha
 * \return void
 *
 */

void cursorLinha( int linha ){
        // Em construção
}
//###########################################################



/** \brief Salva Posicão do cursor
 *
 * \param void
 * \return void
 *
 */

void salvarPosCursor( void ){
        printf("\x1b[s");
}
//###########################################################



/** \brief Posiciona o cursor na posição salva anteriormente com o comando salvarPosCursor
 *
 * \param void
 * \return void
 *
 */

void carregarPosCursor( void ){
        printf("\x1b[u");
}
//###########################################################



/** \brief Avança o cursor um número de linhas sem alterar coluna
 *
 * \param int : Quantidade de linhas para avançar( ou recuar se negativo )
 * \return void
 *
 */

void avancarCursorLins( int qtd_lins ){
        if( qtd_lins > 0 )
                printf("\x1b[%dB" , qtd_lins);
        else
                printf("\x1b[%dA" , -qtd_lins);
}
//###########################################################



/** \brief Avança o cursor um número de colunas sem alterar linha
 *
 * \param int : Quantidade de colunas para avançar( ou recuar se negativo )
 * \return void
 *
 */

void avancarCursorCols( int qtd_cols ){
        if( qtd_cols > 0 )
                printf("\x1b[%dC" , qtd_cols);
        else
                printf("\x1b[%dD" , -qtd_cols);
}
//###########################################################



/** \brief Torna o cursor do teclado invisivel
 *
 * \param void
 * \return void
 *
 */

void esconderCursorTec( void ){
        printf("\x1b[?25l");
}
//###########################################################



/** \brief Torna o cursor do teclado visivel
 *
 * \param
 * \param
 * \return
 *
 */

void exibirCursorTec( void ){
        printf("\x1b[?25h");
}
//###########################################################



/** \brief Obtém as coordenadas do cursor do teclado
 *
 * \param void
 * \return PONTO : Posição do cursor do teclado
 */
PONTO obterCursorTec( void ){
//        printf("\x1b[6n");
        // Em construção
        return (PONTO){ 0 , 0};
}
//###########################################################



/// STRINGS ═════════════════════════════════════════════════════

/** \brief Retorna coordenada de inserção de string para centralização horizontal
 *
 * \param char* : Texto a ser centralizad
 * \param RETANG : Tela de referência
 * \return int : Número da coluna de inserção do texto para ficar centralizado
 *
 */

int centraTxtXTela( char* texto , RETANG tela ){
        return ( tela.larg - strlen( texto ) ) / 2;
}
//###########################################################



/// MATRIZES ═════════════════════════════════════════════════════

/** \brief Retorna coordenada de inserção de conjunto de strings para centralização vertical
 *
 * \param int :
 * \param RETANG : Tela de referência
 * \return int : Número da linha de inserção da matriz para ficar centralizado
 *
 */

int centraMatrizYTela( int qtd_elementos , RETANG tela ){
        return ( tela.altu - qtd_elementos ) / 2;
}
//###########################################################



/** \brief Checa se elemento pertence a array
 *
 * \param float : Elemento
 * \param int : Quantidade de elementos
 * \param VOID* : Array a ser vasculhado
 * \param char : Tipo do array
 * \return BOOL : Verdadeiro se elemento pertence ao array
 *
 */

int pertence( float elemento , int qtd_elementos , VOID* array_generico , char tipo ){
        switch( tipo ){
                case TIPO_CHAR:
                        {
                                char* array_formatado = (char*)array_generico;
                                for( int i = 0 ; i < qtd_elementos ; i++ )
                                        if( *( array_formatado + i ) == elemento)
                                                return true;
                        }
                        break;
                case TIPO_INT:
                        {
                                int* array_formatado = (int*)array_generico;
                                for( int i = 0 ; i < qtd_elementos ; i++ )
                                        if( *( array_formatado + i ) == elemento)
                                                return true;
                        }
                        break;
                case TIPO_FLOAT:
                        {
                                float* array_formatado = (float*)array_generico;
                                for( int i = 0 ; i < qtd_elementos ; i++ )
                                        if( *( array_formatado + i ) == elemento)
                                                return true;
                        }
                        break;


        }





        return false;
}
//###########################################################



///### FORMAS  ═════════════════════════════════════════════════════
        /// MACIÇAS --------------------------------------------------------------------------------
/** \brief Desenha retângulo
 *
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \param int : Largura
 * \param int : Altura
 * \param COR : Cor
 * \return void
 *
 */

void desenRetang( int x , int y , int larg , int altu , COR cor ){
        defCorTxtFundo( cor );
        for( int i = 0 ; i < altu ; i++ )
                for( int j = 0 ; j < larg ; j++ )
                        putcXY(' ', x + j , y + i );

        RESET_PADRAO;
}
//###########################################################



/** \brief Desenha retângulo a partir de RETANG
 *
 * \param RETANG : Retângulo a ser desenhado
 * \param char : Caractere de preenchimento
 * \param COR : Cor do texto
 * \param COR : Cor do fundo do texto
 * \return void
 *
 */

void desenRetang_R( RETANG retang , char caractere , COR cor_texto , COR cor_fundo ){
        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );
        for( int i = 0 ; i < retang.altu ; i++ )
                for( int j = 0 ; j < retang.larg ; j++ )
                        putcXY( caractere , retang.ponto.x + j , retang.ponto.y + i );

        RESET_PADRAO;
}
//###########################################################



/** \brief Desenha retângulo a partir de RETANG_CT
 *
 * \param RETANG_CT : Retângulo a ser desenhado
 * \param char : Caractere de preenchimento
 * \param COR : Cor do texto
 * \param COR : Cor do fundo do texto
 * \return void
 *
 */

void desenRetang_RCT( RETANG_CT retang , char caractere , COR cor_texto , COR cor_fundo ){
        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );
        for( int i = 0 ; i < retang.altu ; i++ )
                for( int j = 0 ; j < retang.larg ; j++ )
                        putcXY( caractere , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

        RESET_PADRAO;
}
//###########################################################



/// MOLDURAS --------------------------------------------------------------------------------

/** \brief  Desenha moldura linear retângular
 *
 * \param int : Coordenada x
 * \param int : Coordenada y
 * \param int : Largura
 * \param int : Altura
 * \param COR : Cor
 * \return void
 *
 */

void desenMolduraLinear( int x , int y , int larg , int altu , COR cor ){
        defCorTxt( cor );

        /// HORIZONTAL
        for( int i = 0 ; i < altu ; i += altu - 1 )
                for( int j = 0 ; j < larg ; j++ )
                        putcXY( '\304' , x + j , y + i );

        /// VERTICAL
        for( int j = 0 ; j < larg ; j += larg - 1 )
                for( int i = 0 ; i < altu ; i++ )
                        putcXY( '\263' , x + j , y + i );

        /// QUINAS
        putcXY( '\332' , x + 0 , y + 0 );                               // SUPERIOR ESQUERDA
        putcXY( '\277' , x + larg - 1 , y + 0 );                       // SUPERIOR DIREITA
        putcXY( '\300' , x + 0 , y + altu - 1 );                       // INFERIOR ESQUERDA
        putcXY( '\331' , x + larg - 1 , y + altu - 1 );           // INFERIOR DIREITA

        RESET_PADRAO;
}
//###########################################################



/** \brief  Desenha moldura linear retângular a partir de RETANG
 *
 * \param RETANG : Retângulo de desenho
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \param BOOL : Usar linha dupla
 * \return void
 *
 */

void desenMoldura_R( RETANG retang , COR cor_texto , COR cor_fundo , BOOL duplo ){            // Desenha moldura retângular a partir de RETANG
        char blocos[ 6 ];
        blocos[ 0 ] = ( duplo ) ? '\315' : '\304';   // Horizontal
        blocos[ 1 ] = ( duplo ) ? '\272' : '\263';   // Vertical
        blocos[ 2 ] = ( duplo ) ? '\311' : '\332';   // Superior Esquerdo
        blocos[ 3 ] = ( duplo ) ? '\273' : '\277';   // Superior Direito
        blocos[ 4 ] = ( duplo ) ? '\310' : '\300';   // Inferior Esquerdo
        blocos[ 5 ] = ( duplo ) ? '\274' : '\331';   // Inferior Direito

        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );

        /// HORIZONTAL
        for( int i = 0 ; i < retang.altu ; i += retang.altu - 1 )
                for( int j = 0 ; j < retang.larg ; j++ )
                        putcXY( blocos[ 0 ] , retang.ponto.x + j , retang.ponto.y + i );

        /// VERTICAL
        for( int j = 0 ; j < retang.larg ; j += retang.larg - 1 )
                for( int i = 0 ; i < retang.altu ; i++ )
                        putcXY( blocos[ 1 ] , retang.ponto.x + j , retang.ponto.y + i );

        /// QUINAS
        putcXY( blocos[ 2 ] , retang.ponto.x + 0 , retang.ponto.y + 0 );                               // SUPERIOR ESQUERDA
        putcXY( blocos[ 3 ] , retang.ponto.x + retang.larg - 1 , retang.ponto.y + 0 );                       // SUPERIOR DIREITA
        putcXY( blocos[ 4 ] , retang.ponto.x + 0 , retang.ponto.y + retang.altu - 1 );                       // INFERIOR ESQUERDA
        putcXY( blocos[ 5 ] , retang.ponto.x + retang.larg - 1 , retang.ponto.y + retang.altu - 1 );           // INFERIOR DIREITA

        RESET_PADRAO;
}
//###########################################################



/** \brief  Desenha moldura linear retângular a partir de RETANG_CT
 *
 * \param RETANG_CT : Retângulo de desenho
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \param BOOL : Usar linha dupla
 * \return void
 *
 */

void desenMoldura_RCT( RETANG_CT retang , COR cor_texto , COR cor_fundo , BOOL duplo ){
        char blocos[ 6 ];
        blocos[ 0 ] = ( duplo ) ? '\315' : '\304';   // Horizontal
        blocos[ 1 ] = ( duplo ) ? '\272' : '\263';   // Vertical
        blocos[ 2 ] = ( duplo ) ? '\311' : '\332';   // Superior Esquerdo
        blocos[ 3 ] = ( duplo ) ? '\273' : '\277';   // Superior Direito
        blocos[ 4 ] = ( duplo ) ? '\310' : '\300';   // Inferior Esquerdo
        blocos[ 5 ] = ( duplo ) ? '\274' : '\331';   // Inferior Direito

        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );

        /// HORIZONTAL
        for( int i = 0 ; i < retang.altu ; i += retang.altu - 1 )
                for( int j = 0 ; j < retang.larg ; j++ )
                        putcXY( blocos[ 0 ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

        /// VERTICAL
        for( int j = 0 ; j < retang.larg ; j += retang.larg - 1 )
                for( int i = 0 ; i < retang.altu ; i++ )
                        putcXY( blocos[ 1 ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

        /// QUINAS
        putcXY( blocos[ 2 ] , retang.ponto.x - retang.larg / 2 + 0 , retang.ponto.y - retang.altu / 2 + 0 );                               // SUPERIOR ESQUERDA
        putcXY( blocos[ 3 ] , retang.ponto.x - retang.larg / 2 + retang.larg - 1 , retang.ponto.y - retang.altu / 2 + 0 );                       // SUPERIOR DIREITA
        putcXY( blocos[ 4 ] , retang.ponto.x - retang.larg / 2 + 0 , retang.ponto.y - retang.altu / 2 + retang.altu  - 1 );                       // INFERIOR ESQUERDA
        putcXY( blocos[ 5 ] , retang.ponto.x - retang.larg / 2 + retang.larg - 1 , retang.ponto.y - retang.altu / 2 + retang.altu - 1 );           // INFERIOR DIREITA

        RESET_PADRAO;
}
//###########################################################



/** \brief Desenha moldura retângular com caractere personalizável e espessura variável
 *
 * \param RETANG : Retângulo de desenho
 * \param int : Espessura da moldura em casas
 * \param char : Caractere de preenchimento
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \return void
 *
 */

void desenMoldura_EX( RETANG retang , int espessura , char caratere , COR cor_texto , COR cor_fundo ){
        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );

        for( int i = 0 ; i < retang.altu ; i ++ )
                for( int j = 0 ; j < retang.larg ; j++ )
                        if( i < espessura  ||  i > retang.altu - 1 - espessura ||  j < espessura  ||  j > retang.larg - 1 - espessura )
                                putcXY( caratere , retang.ponto.x + j , retang.ponto.y+ i );

        RESET_PADRAO;
}
//###########################################################



/** \brief Desenha moldura retângular com sequências de caracteres
 *
 * \param RETANG : Retângulo de desenho
 * \param int : Espessura da moldura em casas
 * \param char* : Caracteres de preenchimento
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \return void
 *
 */

void desenMoldura_PRO( RETANG retang , int espessura , char* sequen_carateres , COR cor_texto , COR cor_fundo ){
        const int tam = strlen( sequen_carateres ) - 1;
        int aux = -1;

        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );

        /// TOPO
        for( int j = 0 ; j < retang.larg ; j++ ){
                aux++;

                for( int i = 0 ; i < espessura ; i ++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x + j , retang.ponto.y+ i );

                if( aux == tam ) aux = -1;
        }

        /// LATERAL DIREITA
        for( int i = espessura ; i < retang.altu - espessura ; i ++ ){
                aux++;

                for( int j = retang.larg - espessura ; j < retang.larg ; j++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x + j , retang.ponto.y+ i );

                if( aux == tam ) aux = -1;
        }

        /// BASE
        for( int j = retang.larg - 1 ; j >= 0  ; j-- ){
                aux++;

                for( int i = retang.altu - espessura ; i < retang.altu ; i ++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x + j , retang.ponto.y+ i );

                if( aux == tam ) aux = -1;
        }

        /// LATERAL ESQUERDA
        for( int i = retang.altu - 1 ; i >= espessura ; i-- ){
                aux++;

                for( int j = 0 ; j < espessura ; j++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x + j , retang.ponto.y+ i );

                if( aux == tam ) aux = -1;
        }

        avancarCursorLins( retang.altu );

        RESET_PADRAO;
}
//###########################################################



/** \brief Desenha moldura retângular com sequências de caracteres ( usa RETANG_CT )
 *
 * \param RETANG_CT : Retângulo de desenho
 * \param int : Espessura da moldura em casas
 * \param char* : Caracteres de preenchimento
 * \param COR : Cor do texto
 * \param COR : Cor do fundo
 * \return void
 *
 */

void desenMoldura_PRO_CT( RETANG_CT retang , int espessura , char* sequen_carateres , COR cor_texto , COR cor_fundo ){
        const int tam = strlen( sequen_carateres ) - 1;
        int aux = -1;

        defCorTxt_PRO( cor_texto , cor_fundo , PADRAO );

        /// TOPO
        for( int j = 0 ; j < retang.larg ; j++ ){
                aux++;

                for( int i = 0 ; i < espessura ; i ++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

                if( aux == tam ) aux = -1;
        }

        /// LATERAL DIREITA
        for( int i = espessura ; i < retang.altu - espessura ; i ++ ){
                aux++;

                for( int j = retang.larg - espessura ; j < retang.larg ; j++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

                if( aux == tam ) aux = -1;
        }

        /// BASE
        for( int j = retang.larg - 1 ; j >= 0  ; j-- ){
                aux++;

                for( int i = retang.altu - espessura ; i < retang.altu ; i ++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

                if( aux == tam ) aux = -1;
        }

        /// LATERAL ESQUERDA
        for( int i = retang.altu - 1 ; i >= espessura ; i-- ){
                aux++;

                for( int j = 0 ; j < espessura ; j++ )
                        putcXY( sequen_carateres[ aux ] , retang.ponto.x - retang.larg / 2 + j , retang.ponto.y - retang.altu / 2 + i );

                if( aux == tam ) aux = -1;
        }

        avancarCursorLins( retang.altu );

        RESET_PADRAO;
}
//###########################################################

