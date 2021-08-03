#include "extra.h"

        //FUNCIONES PARA EL CODIFICADO POR EL METODO 1


unsigned long long lectura_natural(){

    ifstream archivo ;

    unsigned long long tam = 0 ;

    archivo.open( "natural.txt", ios::in | ios::ate );         //Abrimos el archivo en modo lectura

    if( archivo.is_open() ){

        tam  = archivo.tellg(); //Tamaño del archivo

    }
    else{

        cout << " El archivo NO se pudo abrir..." << endl ;

    }

    archivo.close();        //cerramos el archivo

    return tam ;

}


void contenido_archivo( unsigned long long tam, int n ){

    try{    //Usamos un try/catch ya que puede ocurrir un problema al momento de crear el arreglo si no hay suf. memoria

        char *arreglo = new char[tam+1] ;           //Si hay que poner el +1

        ifstream archivo ;

        archivo.open( "natural.txt", ios::in );     //Abrimos el archivo en modo lectura

        archivo.read(arreglo, tam+1);      //Llenamos el arreglo con los caracteres que componen el archivo

        try{

            conversion_entero(tam,arreglo, n);      //Convertimos los caracteres del texto a binario

            archivo.close();                            //cerramos el archivo

            delete []arreglo ;

        }
        catch (...) {

            throw ;     //Throw para que salte una excepcion si ocurrio algun error
        }

    }
    catch (...) {

        cout << endl << " Ocurrio un problema de excepcion en la función contenido_archivo() " << endl ;

    }

}



void conversion_entero( unsigned long long tam, char *arreglo, int n ){

    int **entero = new int*[tam+1] ;

    for( unsigned long long k = 0 ; k < tam ; k++ ){      //Creamos una matriz, en donde las filas representan un caracter
                                            // y las columnas los bits que tiene cada letra en binario
        entero[k] = new int[8] ;
    }

    int num ;

    for( unsigned long long f = 0 ; f < tam ; f++){      //Ciclo en el cual convertimos a binario

        num = int( arreglo[f] );

        for( int c = 7 ; c >= 0 ; c--){

            entero[f][c] = num % 2 ;        //Operacion para obtener los bits y ubicalos de derecha a izquierda

            num = num/2 ;
        }
    }


    codif_met1_chr( entero ,n,tam);         //Codificamos por el primer metodo {con arreglos char}

    try{

        escritura_bin_met1( entero, tam );

    }
    catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función escritura_bin_met1() " << endl ;

    }

    delete []entero ;
}



void codif_met1_chr( int **arb, int n, unsigned long long tam ){

    int cont1 = 1, cont2 = 1, unos = 0, ceros = 0, gant0 = 0, gant1 = 0, cont3 = 1 ;          //Contadores

    for( unsigned long long f = 0 ; f < tam ; f++ ){

        for( int c = 0 ; c < 8 ; c++ ){


            if( cont1 <= n && cont2 == 1 ){     //Primer grupo para ser codificado

                if( arb[f][c] == 0 ){

                    ceros++ ;

                    arb[f][c] = 1 ;
                }
                else{

                    unos++ ;

                    arb[f][c] = 0 ;
                }

                cont1++ ;

            }
            else if( gant0 > gant1 && cont2 > 1 ){      //Si hay mayor cantidad de ceros

                    if( cont3 == 2 ){           //Intercambia cada 2 bits

                        if( arb[f][c] == 0 ){

                            ceros++ ;

                            arb[f][c] = 1 ;
                        }
                        else{

                            unos++ ;

                            arb[f][c] = 0 ;
                        }


                        cont3 = 1 ;

                    }
                    else{

                        if( arb[f][c] == 0 ){

                            ceros++ ;
                        }
                        else{

                            unos++ ;
                        }


                        cont3++ ;

                    }

                    cont1++ ;

            }
            else if( gant0 < gant1 && cont2 > 1 ){      //Si hay mayor cantidad de unos

                if( cont3 == 3 ){           //Intercambia cada 3 bits

                    if( arb[f][c] == 0 ){

                        ceros++ ;

                        arb[f][c] = 1 ;
                    }
                    else{

                        unos++ ;

                        arb[f][c] = 0 ;
                    }


                    cont3 = 1 ;

                }
                else{


                    if( arb[f][c] == 0 ){

                        ceros++ ;
                    }
                    else{

                        unos++ ;
                    }


                    cont3++ ;

                }

                cont1++ ;

            }
            else if( gant0 == gant1 && cont2 > 1 ){     //Si hay igual cantidad de ceros y de unos

                if( arb[f][c] == 0 ){

                    ceros++ ;

                    arb[f][c] = 1 ;
                }
                else{

                    unos++ ;

                    arb[f][c] = 0 ;
                }

                cont1++ ;

            }



            if( cont1 > n ){       //Condicion que revisa si el contador llegó al numero n ingresado por el usuario

                cont2++ ;

                gant0 = ceros ;

                gant1 = unos ;

                unos = 0 ;

                ceros = 0 ;     //Reinicia estos 4 contadores para un nuevo grupo de n bits

                cont1 = 1 ;

                cont3 = 1 ;

            }

        }
    }

}



