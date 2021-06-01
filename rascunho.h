#ifndef __RASCUNHO_H_
#define __RASCUNHO_H_

                // Elementos Teclas Simples
//        int teclas_simples[] = {
//                TECLA_ENTER,
//                TECLA_ESPACO,
//                TECLA_BACKSPACE,
//                TECLA_ESC,
//                TECLA_DEL,
//                TECLA_TAB
//
//        };
//        #define QTD_TECLAS_SIMPLES sizeof( teclas_simples ) / sizeof( int )
//
//        // Elementos Teclas Setas
//        int teclas_setas[] = {
//                TECLA_SETA_DIREITA,
//                TECLA_SETA_ESQUERDA,
//                TECLA_SETA_BAIXO,
//                TECLA_SETA_CIMA
//        };
//        #define QTD_TECLAS_SETAS sizeof( teclas_setas ) / sizeof( int )
//
//        int teclas_especiais[] = {
//                TECLA_SETA_DIREITA,
//                TECLA_SETA_ESQUERDA,
//                TECLA_SETA_BAIXO,
//                TECLA_SETA_CIMA
//
//        };

/// RASCUNHOS
//        /// TECLADO ------------------------------------------------------------------------------
//        BOOL checaTecla( int tecla );                   // Verifica se tecla está sendo pressionada
//        BOOL checaTeclaEspecial( int tecla );        // Verifica se tecla especial está sendo pressionada
//        BOOL checaTeclasSetas( int seta_checar );       // Checa o status de acionamento de uma tecla seta



///** \brief Checa o status de acionamento de uma tecla
// *
// * \param int : Código da Tecla
// * \return BOOL : Status de acionamento da tecla
// *
// */
//
//
//BOOL checaTecla( int tecla ){
//        // Buffer Temporário: 0 -> Teclas simples , 1-> 1° Byte Tecla especial , 2° Byte Tecla especial
//        static char buffer_temp[ 3 ] = { '\0' };
//
//        int tecla_pressionada;
//
//        /// Teclas Simples
////        if( pertence( tecla , QTD_TECLAS_SIMPLES , teclas_simples , TIPO_INT ) ){
////                if ( kbhit()  ||  buffer_temp[ 0 ] ){
////
////                        if( kbhit() ){
////                                tecla_pressionada = getch();
////                                if( tecla_pressionada == tecla ){
////                                        buffer_temp[ 0 ] = '\0';
////                                        return true;
////                                }else{
////                                        buffer_temp[ 0 ] = tecla_pressionada;
////                                        if ( tecla_pressionada == 224 ) {
////                                                buffer_temp[ 1 ] = tecla_pressionada;////                                                do {
////                                                        tecla_pressionada = getch();
////                                                } while( tecla_pressionada == 224 );
////                                                buffer_temp[ 2 ] = tecla_pressionada;
////                                        }
////
////                                }
////                        }else{
////                                if( buffer_temp[ 0 ] == tecla ){
////                                        buffer_temp[ 0 ] = '\0';
////                                        return true;
////                                }
////                        }
////                }
////        }
//
//
//        /// Teclas Setas
//        if( pertence( tecla , QTD_TECLAS_SETAS , teclas_setas , TIPO_INT ) ){
//                if ( kbhit() ){
//                        tecla_pressionada = getch();
//                        buffer_temp[ 1 ] = tecla_pressionada;
//
//                        if ( tecla_pressionada == 224 ){
//                                do{
//                                        tecla_pressionada = getch();
//                                }while( tecla_pressionada == 224 );
//
//                                if( tecla_pressionada == tecla % 100  ||  buffer_temp[ 2 ] == tecla % 100 ){
//                                        buffer_temp[ 0 ] = '\0';
//                                        buffer_temp[ 1 ] = '\0';
//                                        buffer_temp[ 2 ] = '\0';
//                                        return true;
//                                }
//
//                                buffer_temp[ 0 ] = '\0';
//                                buffer_temp[ 1 ] = 224;
//                                buffer_temp[ 2 ] = tecla_pressionada;
//                        }
//                }else{
//                        if(  buffer_temp[ 1 ] == 224 ){
//                                if(  buffer_temp[ 2 ] == tecla % 100 ){
//                                        buffer_temp[ 0 ] = '\0';
//                                        buffer_temp[ 1 ] = '\0';
//                                        buffer_temp[ 2 ] = '\0';
//                                        return true;
//                                }
//                        }
//                }
//        }
////                if ( kbhit()  ||  buffer_temp[ 3 ] ){
////
////                        if( kbhit() ){
////                                byte1 = getch();
////                                if( byte1 == tecla / 100 ){
////                                        do{
////                                                byte2 = getche();
////                                        }while( byte2 == tecla / 100);
////
////                                        if( byte2 == tecla % 100 ){
////                                                buffer_temp[ 2 ] = '\0';
////                                                return true;
////                                        }else
////                                                buffer_temp[ 2 ] = byte2;
////                                }else
////                                        buffer_temp[ 1 ] = byte1;
////
////                        }else{
////                                if( buffer_temp[ 1 ] == tecla / 100 )
////                                        if( buffer_temp[ 2 ] == tecla % 100 ){
////                                                buffer_temp[ 1 ] = '\0';
////                                                buffer_temp[ 2 ] = '\0';
////                                                return true;
////                                        }
////                                }
////                        }
////        }
//
//        return false;
//}
////###########################################################



