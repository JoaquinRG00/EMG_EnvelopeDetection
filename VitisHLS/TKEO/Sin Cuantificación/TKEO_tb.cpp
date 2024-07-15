//Test Bench de la RMS
//C�digo de la RMS con float (sin cuantifiacar)
//Joaqu�n Ramos Garc�a

#include "stdio.h"
#include "TKEO.h" // Se declara el archivo que se va a simular. RNC: S�, pero lo tienes que crear, porque s�lo as� no funciona.
#include <math.h>

// RNC: Esto est� bien, pero necesitamos dos cosas m�s:
	// 1- Definir las muestras de entrada para probar nuestra funci�n. Pero tambi�n la salida (patr�n de oro) que obtenemos de matlab.
float in_real[] = {
	#include "Datain_TKEO.txt"
};

float out_gold[] = {
	#include "Dataout_TKEO.txt"
};
	// 2- Ajustar este main, como hab�as hecho en la Media_movil para que vaya pasando 64 muestras a la funci�n. En este punto puedes utilizas las funciones de imprimir sin problema.

float output[9140];

int main(void)
{
	int fin = sizeof(in_real) / sizeof(in_real[0]);
	printf("N_Vectors = %d\n\r", fin);
	printf("N_loops = %d\n\r", fin/Nsamples);
	printf("N_outputs = %lld\n\r", sizeof(out_gold)/sizeof(out_gold[0]));

	for (int i = 0; i < fin; i++)
	{
		// printf("input[%d] = %f\n\r", i*Nsamples, in_real[i*Nsamples]);
		TKEO(&in_real[i], &output[i]);
	}

	// 3- Ahora contrastamos lo que nos ha salido del algoritmo en C con lo que sale en Matlab. En este caso de forma visual
	for (int i = 0; i < sizeof(out_gold)/sizeof(out_gold[0]); i++)
	{
		printf("outputC = %f | outputG = %f | error = %f\n\r", output[i], out_gold[i], (out_gold[i]-output[i]));
	}

	// 3- Tambi�n podemos contrastar de forma autom�tica la salida
	for (int i = 0; i < sizeof(out_gold)/sizeof(out_gold[0]); i++)
	{
		if ((out_gold[i] - output[i]) > 0.0000001){
			printf("ERROR %d: outputC = %f | outputG = %f | error = %f\n\r", i, output[i], out_gold[i], (out_gold[i]-output[i]));
		}else{
			printf("Filtrado correcto \n\r");
		}
	}

}
