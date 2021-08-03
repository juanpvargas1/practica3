#include "extra2.h"

        //FUNCIONES PARA EL CODIFICADO POR EL METODO 2 [con string]

void contenido_archivo_strng( unsigned long long tam, int n, int archivo_num ){

    try{
        unsigned long long cont = 0 ;

        ifstream archivo ;

        string texto ;

        archivo.open( "natural.txt", ios::in );

        if( archivo.is_open() ){

            while( !archivo.eof() ){

                texto.push_back( archivo.get() ) ;      //Obtenemos los datos del archivo
                cont++ ;
            }

            tam = cont-1 ;

            //Convertimos de char a binario

            if( tam > 0 ){

                convertir_chr2bin_strng( tam, n, texto, archivo_num );
            }

            archivo.close();

        }

    }catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función contenido_archivo_strng() " << endl ;

    }

}



void convertir_chr2bin_strng( unsigned long long tam, int n, string texto, int archivo_num ){

    try {

        string binarios[tam*8] ;        //String que contiene  el contenido del archivo pero en binario

        string codif ;      //creamos un nuevo string para almacenar posteriormente lo que habra en binarios

        unsigned long long b ;

        int num ;

        char c ;

        for( unsigned long long i = 1 ; i <= tam ; i++ ){

            b = i*8 ;

            num = int( texto[i-1] ) ;

            if( num < 0 ){

                tam-- ;
                num = 0 ;   //Caracter nulo
            }

            for( int k = 0 ;  k < 8 ; k++ ){

                c = char( (num%2)+48 );     //Convertimos de entero a char y lo almacenamos en binarios

                binarios[b-1] = c ;

                num = num/2 ;

                b-- ;
            }

        }

        //Codificamos el contenido de Binarios

        for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){    //Rellenamos un nuevo string con lo que habia en binarios

            codif.append( binarios[i] );
        }

        codificacion_met2( tam, n, codif, archivo_num );

    }
    catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función convertir_chr2bin_strng() " << endl ;
    }


}



void codificacion_met2( unsigned long long tam, int n, string binarios, int archivo_num ){

    char n1, n2 ;

    int x, cont1 = 1 ;

    for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){        //Ciclo para recorrer el arreglo binarios entero

        if( cont1 == 1 ){

            x = i ;     //Coordenada inicial de cada grupo

            cont1++ ;
        }
        else if( cont1 > 1 ){

            if( cont1 == n ){

                n1 = binarios[i] ;

                binarios[i] = binarios[x] ;  //Cambiamos lo que halla en la ultima pos por lo que hay la inicial

                binarios[x] = n1 ;      //Ubicamos lo que habia en la inical por lo que hay en la ultima

            }
            else{

                n1 = binarios[x] ;      //Guardamos el inicial

                n2 = binarios[i] ;      //Guardamos el Actual

                binarios[i] = n1 ;      //LLevamos a la pos actual lo que hay en la inicial

                binarios[x] = n2 ;      //Llevamos a la pos inicial lo que habia en la actual

            }

            cont1++ ;
        }


        if( cont1 > n ){        //Reiniciamos el contador 1

           cont1 = 1 ;
        }

    }


    //Re-convertimos a char y guardamos como binario

    escritura_met2_strng(tam, binarios, archivo_num );

}



void escritura_met2_strng( unsigned long long tam, string codificado, int archivo_num ){

    string bin2chr ;

    char c ;

    int inicial = 0, pot = 7, rest = 0, mult, num ;

    for( unsigned long long i = 1 ; i <= tam ; i++ ){

        for( int k = 0 ; k < 8 ; k++ ){

           num = int( codificado[inicial] ) - 48 ;

           mult = pow(2,pot);

           rest = rest + mult*( num );

           inicial++ ;

           pot-- ;
        }

        c = char(rest);

        bin2chr.push_back(c);

        pot = 7 ;

        inicial = i*8 ;

        rest = 0 ;
    }


    //AHORA ESCRIBIMOS EN BINARIO

    fstream archivo ;

    string nombre_arch ;

    switch( archivo_num ){

    case 0 :{
     nombre_arch = "codificado.dat" ;
    }break;

    case 1 :{
      nombre_arch = "usuarios.dat" ;
    }break;

    default:
      nombre_arch = "codificado.dat" ;
    break;

    }

    archivo.open( nombre_arch , ios::out | ios::binary );

    if( archivo.is_open() ){

        archivo << bin2chr ;

    }
    else{

        cout << " NO se pudo abrir el archivo..." << endl ;
    }

    archivo.close();

}




        //FUNCIONES PARA EL CODIFICADO POR EL METODO 2 [con string]

