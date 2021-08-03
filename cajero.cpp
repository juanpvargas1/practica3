#include "cajero.h"

        //PROGRAMA PRINCIPAL

void Programa_principal(){

    int opcion, op2 ;

    bool seguir = true ;

    while( seguir == true ){

    cout << " ---BIENVENIDO---" << endl ;
    cout << endl << " *Que desea hacer?" << endl << endl ;
    cout << " Codificar      [0]" << endl ;
    cout << " Decodificar    [1]" << endl ;
    cout << " Usar el Cajero [2]" << endl ;
    cout << endl << " Su Opcion: " ;
    cin >> opcion ;
    cout << endl ;

    switch( opcion ){

        case 0 :{

        cout << endl << " --CODIFICACION--" << endl ;

        int metodo, semilla ;

        cout << endl << " *Que metodo de Encriptacion desea usar?" << endl << endl ;
        cout << " Metodo 1 [1]" << endl ;
        cout << " Metodo 2 [2]" << endl ;
        cout << endl << " Su Opcion: " ;
        cin >> metodo ;
        cout << endl ;

        cout << " Ingrese la semilla de Codificacion: " ;
        cin >> semilla ;
        cout << endl ;

        if( semilla > 0 ){

            switch( metodo ){

                case 1 :{

                    unsigned long long tam = 0 ;

                    tam = lectura_natural();

                    contenido_archivo( tam, semilla );

                    cout << endl << " [Encriptacion completada]" << endl ;

                }break;

                case 2 :{

                    unsigned long long tam = 0 ;

                    tam = lectura_natural();

                    contenido_archivo_strng( tam, semilla, 0 );

                    cout << endl << " [Encriptacion completada]" << endl ;

                }break;

                default:

                    cout << endl << " Metodo NO valido..." << endl ;

                break;

            }

        }
        else{

            cout << endl << " La semilla era un numero NO valido..." << endl ;
        }

        }break;

        case 1 :{

            cout << endl << " --DECODIFICACION--" << endl ;

            int metodo, semilla ;

            cout << endl << " *Que metodo de DESencriptacion desea usar?" << endl << endl ;
            cout << " Metodo 1 [1]" << endl ;
            cout << " Metodo 2 [2]" << endl ;
            cout << endl << " Su Opcion: " ;
            cin >> metodo ;
            cout << endl ;


            switch( metodo ){

                case 1 :{

                    cout << " Ingrese la semilla de DEcodificacion: " ;
                    cin >> semilla ;
                    cout << endl ;

                    unsigned long long tam = 0 ;

                    tam = lectura_binario();

                    contenido_binario( tam, semilla );

                    cout << endl << " [DESencriptacion completada]" << endl ;

                }break;

                case 2 :{

                    int semilla, metodo ;

                    metodo = pregunta_met2() ;

                    semilla = semilla_met2();

                    contenido_binario_met2( metodo, semilla );

                    cout << endl << " [DESencriptacion completada]" << endl ;

                }break;

                default:

                cout << endl << " Metodo NO valido..." << endl ;

                break;


            }

        }break;

        case 2 :{

            //APLICACION CAJERO

            cajero_exe();

        }break;

        default:

            cout << endl << " Por favor leea bien cuales son las opciones..." << endl ;

        break;

        }



    cout << endl << " Desea seguir usando el programa?" << endl << endl ;
    cout << "       Si [0] || No [1]" << endl ;
    cout << endl << "            R/: " ;
    cin >> op2 ;
    cout << endl ;

    if( op2 == 0 ){

      seguir = true ;
    }
    else{

      seguir = false ;
    }


    }

    cout << endl << " Hasta luego, vuelva pronto..." << endl << endl ;

}



        //CAJERO

void cajero_exe(){

    //Menu del cajero

    int opcion ;

    cout << " ---CAJERO.EXE---" << endl ;
    cout << endl << " *Que desea hacer?" << endl << endl ;
    cout << " Ingresar como Admin   [0]" << endl ;
    cout << " Ingresar como Usuario [1]" << endl ;
    cout << endl << " Su Opcion: " ;
    cin >> opcion ;
    cout << endl ;

    switch( opcion ){

        case 0 :{

            //Validacion clave admin

            bool verif ;

            verif = validacion_admin();

                if( verif == true ){

                    registro_usuario();

                }


        }break;

        case 1 :{

            //Validacion Usuario

            login_usuario();

        }break;

        default:

        cout << endl << " Opcion NO valida..." << endl ;

        break;

    }

    cout << endl << " [CERRANDO CAJERO]" << endl ;
}




        //FUNCIONES EXTRA PARA EL CAJERO


