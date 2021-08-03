#ifndef EXTRA2_H
#define EXTRA2_H

#include "extra.h"

//FUNCIONES PARA EL CODIFICADO POR EL METODO 2 [string]

void contenido_archivo_strng( unsigned long long tam, int n, int archivo_num );

void convertir_chr2bin_strng( unsigned long long tam, int n, string texto, int archivo_num );

void codificacion_met2( unsigned long long tam, int n, string binarios, int archivo_num );

void escritura_met2_strng( unsigned long long tam, string codificado, int archivo_num );


   //Funciones para el DECODIFICADO con el metodo 2 [String]


int pregunta_met2();

int semilla_met2();

void contenido_binario_met2( int numero, int n );

void conversion_chr2bin_decodif( unsigned long long tam, int n, string codif );

void decodificacion_met2( unsigned long long tam, int n, string codif );

void escritura_met2_decodif( unsigned long long tam, string decodif );

#endif // EXTRA2_H
