// Código de la RMS con ap_fixed (con cuantización)
// Joaquín Ramos García
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "quant.hpp"
#include "RMS_Q.hpp"



//	Registro de desplazamiento para la ventana de 64
Q_data  shift_reg[Nsamples] = {0};//Se inicializa como un vector de 64 ceros
static Q_suma acumulado = 0;
static Q_data reg_loop = 0;
//Creación de la función RMS

void RMS(Q_data  input[1], Q_data  output[1]) {

	//Bucle con el registro de desplazamientos
	Loop_registro_desp: for (int i = Nsamples - 1; i >= 0; i--) {
		if (i == 0) {
			shift_reg[0] = input[0];
	    } else {
	        shift_reg[i] = shift_reg[i - 1];
	    }
	 }
	//printf("input_in[%d] = %f\n\r", 0, shift_reg[0]);//Print para saber que estaba haciendo bien el registro de desplazamiento

	acumulado = 0;
	// Bucle for
	Loop_product: for (int k=0; k < Nsamples; k++)
	{
		reg_loop = shift_reg[k];
		Q_data EMG_product = (Q_data)((Q_product)(reg_loop*reg_loop));
		acumulado += EMG_product;

	}

	//output[0] = sqrt(static_cast<double>(acumulado) / Nsamples);

	output[0] = (Q_data)((acumulado) / Nsamples);
	//output[0] = (acumulado) / Nsamples;
	//output[0] = sqrt(acumulado / Nsamples);
	// output = (acumulado >> Nshift);

}