void escritura_bin_met1( int **arb, unsigned long long tam ){

    fstream archivo ;

    archivo.open( "codificado.dat" , ios::out | ios::binary );

    if( archivo.is_open() ){        //Verificamos que se haya abiero el archivo

        int *nuevo_arr = new int[tam*8];

        unsigned long long t = 0 ;

        for( unsigned long long f = 0 ; f < tam ; f++){     //Rellenamos el arreglo

            for( unsigned long long c = 0 ; c < 8 ; c++ ){

                nuevo_arr[t] = arb[f][c] ;

                t++ ;
            }
        }

        char *caracteres = new char[tam+1];

        unsigned long long a = 0, b ;

        int pot = 7, rest = 0, mult ;

        for( unsigned long long i = 1 ; i <= tam ; i++ ){

            b = i*8 ;

            for( ; a < b ; a++ ){

                mult = pow(2,pot);      //Potencias de 7 hasta 0 [base 2]

                rest = rest + mult*(nuevo_arr[a]) ;

                pot--;

            }

            a = b ;

            pot = 7 ;

            caracteres[i-1] = char(rest) ;

            rest = 0 ;

        }


        //ESCRIBIMOS

        char c ;

        for( unsigned long long e = 0 ; e < tam ; e++ ){

            c = caracteres[e] ;

            archivo.put(c);

        }

        delete []nuevo_arr ;

        delete []caracteres ;
    }
    else{

        cout << " NO se pudo abrir el archivo..." << endl ;
    }

    archivo.close();
}




        //FUNCIONES PARA EL DECODIFICADO POR EL METODO 1


unsigned long long lectura_binario(){

    ifstream archivo ;

    unsigned long long tam = 0 ;

    int numero ;

    string nombre_archivo ;

    cout << endl << " Cual de los siguientes archivos (Encriptados) desea leer?" << endl << endl ;
    cout << " Codificado.dat [0]" << endl ;
    cout << " Sudo.txt       [1]" << endl ;
    cout << " Usuario.dat    [2]" << endl ;
    cout << endl << " Su Opcion: " ;
    cin >> numero ;
    cout << endl ;


    switch( numero ){

        case 0 :

            nombre_archivo = "codificado.dat" ;

        break;

        case 1 :

            nombre_archivo = "sudo.txt" ;

        break;

        case 2 :

            nombre_archivo = "usuario.dat" ;

        break;

        default:

            cout << endl << " Algo salio mal, asi que por defecto se leera codificado.dat" << endl ;

            nombre_archivo = "codificado.dat" ;

        break;
    }

    archivo.open( nombre_archivo , ios::in | ios::ate | ios::binary );       //Abrimos el archivo en modo lectura y Binario

    if( archivo.is_open() ){

        tam  = archivo.tellg(); //Tamaño del archivo

    }
    else{

        cout << " El archivo NO se pudo abrir..." << endl ;

    }

    archivo.close();        //cerramos el archivo

    return tam ;

}



void contenido_binario( unsigned long long tam, int n ){

    try {

        char *arreglo = new char[ tam+1 ] ;

        int semilla = n ;

        ifstream archivo ;

        cout << endl << " Lo sentimos, pero debes elegir nuevamente el archivo que querias leer hace un momento..." << endl ;

        int numero ;

        string nombre_archivo ;

        cout << endl << " Cual de los siguientes archivos (Encriptados) desea leer?" << endl << endl ;
        cout << " Codificado.dat [0]" << endl ;
        cout << " Sudo.txt       [1]" << endl ;
        cout << " Usuario.dat    [2]" << endl ;
        cout << endl << " Su Opcion: " ;
        cin >> numero ;
        cout << endl ;


        switch( numero ){

            case 0 :

                nombre_archivo = "codificado.dat" ;

            break;

            case 1 :

                nombre_archivo = "sudo.txt" ;

            break;

            case 2 :

                nombre_archivo = "usuario.dat" ;

            break;

            default:

                cout << endl << " Algo salio mal, asi que por defecto se leera codificado.dat" << endl ;

                nombre_archivo = "codificado.dat" ;

            break;
        }

        archivo.open( nombre_archivo , ios::in | ios::binary );

        if( archivo.is_open() ){

            archivo.read(arreglo,tam+1);

            int *arreglo_ent = new int[tam*8] ;

            unsigned long long b ;

            int num ;

            //CONVERTIMOS DE CHAR A BIN

            for( unsigned long long i = 1 ; i <= tam ; i++ ){

                b = (i*8)-1 ;

                num = int(arreglo[i-1]) ;

                if( num < 0 ){

                    num = (( num +128 )+128) ;

                }

                for( int w = 0 ; w < 8 ; w++ ){

                    arreglo_ent[b] = num%2 ;

                    num = num/2 ;

                    b-- ;

                }


            }


            decodificacion_bin(arreglo_ent,semilla,tam*8);

            conversion_entero(arreglo_ent,tam*8);

            archivo.close();
            delete []arreglo_ent ;

        }
        else{

            cout << " El archivo NO se pudo abrir..." << endl ;
        }

        delete []arreglo ;

    }
    catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función contenido_binario() " << endl ;

    }

}



