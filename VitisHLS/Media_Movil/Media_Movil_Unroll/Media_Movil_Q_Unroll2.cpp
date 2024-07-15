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
Q_data shift_reg_1[Nsamples/4] = {0};//Se inicializa como un vector de 16 ceros
Q_data shift_reg_2[Nsamples/4] = {0};//Se inicializa como un vector de 16 ceros
Q_data shift_reg_3[Nsamples/4] = {0};//Se inicializa como un vector de 16 ceros
Q_data shift_reg_4[Nsamples/4] = {0};//Se inicializa como un vector de 16 ceros
//static Q_suma acumulado = 0;
// RNC: Esta bien, pero para que sea más escalable vamos a trabajar con ventanas de 64 para obtener una sola muestra de salida. la entrada no puede ser const
void media_movil(Q_data input[1], Q_data output[1]) {

	Q_suma_16 acumulado_1 = 0;
	Q_suma_16 acumulado_2 = 0;
	Q_suma_16 acumulado_3 = 0;
	Q_suma_16 acumulado_4 = 0;
	Q_suma_64 acumulado = 0;
	// RNC: Debemos definir la señal EMG_rectificada. No hace falta que sea un vector, porque usamos el valor y sobreescribimos. Así ahorramos memoria.
	Q_data EMG_rectificada_1;
	Q_data EMG_rectificada_2;
	Q_data EMG_rectificada_3;
	Q_data EMG_rectificada_4;
	//printf("input_in[%d] = %f\n\r", 0, input[0]);

	//Bucle con el registro de desplazamiento
	for_registro_desplazamiento_par:
	for (int i = Nsamples/4 - 1; i >= 0; i-=1) {
        if (i == 0) {
        	shift_reg_4[0] = shift_reg_3[0];
        	shift_reg_3[0] = shift_reg_2[0];
        	shift_reg_2[0] = shift_reg_1[0];
        	shift_reg_1[0] = *input;
        } else  {
        	shift_reg_4[i] = shift_reg_3[i];
        	shift_reg_3[i] = shift_reg_2[i];
        	shift_reg_2[i] = shift_reg_1[i];
        	shift_reg_1[i] = shift_reg_4[(i - 1)];
        }
    }
	//printf("input_in[%d] = %f\n\r", 0, shift_reg[0]);//Print para saber que estaba haciendo bien el registro de desplazamiento
	// Bucle for
	//acumulado = 0;
	for_media_movil:for (int k=0; k < Nsamples/4; k++)
	{

		// Hacemos el valor absoluto de la señal, del registro de desplazamiento 1
		if(shift_reg_1[k] < 0){
			EMG_rectificada_1 = -shift_reg_1[k];
		}else{
			EMG_rectificada_1 = shift_reg_1[k];
		}
		// Hacemos el valor absoluto de la señal, del registro de desplazamiento 2
		if(shift_reg_2[k] < 0){
			EMG_rectificada_2 = -shift_reg_2[k];
		}else{
			EMG_rectificada_2 = shift_reg_2[k];
		}
		// Hacemos el valor absoluto de la señal, del registro de desplazamiento 3
		if(shift_reg_3[k] < 0){
			EMG_rectificada_3 = -shift_reg_3[k];
		}else{
			EMG_rectificada_3 = shift_reg_3[k];
		}
		// Hacemos el valor absoluto de la señal, del registro de desplazamiento 4
		if(shift_reg_4[k] < 0){
			EMG_rectificada_4 = -shift_reg_4[k];
		}else{
			EMG_rectificada_4 = shift_reg_4[k];
		}
		acumulado_1 += EMG_rectificada_1;
		acumulado_2 += EMG_rectificada_2;
		acumulado_3 += EMG_rectificada_3;
		acumulado_4 += EMG_rectificada_4;
	}

	acumulado = acumulado_1+acumulado_2+acumulado_3+acumulado_4;
	// printf("acum = %f\n\r", acumulado);
	//La división está bien, pero al ser potencia de 2 puedes hacer un desplazamiento a la derecha para implementar la división.
	output[0] = acumulado / Nsamples;
	// output = (acumulado >> Nshift);

}





