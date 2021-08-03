#ifndef EXTRA_H
#define EXTRA_H

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//Funciones extras o adicionales para el funcionanmiento del programa


   //FUNCIONES PARA EL CODIFICADO POR EL METODO 1

unsigned long long lectura_natural();        //Funcion que lee el archivo y retorna el tamaño del archivo

void contenido_archivo( unsigned long long tam, int n );

void conversion_entero( unsigned long long tam, char *arreglo, int n );

void escritura_bin_met1( int **arb, unsigned long long tam );

void codif_met1_chr( int **arb, int n, unsigned long long tam );


//Funciones para el DECODIFICADO con el metodo 1

unsigned long long lectura_binario();

void contenido_binario( unsigned long long tam, int n );

void decodificacion_bin( int *codif, int n, unsigned long long tam );

void conversion_entero( int *codif, unsigned long long tam );

void escritura_decodificada( char *decodif, unsigned long long tam );//Prueba de que todo salio bien





#endif // EXTRA_H
