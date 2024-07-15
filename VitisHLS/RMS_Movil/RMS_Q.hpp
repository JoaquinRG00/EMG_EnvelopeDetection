// Normalmente, se utiliza la estructura ifndef, define, endif para evitar que se redefinan cosas cuando se compila el código.
#ifndef RMS_LIB
#define RMS_LIB

// RNC: Cuando tengas variables globales, mejor declaralas con un #define.
// Definicion de las variables globales
#define Nsamples	64
#define Nshift		6 // log2(Nsamples)

#include "quant.hpp"

// Declaración la función que estamos creando para que la encuentre en el testbench.
void RMS(Q_data input[1], Q_data output[1]);

#endif
