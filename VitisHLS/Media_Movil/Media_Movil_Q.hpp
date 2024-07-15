// Normalmente, se utiliza la estructura ifndef, define, endif para evitar que se redefinan cosas cuando se compila el código.
#ifndef Media_Movil_LIB
#define Media_Movil_LIB

// RNC: Cuando tengas variables globales, mejor declaralas con un #define.
// Definicion de las variables globales
#define Nsamples	64
#define Nshift		6 // log2(Nsamples)

#include "quant.hpp"

// RNC: Aquí debemos declarar la función que estamos creando para que la encuentre en el testbench.
void media_movil(Q_data input[1], Q_data output[1]);

#endif