bool validacion_admin(){

    bool verificacion = false ;

    string clave, c_encriptada ;

    ifstream archivo ;

    cout << endl << " --AUTENTICACION--" << endl << endl ;
    cout << " Ingrese la contrasena de seguridad" << endl ;
    cout << endl << " Password: " ;
    cin >> clave ;

    cout << endl << " ------------------------------ " ;

    contenido_binario_met2( 1, 4 );

    archivo.open( "natural.txt", ios::in | ios::binary );

    if( archivo.is_open() ){

        char c ;
        while( !archivo.eof() ){

           c = archivo.get();

           if( int(c) >= 0 ){

             c_encriptada.push_back( c );
           }

        }

        //c_encriptada.pop_back();

        archivo.close();
        remove( "natural.txt" );        //Eliminamos el archivo ya que la clave queda ahi

    }
    else{

       cout << endl << " NO se pudo abrir el archivo..." << endl ;
    }



    if( clave == c_encriptada ){

        cout << endl << " Contrasena CORRECTA." << endl ;

        cout << " ------------------------------ " << endl ;

        verificacion = true ;
    }
    else{

        cout << endl << " Contrasena INCORRECTA." << endl ;

        cout << " ------------------------------ " << endl ;
    }

    return verificacion ;
}



void registro_usuario(){

    cout << endl << " --REGISTRO DE USUARIOS--" << endl << endl ;

    ofstream archivo, nat ;

    ifstream binarch ;

    string nuevo_usuario, id, clave, saldo, asignar ;

    archivo.open( "usuarios.dat", ios::app | ios::binary );

    if( archivo.is_open() ){

        bool verif ;

        do{

            cout << endl << " Ingrese la cedula del usuario: " ;
            cin >> id ;

            verif = verif_id( id ) ;

            if( verif == false ){

               cout << endl << " Usuario ya existente..." << endl ;
            }

        }while( verif == false );

        cout << endl << " Ingrese la clave del usuario: " ;
        cin >> clave ;

        cout << endl << " Ingrese el saldo del usuario: " ;
        cin >> saldo ;
        cout << endl ;

        nuevo_usuario = id + "," + clave + "," + saldo + ':' ;

        //Encriptar info nuevo usuario

        nat.open( "natural.txt", ios::out );

        nat << nuevo_usuario ;

        nat.close();

        unsigned long long t = 0 ;

        t = lectura_natural();

        contenido_archivo_strng(t,4,0);

        remove("natural.txt");

        unsigned long long cont = 0;

        binarch.open( "codificado.dat", ios::in | ios::binary );

        while( cont < t ){

            asignar.push_back( binarch.get());
            cont++;
        }

        binarch.close();

        archivo << asignar ;

    }
    else{

       cout << " El archivo NO se pudo abrir..." << endl ;
    }

    archivo.close();

}



bool verif_id( string id ){

    bool verif ;

    ifstream archivo ;

    string datos ;

    contenido_binario_met2( 2 , 4 );

    archivo.open( "natural.txt", ios::in );

    while( !archivo.eof() ){

        datos.push_back( archivo.get() ) ;

    }

    int clave ;

    clave = datos.find( id );

    if( clave < 0 ){        //No lo encontro

       verif = true ;
    }
    else{

        verif = false ;     //lo encontro
    }

    archivo.close();

    remove( "natural.txt" );

    return verif ;
}



void login_usuario(){

    bool veri_usuario ;

    string id, pass ;

    cout << endl << " --Login--" << endl << endl ;

    cout << " Ingrese su ID: " ;
    cin >> id ;
    cout << endl ;

    veri_usuario = verif_id( id );

    if( veri_usuario == false ){

        bool v_pass ;

        do{

            cout << endl << " Ingrese su password: " ;
            cin >> pass ;
            cout << endl ;

            v_pass = verif_pass( pass, id );


        }while( v_pass == false );

        cout << endl << " ---------------------" << endl ;
        cout << "      ACCEDIENDO" ;
        cout << endl << " ---------------------" << endl ;

        //Si efectivamente ingresa...

        int opcion_usuario ;

        cout << endl << " *Que desea hacer?" << endl << endl ;
        cout << " Consultar mi Saldo   [0]" << endl ;
        cout << " Retirar Dinero       [1]" << endl ;
        cout << endl << " Su Opcion: " ;
        cin >> opcion_usuario ;
        cout << endl ;

        //Funcion para realizar las operaciones

        funciones_usuario( id, opcion_usuario );

    }
    else{

        cout << endl << " ---------------------" << endl ;
        cout << " Usuario NO REGISTRADO" ;
        cout << endl << " ---------------------" << endl ;
    }

}



unsigned long pos_verif_id( string id ){

    unsigned long verif ;

    ifstream archivo ;

    string datos ;

    contenido_binario_met2( 2 , 4 );

    archivo.open( "natural.txt", ios::in );

    while( !archivo.eof() ){

        datos.push_back( archivo.get() ) ;

    }

    verif = datos.find( id );

    archivo.close();

    remove( "natural.txt" );

    return verif ;
}