void decodificacion_bin( int *codif, int n, unsigned long long tam ){

    int semilla = n, unos = 0 , ceros = 0, cont1 = 1, cont2 = 1, g_ant0 = 0, g_ant1 = 0, cont3 = 1 ;

    for( unsigned long long i = 0 ; i < tam ; i++ ){

        if( cont1 <= semilla && cont2 == 1 ){   //Condicion unicamente para el primer gupo

            if( codif[i] == 0 ){

                codif[i] = 1 ;

                unos++;

            }else{          //el aumento de ceros y unos debe ser alreves ya que se debe contar la cantidad e 1s y 0s...
                                                                        //...pero del binario original
               codif[i] = 0 ;

               ceros++;

            }

            cont1++ ;

        }
        else if( g_ant0 > g_ant1 && cont2 > 1 ){    //Si hay mayor cantidad de CEROS

            if( cont3 == 2 ){

                if( codif[i] == 0 ){

                    codif[i] = 1 ;

                    unos++ ;
                }
                else{

                    codif[i] = 0 ;

                    ceros++ ;
                }

                cont3 = 1 ;
            }
            else{

                if( codif[i] == 0 ){    //Si No se modifica, se hace conteo sin intercambiar

                    ceros++ ;
                }
                else{
                   unos++ ;
                }

                cont3++ ;

            }

            cont1++ ;
        }
        else if( g_ant1 > g_ant0 && cont2 > 1 ){     //Si hay mayor cantidad de UNOS

            if( cont3 == 3 ){

                if( codif[i] == 0 ){

                    codif[i] = 1 ;

                    unos++ ;
                }
                else{

                    codif[i] = 0 ;

                    ceros++ ;
                }

                cont3 = 1 ;
            }
            else{

                if( codif[i] == 0 ){    //Si No se modifica, se hace conteo sin intercambiar

                    ceros++ ;
                }
                else{
                   unos++ ;
                }

                cont3++ ;

            }

            cont1++ ;
        }
        else if( g_ant0 == g_ant1 && cont2 > 1 ){

            if( codif[i] == 0 ){

                codif[i] = 1 ;

                unos++;

            }else{          //el aumento de ceros y unos debe ser alreves ya que se debe contar la cantidad e 1s y 0s...
                                                                        //...pero del binario original
               codif[i] = 0 ;

               ceros++;

            }

            cont1++ ;

        }


        if( cont1 > semilla ){  //Condicion para verificar y reiniciar contadores

           cont2++ ;

           cont1 = 1 ;

           cont3 = 1 ;

           g_ant0 = ceros ;

           g_ant1 = unos ;

           ceros = 0 ;

           unos = 0 ;

        }

    }//FIN CICLO
}



void conversion_entero( int *codif, unsigned long long tam ){

    unsigned long long nuevo_tam = tam/8 ; //Variable para saber el numero de caracter representados como int

    char *caracteres = new char[nuevo_tam+1] ;  //Generamos un arreglo que contendra los caracteres

    unsigned long long a = 0, b ;

    int pot = 7, rest = 0, mult ;

    for( unsigned long long i = 1 ; i <= nuevo_tam ; i++ ){     //Ciclo en el cual convertimos de binario a entero

        b = i*8 ;

        for(  ; a < b ; a++ ){

            mult = pow(2,pot);      //Potencias de 7 hasta 0 [base 2]

            rest = rest + mult*(codif[a]) ;

            pot--;
        }

        a = b ;

        pot = 7 ;

        caracteres[i-1] = char( rest ) ;        //De entero, convertimos a Char y obtenemos el caracter

        rest = 0 ;

    }

    escritura_decodificada( caracteres, nuevo_tam );

    delete []caracteres ;

}



void escritura_decodificada( char *decodif, unsigned long long nuevo_tam ){

    fstream archivo ;

    archivo.open( "natural.txt" , ios::out );

    if( archivo.is_open() ){

        char c ;

        for( unsigned long  long i = 0 ; i < nuevo_tam ; i++ ){

            c = decodif[i] ;

            archivo.put( c );

        }

        cout << endl << " [Contenido Decodificado en el archivo natural.txt]" << endl << endl ;
    }
    else{

        cout << " NO se pudo abrir el archivo..." << endl ;

    }
}
