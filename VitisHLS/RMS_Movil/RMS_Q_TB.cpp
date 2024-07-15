//Test Bench de la RMS
//Código de la RMS con Ap_fixed (los datos estan cuantizados)
//Joaquín Ramos García

#include <iostream>   // cout
#include "RMS_Q.hpp" // Se declara el archivo que se va a simular. RNC: Sí, pero lo tienes que crear, porque sólo así no funciona.
#include <cmath>
#include <fstream>


Q_data in_real[9140];
Q_data out_gold[9140];
Q_data out_gold_ok[9140];
Q_data output[9140];


#include <iostream>
#include <fstream>


int main(void)
{
    std::ifstream fileInput("Datain_RMS_Q2.dat", std::ios::binary);
    std::ifstream fileOutput("Dataout_RMS_Q2.dat", std::ios::binary);

    if (!fileInput.is_open())
    {
        std::cerr << "Error: Apertura fichero de entrada fallida\n";
        return 1;
    }

    if (!fileOutput.is_open())
    {
        std::cerr << "Error: Apertura fichero de salida fallida\n";
        return 1;
    }


    // Leer datos de entrada
    for (int i = 0; i < 9140; ++i)
    {

    	//fileInput.read(reinterpret_cast<char*>(&in_real[i]), sizeof(Q_data));
        fileInput.read(reinterpret_cast<char*>(&in_real[i]), sizeof(int32_t));
    }

    // Leer datos de salida esperados
    for (int i = 0; i < 9140; ++i)
    {
        //fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(Q_out));
        fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(int32_t));
        out_gold_ok[i] = (Q_data)(out_gold[i]);
    }

    // Procesar datos
    for (int i = 0; i < 9140; ++i)
    {
    	RMS(&in_real[i], &output[i]);
    }


    // Comparar resultados
    for (int i = 0; i < 9140; ++i)
    {

        if (fabs(static_cast<double>(out_gold[i]) - static_cast<double>(output[i])) > 0.0000001)
        {
            std::cout << "ERROR " << i << ": outputC = " << output[i] << " | outputG = "  << out_gold_ok[i] << " | error = " << (out_gold_ok[i] - output[i]) << "\n";
        }
        else
        {
        	std::cout << "Filtrado correcto, salida calculada para i=" << i << ": " << output[i] << " y salida de Matlab: " << out_gold_ok[i] << "\n";
        }
    }
}
