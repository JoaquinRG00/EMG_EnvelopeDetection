// Normalmente, se utiliza la estructura ifndef, define, endif para evitar que se redefinan cosas cuando se compila el c�digo.
#ifndef TKEO_LIB
#define TKEO_LIB

// RNC: Cuando tengas variables globales, mejor declaralas con un #define.
// Definicion de las variables globales
#define Nsamples	64
#define Nshift		6 // log2(Nsamples)

// RNC: Aqu� debemos declarar la funci�n que estamos creando para que la encuentre en el testbench.
void TKEO(float input[1], float output[1]);

#endif
