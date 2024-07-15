// Código del TKEO con float (sin cuantifiacar)
// Joaquín Ramos García

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TKEO.h"

//Creación de la función


void TKEO(float input[1], float output[1]) {

	static float prev_input_1 = 0;
	static float prev_input_2 = 0;

	output[0]= 4*((prev_input_1*prev_input_1)-(prev_input_2*input[0]));

	prev_input_2 = prev_input_1;
	prev_input_1 = input[0];

}
