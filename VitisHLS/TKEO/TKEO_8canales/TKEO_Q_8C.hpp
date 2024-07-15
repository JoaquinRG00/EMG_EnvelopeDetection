// Normalmente, se utiliza la estructura ifndef, define, endif para evitar que se redefinan cosas cuando se compila el código.
#ifndef TKEO_LIB
#define TKEO_LIB

// RNC: Cuando tengas variables globales, mejor declaralas con un #define.
// Definicion de las variables globales
#define Nsamples	64
#define Nshift		6 // log2(Nsamples)

#include "quant.hpp"

// RNC: Aquí debemos declarar la función que estamos creando para que la encuentre en el testbench.
void TKEO(int32_t input[9], Q_out output_C1[1], Q_out output_C2[1], Q_out output_C3[1], Q_out output_C4[1], Q_out output_C5[1], Q_out output_C6[1], Q_out output_C7[1], Q_out output_C8[1]);

#endif