bool verif_pass( string password, string id ){

    bool verif ;

    unsigned long pos ;

    pos = pos_verif_id( id );

    ifstream archivo ;

    string datos ;

    contenido_binario_met2( 2 , 4 );

    archivo.open( "natural.txt", ios::in );

    while( !archivo.eof() ){

        datos.push_back( archivo.get() ) ;

    }

    int pass, ste_coma, inicio ;

    pass = datos.find( password, pos );

    if( pass < 0 ){     //Incorrecta

        verif = false ;

        cout << endl << " ---------------------" << endl ;
        cout << " Password INCORRECTA" ;
        cout << endl << " ---------------------" << endl ;
    }
    else{

       ste_coma = datos.find( "," , pass );

       inicio = pass ;

       string confirmar_clave ;

       char c;

       for(  ; inicio < ste_coma ; inicio++ ){

          c = datos[inicio];

          confirmar_clave.push_back(c);
       }

       if( confirmar_clave == password ){

          verif = true ;       //Correcta
       }
       else{

           verif = false ;
           cout << endl << " ---------------------" << endl ;
           cout << " Password INCORRECTA" ;
           cout << endl << " ---------------------" << endl ;
       }
    }

    archivo.close();
    remove( "natural.txt" );

    return  verif ;
}



void funciones_usuario( string id, int modo ){

    switch( modo ){

        case 0 :{       //Consultar saldo

        mi_saldo( id, 0 );

        }break;


        case 1 :{       //Retirar dinero

        mi_saldo( id, 1 );

        }break;

        default:

        cout << endl << " Opcion NO valida..." << endl ;

        break;

    }


}



void mi_saldo( string id, int n ){

    unsigned long p_usuario ;

    p_usuario = pos_verif_id( id );

    ifstream archivo ;

    string datos, platica ;

    contenido_binario_met2( 2 , 4 );

    archivo.open( "natural.txt", ios::in );

    while( !archivo.eof() ){

        datos.push_back( archivo.get() ) ;

    }

    archivo.close();

    int saldo_pos, separador, cont = 0, p_sald, resta ;

    separador = datos.find( ":" , p_usuario );

    saldo_pos = datos.find_last_of( "," , separador );

    resta = separador - saldo_pos ; //tamaño del saldo

    char c ;

    p_sald = saldo_pos+1 ;

    for( ; p_sald < separador ; p_sald++ ){

        c = datos[p_sald] ;
        platica.push_back(c);
        cont++ ;
    }

    long long int dinero ;

    dinero = dinero_int( platica );

    if( n == 0 ){       //Opcion consulta

        cout << endl << " *Recuerde que se le cobraran 1000$ por cada consulta*" << endl ;
        cout << endl << " ---------------------" << endl ;
        cout << endl << " Su saldo es de: " << platica << " [COP] " << endl ;
        cout << endl << " ---------------------" << endl ;

        //Se cobra la cuota de 1000 [cop]

        dinero = dinero - 1000 ;

        if( dinero < 0 ){

            dinero = 0 ;
        }

    }
    else if( n == 1 ){  //Opcion Retirar

        long long int monto, dinero_pregunta ;

        do{

            dinero_pregunta = dinero ;

            cout << endl << " *Cuanto desea Retirar?" << endl << endl ;
            cout << endl << " *Recuerde que se le cobraran 1000$ por cada retiro*" << endl ;
            cout << endl << "  Monto [COP]: " ;
            cin >> monto ;
            cout << endl ;

            dinero_pregunta = dinero_pregunta - (monto + 1000) ;

            if( dinero_pregunta < 0 ){

               cout << endl << " --NO HAY DINERO SUFICIENTE--"  << endl ;
            }

        }while( dinero_pregunta < 0 );

        //Se realiza el retiro

        dinero = dinero - (monto + 1000) ;

    }

    //reemplazamos el nuevo dinero en el arreglo datos

    string plata_chr ;

    plata_chr = to_string(dinero);

    datos.replace( saldo_pos+1, resta-1 , " " );

    datos.erase( saldo_pos+1, 1);

    datos.insert( saldo_pos+1, plata_chr );

    datos.pop_back();

    //Escribimos los datos actualizados en el archivo natural
    //para luego codificarlos y escribirlos en usuarios.dat

    ofstream escribir_archivo ;

    escribir_archivo.open( "natural.txt", ios::out );

    escribir_archivo << datos ;

    escribir_archivo.close();

    unsigned long long tam_a = 0 ;

    tam_a = lectura_natural();

    contenido_archivo_strng( tam_a, 4, 1 );

}



long long int dinero_int( string plata ){

    long long int money = 0 ;

    int conversion ;

    char c ;

    for( unsigned int i = 0 ; i < plata.length() ; i++ ){

        c = plata[i] ;

        conversion = int( c ) - 48 ;

        money = ( money*10 ) + conversion ;
    }

    return money ;
}
