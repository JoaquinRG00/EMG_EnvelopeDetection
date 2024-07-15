// Código de la Media Movil con ap_fixed (con cuantizacion)
// Joaquín Ramos García

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Media_Movil_Q.hpp"
#include "quant.hpp"


// Definicion de las variables globales
#define Nsamples	64 //Ventana de 64
#define Nshift		6 // log2(Nsamples)

//	Registro de desplazamiento para la ventana de 64
Q_data shift_reg_par[Nsamples/2] = {0};//Se inicializa como un vector de 32 ceros
Q_data shift_reg_impar[Nsamples/2] = {0};//Se inicializa como un vector de 32 ceros
//static Q_suma acumulado = 0;
// RNC: Esta bien, pero para que sea más escalable vamos a trabajar con ventanas de 64 para obtener una sola muestra de salida. la entrada no puede ser const
void media_movil(Q_data input[1], Q_data output[1]) {

	Q_suma_32 acumulado_par = 0;
	Q_suma_32 acumulado_impar = 0;
	Q_suma_64 acumulado = 0;
	// RNC: Debemos definir la señal EMG_rectificada. No hace falta que sea un vector, porque usamos el valor y sobreescribimos. Así ahorramos memoria.
	Q_data EMG_rectificada_par;
	Q_data EMG_rectificada_impar;
	//printf("input_in[%d] = %f\n\r", 0, input[0]);

	//Bucle con el registro de desplazamiento
	for_registro_desplazamiento_par:
	for (int i = Nsamples/2 - 1; i >= 0; i-=1) {
        if (i == 0) {
        	shift_reg_impar[0] = shift_reg_par[0];
            shift_reg_par[0] = *input;
        } else  {
        	shift_reg_impar[i] = shift_reg_par[i];
            shift_reg_par[i] = shift_reg_impar[(i - 1)];
        }
    }
	//printf("input_in[%d] = %f\n\r", 0, shift_reg[0]);//Print para saber que estaba haciendo bien el registro de desplazamiento
	// Bucle for
	//acumulado = 0;
	for_media_movil:for (int k=0; k < Nsamples/2; k++)
	{

		// Hacemos el valor absoluto de la señal, del registro de desplazamiento de indices pares
		if(shift_reg_par[k] < 0){
			EMG_rectificada_par = -shift_reg_par[k];
		}else{
			EMG_rectificada_par = shift_reg_par[k];
		}
		// Hacemos el valor absoluto de la señal, del registro de desplazamiento de indices pares
		if(shift_reg_impar[k] < 0){
			EMG_rectificada_impar = -shift_reg_impar[k];
		}else{
			EMG_rectificada_impar = shift_reg_impar[k];
		}
		acumulado_par += EMG_rectificada_par;
		acumulado_impar += EMG_rectificada_impar;
	}

	acumulado = acumulado_par+acumulado_impar;
	// printf("acum = %f\n\r", acumulado);
	//La división está bien, pero al ser potencia de 2 puedes hacer un desplazamiento a la derecha para implementar la división.
	output[0] = acumulado / Nsamples;
	// output = (acumulado >> Nshift);

}





