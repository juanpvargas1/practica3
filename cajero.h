#ifndef CAJERO_H
#define CAJERO_H

#include "extra2.h"

//Programa Principal

void Programa_principal();


   //CAJERO

void cajero_exe();


   //FUNCIONES EXTRA PARA EL CAJERO

bool validacion_admin();

void registro_usuario();

bool verif_id( string id );

void login_usuario();

unsigned long pos_verif_id( string id );

bool verif_pass( string password, string id );

void funciones_usuario( string id, int modo );

void mi_saldo( string id, int n );

long long int dinero_int( string plata );


#endif // CAJERO_H
