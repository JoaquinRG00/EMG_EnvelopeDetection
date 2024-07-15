// C�digo del TKEO con float (sin cuantifiacar)
// Joaqu�n Ramos Garc�a

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "TKEO_Q.hpp"
#include "quant.hpp"

/*
//TKEO 1 (Desglosado)
void TKEO(Q_data input[1], Q_out output[1]) {
//#pragma HLS PIPELINE

	static Q_data prev_input_1 = 0;
	static Q_data prev_input_2 = 0;

	//Cuantizaci�n de la operacion  de la muestra k al cuadrado
	Q_product EMG_sqrt_1 = prev_input_1*prev_input_1;
	//Q_product EMG_sqrt_1 = (Q_product)(prev_input_1*prev_input_1);
	Q_data EMG_sqrt_2= EMG_sqrt_1;

	//Cuantizaci�n de la operacion  de la muestra k-1 * k+1
	Q_product EMG_produc_1 = prev_input_2*input[0];
	Q_data EMG_produc_2= EMG_produc_1;

	//Cuantizaci�n de la resta
	Q_suma EMG_resta_1 = EMG_sqrt_2 - EMG_produc_2;
	Q_data EMG_resta_2= EMG_resta_1;

	//C�lculo de la salida y Cuantizaci�n de la salida
	output[0] = (EMG_resta_2 << 2);

	//Actualizaci�n de los valores
	prev_input_2 = prev_input_1;
	prev_input_1 = input[0];

}*/

//TKEO 2 (Compcto)
void TKEO(Q_data input[1], Q_out output[1]) {
//#pragma HLS PIPELINE

	static Q_data prev_input_1 = 0;
	static Q_data prev_input_2 = 0;

	//Cuantizaci�n de la operacion  de la muestra k al cuadrado
	Q_data EMG_sqrt = (Q_data)((Q_product)(prev_input_1*prev_input_1));

	//Cuantizaci�n de la operacion  de la muestra k-1 * k+1
	Q_data EMG_product = (Q_data)((Q_product)(prev_input_2*input[0]));

	//C�lculo de la salida y Cuantizaci�n de la salida
	output[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt - EMG_product))));


	//Actualizaci�n de los valores
	prev_input_2 = prev_input_1;
	prev_input_1 = input[0];

}