int pregunta_met2(){

    int numero ;

    cout << endl << " Cual de los siguientes archivos (Encriptados) desea leer?" << endl << endl ;
    cout << " Codificado.dat [0]" << endl ;
    cout << " Sudo.txt       [1]" << endl ;
    cout << " Usuario.dat    [2]" << endl ;
    cout << endl << " Su Opcion: " ;
    cin >> numero ;
    cout << endl ;

    return numero ;
}


int semilla_met2(){

    int n ;

    cout << endl << " Ingrese la semilla de Decodificacion: " ;
    cin >> n ;
    cout << endl ;

    return  n;
}


void contenido_binario_met2( int numero, int n ){

    try{

        unsigned long long cont = 0, tam = 0 ;

        ifstream archivo ;

        string conte_codif ;

        string nombre_archivo ;

        switch( numero ){

            case 0 :

                nombre_archivo = "codificado.dat" ;

            break;

            case 1 :

                nombre_archivo = "sudo.txt" ;

            break;

            case 2 :

                nombre_archivo = "usuarios.dat" ;

            break;

            default:

                cout << endl << " Algo salio mal, asi que por defecto se leera codificado.dat" << endl ;

                nombre_archivo = "codificado.dat" ;

            break;
        }

        archivo.open( nombre_archivo, ios::in | ios::binary );

        if( archivo.is_open() ){

            while( !archivo.eof() ){

                conte_codif.push_back( archivo.get() ) ;      //Obtenemos los datos del archivo
                cont++;
            }

            tam = cont - 1 ;

            //Convertimos de char a binario para poder Decodificar

            if( tam > 0 ){

                conversion_chr2bin_decodif( tam, n, conte_codif );
            }

            archivo.close();
        }
        else{

            cout << endl << " NO se pudo abrir el archivo..." << endl ;
        }

    }
    catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función contenido_binario_met2() " << endl ;
    }

}



void conversion_chr2bin_decodif( unsigned long long tam, int n, string codif ){

    try{

        string binarios[tam*8] ;

        string arr_bin ;

        unsigned long long b ;

        int num ;

        char c ;

        for( unsigned long long i = 1 ; i <= tam ; i++ ){

            b = i*8 ;

            num = int( codif[i-1] ) ;

            if( num < 0 ){

                num = (( num +128 )+128) ;

            }

            for( int k = 0 ;  k < 8 ; k++ ){

                c = char( (num%2)+48 );     //Convertimos de entero a char y lo almacenamos en binarios

                binarios[b-1] = c ;

                num = num/2 ;

                b-- ;
            }

        }


        //Rellenamos un nuevo string con los numeros binarios para poderlo pasar en una funcion

        for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){    //Rellenamos un nuevo string con lo que habia en binarios

            arr_bin.append( binarios[i] );
        }

        //Ahora pasamos el arreglo para que pueda ser Decodificado

        decodificacion_met2( tam, n, arr_bin );

    }
    catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función conversion_chr2bin_decodif() " << endl ;

    }



}



void decodificacion_met2( unsigned long long tam, int n, string codif ){

    int cont = 1, x ;

    char n1, n2 ;

    for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){


        if( cont == 1 ){

            x = i ;         //Posicion inicial de cada grupo

            cont++ ;

        }
        else if( cont > 1 ){

           n1 = codif[x] ;

           n2 = codif[i] ;

           codif[i] = n1 ;

           codif[x] = n2 ;

           x = i ;

           cont++ ;

        }


        if( cont > n ){     //Reiniciamos las variables

            cont = 1 ;

        }

    }



    //Re-convertimos a char y guardamos como txt para ver si todo salio bien

    escritura_met2_decodif( tam, codif );

}


void escritura_met2_decodif( unsigned long long tam, string decodif ){

    try{

        string bin2chr ;

        char c ;

        int inicial = 0, pot = 7, rest = 0, mult, num ;

        for( unsigned long long i = 1 ; i <= tam ; i++ ){

            for( int k = 0 ; k < 8 ; k++ ){

               num = int( decodif[inicial] ) - 48 ;

               mult = pow(2,pot);

               rest = rest + mult*( num );

               inicial++ ;

               pot-- ;
            }

            c = char(rest);

            bin2chr.push_back(c);

            pot = 7 ;

            inicial = i*8 ;

            rest = 0 ;
        }


        //Ahora escribimos en un archivo.txt para verificar si todo salio bien

        fstream archivo ;

        archivo.open( "natural.txt" , ios::out );

        if( archivo.is_open() ){

            archivo << bin2chr ;

            //cout << endl << " [Contenido Decodificado en el archivo natural.txt]" << endl << endl ;

        }
        else{

            cout << " NO se pudo abrir el archivo..." << endl ;
        }

        archivo.close();

    }catch(...){

        cout << endl << " Ocurrio un problema de excepcion en la función escritura_met2_decodif() " << endl ;

    }


}


