/**************************************************************
· file   quant.hpp
· author Joaquín Ramos
· date   12/02/2024
· description:
	Cuantización de los datos uilizados en el algoritmo TKEO
*************************************************************/
#include <ap_fixed.h>
#ifndef QUANT_H
#define QUANT_H

/*
// Cuantización de datos normales, como los datos de entrada al algoritmo
#define Q_data_total 24 //Tamaño total del dato 24 bits
#define Q_data_entero 1 //Tamaño de la parte entera del dato
#define Q_data_fraccion 23 //Tamaño de la parte entera del dato
typedef ap_fixed<Q_data_total, Q_data_entero, AP_RND_CONV, AP_SAT, Q_data_fraccion> Q_data;*/

// Cuantización de datos normales, como los datos de entrada al algoritmo
#define Q_data_total 24 //Tamaño total del dato 24 bits
#define Q_data_entero 1 //Tamaño de la parte entera del dato
typedef ap_fixed<Q_data_total, Q_data_entero, AP_RND_CONV, AP_SAT, 1> Q_data;

#define Q_suma_total 24+6
#define Q_suma_entero 1+6
typedef ap_fixed<Q_suma_total, Q_suma_entero, AP_RND_CONV, AP_SAT, 1> Q_suma;


#define Q_product_total 24+24
#define Q_product_entero 1+1
typedef ap_fixed<Q_product_total, Q_product_entero, AP_RND_CONV, AP_SAT, 1> Q_product;


// En la RMS este no se utiliza
#define Q_out_total 24+2
#define Q_out_entero 1+2
typedef ap_fixed<Q_out_total, Q_out_entero, AP_RND_CONV, AP_SAT, 1> Q_out;

#endif