///** \brief Checa o status de acionamento de uma tecla especial
// *
// * \param int : Código da Tecla
// * \return BOOL : Status de acionamento da tecla
// *
// */
//BOOL checaTeclaEspecial( int tecla ){
//        int codigo_tecla_recebido;
//        int cod_1 = tecla / 100;
//        int cod_2 = tecla % 100;
//
//        /// Coletando 1° código da tecla pressionada, se houver
//        if( !kbhit() ) return false;
//        else {
//                 codigo_tecla_recebido = getch();
//                /// Teclas Especiais
//                if ( codigo_tecla_recebido == cod_1){
////                        while( getch() == cod_1);
//                        do{
//                                codigo_tecla_recebido = getch();
//                        }while( codigo_tecla_recebido == cod_1 );
//
//                        /// Coletando segundo código
//                        if( getch() == cod_2 )
//                                return true;
//                }
//        }
//
//        return false;
//}
////###########################################################
//
//
//
///** \brief Checa o status de acionamento de uma tecla seta
// *
// * \param int : Código da Tecla seta
// * \return BOOL : Status de acionamento da tecla seta
// *
// */
//BOOL checaTeclasSetas( int seta_checar ){
//        int tecla = 0;
//        int cod = seta_checar % 100;
//
//        if ( kbhit() )
//                tecla = getch();
//
//        if ( tecla == 224 )  {
//                do {
//                        tecla = getch();
//                } while( tecla == 224 );
//
//                if( tecla == cod )
//                        return TRUE;
//        }
//
//        return FALSE;
//}
////###########################################################
//
//
/// TECLADO ------------------------------------------------------------------------------
//
///** \brief Retorna tecla que foi pressionada
// *      Obtém e analisa conteúdo de stdin
// *
// * \param void
// * \return TECLA : Tecla que está sendo pressionada
// *
// */
//TECLA obterTeclaPressionada( void ){
//        char conteudo_stdin[ 100 ];
//        TECLA tecla = 0;
//
//        if( !feof( stdin ) ){
//                fread( conteudo_stdin , sizeof( char ) , 1 , stdin );
//                tecla = getch();
//                fread( &tecla , sizeof( char ) , 1 , stdin );
//                fwrite( "\n" , sizeof(char) , 1 , stdout );
//                printf(">%d<" , getch() );
//                tecla = conteudo_stdin[ 0 ];
//
//                if( pertence( tecla , QTD_TECLAS_SIMPLES , teclas_simples , TIPO_INT ) )
//                if( tecla != 224 )
//                        return tecla;
//
//
//                if( tecla == 224 ){
//                        do{
//                                tecla = getch();
////                                fread( conteudo_stdin , sizeof( char ) , 1 , stdin );
////                        }while( conteudo_stdin[ 0 ] == 224);
//                        }while( tecla == 224);
//
////                        tecla = conteudo_stdin[ 0 ];
//                        tecla += 22400;
//
//                        return tecla;
//                }
//
//        }
//
//        return NENHUMA_TECLA;
//
//}

//        /// TECLADO ------------------------------------------------------------------------------
//        TECLA obterTeclaPressionada( void );
//
//        // TECLAS SIMPLES
//        #define TECLA_ENTER '\n'
//        #define TECLA_ESPACO ' '
//        #define TECLA_BACKSPACE '\b'
////        #define TECLA_ESC '\e'
//        #define TECLA_ESC '\x1b'
//        #define TECLA_DEL 127
//        #define TECLA_TAB '\t'
//
//        // TECLAS ESPECIAIS
//        #define TECLA_SETA_DIREITA  22477
//        #define TECLA_SETA_ESQUERDA 22475
//        #define TECLA_SETA_BAIXO 22480
//        #define TECLA_SETA_CIMA 22472
//        #define NENHUMA_TECLA 0
//
//

//FILE* buffer_entrada;   // Arquivo de texto que servirá como buffer de entrada similar a stdin



///** \brief Obtém próximo caractere na fila do buffer de entrada narconio
// *   Obtém o próximo char e o deleta do arquivo buffer_entrada.txt
// *
// * \param void
// * \return int : O caractere proeminente na fila do buffer
// *
// */
////#define CAPACIDADE_BUFFER 300
////        static char buffer_entrada[ CAPACIDADE_BUFFER ];
//int obterChar_buffer( void ){
//        // Retorna posição de leitura para a origem
////        fseek( buffer_entrada , SEEK_SET , 0 );
//
//        // Coleta do caractere proeminente e retorno
////        caractere = getc( buffer_entrada );
//}
//
//
//
///** \brief Copia o conteúdo do buffer padrão stdin para o buffer_entrada da narconio
// *      Copia manualmente caractere por caractere o buffer padrão para o buffer narconio
// *
// * \param void
// * \return void
// *
// */
//void atualiza_buffer( void ){
//        // Processo de Cópia
////        while( !feof( stdin ) )
////                fputc( fgetc( stdin ) , buffer_entrada );         // Coleta char de stdin e atribui a buffer_entrada
//}
//

#endif // __RASCUNHO_H_
