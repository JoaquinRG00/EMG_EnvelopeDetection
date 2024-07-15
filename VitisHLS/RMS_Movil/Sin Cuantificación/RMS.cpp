// Código de la RMS con float (sin cuantifiacar)
// Joaquín Ramos García

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "RMS.h"

//	Registro de desplazamiento para la ventana de 64
float shift_reg[Nsamples] = {0};//Se inicializa como un vector de 64 ceros

//Creación de la función RMS

void RMS(float input[1], float output[1]) {


	float acumulado = 0;
	//Bucle con el registro de desplazamientos
	for (int i = Nsamples - 1; i >= 0; i--) {
		if (i == 0) {
			shift_reg[0] = *input;
	    } else {
	        shift_reg[i] = shift_reg[i - 1];
	    }
	 }
	//printf("input_in[%d] = %f\n\r", 0, shift_reg[0]);//Print para saber que estaba haciendo bien el registro de desplazamiento


	// Bucle for
	for (int k=0; k < Nsamples; k++)
	{

		// RNC: se podría simplificar en una sola línea: acumulado += abs(input[k]);
		acumulado += (shift_reg[k]*shift_reg[k]);

	}

	// printf("acum = %f\n\r", acumulado);
	// RNC: La división está bien, pero al ser potencia de 2 puedes hacer un desplazamiento a la derecha para implementar la división.
	output[0] = sqrt(acumulado / Nsamples);
	// output = (acumulado >> Nshift);

}
