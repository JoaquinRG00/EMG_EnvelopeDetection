// Código del TKEO con float (sin cuantifiacar)
// Joaquín Ramos García

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "TKEO_Q_8C.hpp"
#include "quant.hpp"
#include <iostream>

//TKEO 2 (Compcto)
void TKEO(int32_t input[9], Q_out output_C1[1], Q_out output_C2[1], Q_out output_C3[1], Q_out output_C4[1], Q_out output_C5[1], Q_out output_C6[1], Q_out output_C7[1], Q_out output_C8[1]) {
	/*
	//Codigo para visualizar que se quita el status_word para no procesarlo
	uint32_t status_word = 0x000C0000;
	if (input[0] == status_word){
		printf("El status_word no se procesa \n");
	}*/
	//printf("Canal 1: %d\n", input[1]);
	//Inicializo las variables necesarias para el algoritmo
	int32_t input_real[8]={0};
	Q_data EMG_raw[8]=0;
	static Q_data prev_input_1[8] = 0;
	static Q_data prev_input_2[8] = 0;
	Q_data EMG_sqrt[8] = 0;
	Q_data EMG_product[8] = 0;
	//Bucle for de 0 a 7 para procesar los 8 canales de entrada
	//El indice k represenata a cada uno de los canales que se quiere procesar
	for(int k=0; k < 8; k++ ){
		//Obtención de solamente el dato de EMG a partir del dato TL_Data
		input_real[k] = ((input[k+1] ) & 0xFFFFFF);//Se guarda cada canal del input en un array de 8 valores
		// EMG_raw[k]= (Q_data)(input_real[k]);
		// EMG_raw[k]= (Q_data)((input_real[k])); // Q_total - Q_entero
		EMG_raw[k]= (Q_data)(((input[k+1] ) & 0xFFFFFF)); // Q_total - Q_entero

		//std::cout << "TL_Data del canal" << k+1 << ": " << input[k+1] << "\n";
		/*std::cout << "Dato original 1 del canal" << k+1 << ": " << input_real[k] << "\n";
		std::cout << "Dato original 2 del canal" << k+1 << ": " << EMG_raw << "\n";
		std::cout << "Dato original 3 del canal" << k+1 << ": " << EMG_raw[k].to_float() << "\n";*/

		//Cuantización de la operacion  de la muestra n al cuadrado
		Q_data EMG_sqrt[k] = (Q_data)((Q_product)(prev_input_1[k]*prev_input_1[k]));

		//Cuantización de la operacion  de la muestra n-1 * n+1
		Q_data EMG_product[k] = (Q_data)((Q_product)(prev_input_2[k]*input_real[k]));

		//Cálculo de la salida y Cuantización de la salida
		//Cada canal se va a sacar como una variable independiente
		switch (k){
			case 1://Salida del Canal 1
			    output_C1[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 2://Salida del Canal 2
			    output_C2[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 3://Salida del Canal 3
			    output_C3[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 4://Salida del Canal 4
			    output_C4[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 5://Salida del Canal 5
			    output_C5[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 6://Salida del Canal 6
			    output_C6[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 7://Salida del Canal 7
			    output_C7[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
			case 8://Salida del Canal 8
			    output_C8[0]= (Q_out)(4*((Q_data)((Q_suma)(EMG_sqrt[k] - EMG_product[k]))));
			    break;
		}
		//Actualización de los valores
		prev_input_2[k] = prev_input_1[k];
		prev_input_1[k]  = input_real[k];

	}


}
