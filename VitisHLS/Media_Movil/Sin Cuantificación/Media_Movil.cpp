// Código de la Media Movil con float (sin cuantifiacar)
// Joaquín Ramos García

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Media_Movil.h"

// Definicion de las variables globales
#define Nsamples	64 //Ventana de 64
#define Nshift		6 // log2(Nsamples)

//	Registro de desplazamiento para la ventana de 64
float shift_reg[Nsamples] = {0};//Se inicializa como un vector de 64 ceros

// RNC: Esta bien, pero para que sea más escalable vamos a trabajar con ventanas de 64 para obtener una sola muestra de salida. la entrada no puede ser const
void media_movil(float input[1], float output[1]) {

	float acumulado = 0;
	// RNC: Debemos definir la señal EMG_rectificada. No hace falta que sea un vector, porque usamos el valor y sobreescribimos. Así ahorramos memoria.
	float EMG_rectificada;
	//printf("input_in[%d] = %f\n\r", 0, input[0]);

	//Bucle con el registro de desplazamientos
	Bucle_Registro_Desplazamiento: for (int i = Nsamples - 1; i >= 0; i--) {
        if (i == 0) {
            shift_reg[0] = *input;
        } else {
            shift_reg[i] = shift_reg[i - 1];
        }
    }
	//printf("input_in[%d] = %f\n\r", 0, shift_reg[0]);//Print para saber que estaba haciendo bien el registro de desplazamiento
	// Bucle for
	Bucle_Media_Movil:for (int k=0; k < Nsamples; k++)
	{

		// RNC: Hacemos el valor absoluto de la señal.
		if(shift_reg[k] < 0){
			EMG_rectificada = -shift_reg[k];
		}else{
			EMG_rectificada = shift_reg[k];
		}
		// printf("EMG_rectificada = %f\n\r", EMG_rectificada);

		// RNC: se podría simplificar en una sola línea: acumulado += abs(input[k]);
		acumulado += EMG_rectificada;

	}

	// printf("acum = %f\n\r", acumulado);
	// RNC: La división está bien, pero al ser potencia de 2 puedes hacer un desplazamiento a la derecha para implementar la división.
	output[0] = acumulado / Nsamples;
	// output = (acumulado >> Nshift);

}
