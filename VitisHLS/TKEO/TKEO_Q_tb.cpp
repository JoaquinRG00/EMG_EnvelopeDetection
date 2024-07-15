//Test Bench del TKEO
//Código del TKEO con Ap_fixed (los datos estan cuantizados)
//Joaquín Ramos García

#include <iostream>   // cout
#include "TKEO_Q.hpp" // Se declara el archivo que se va a simular. RNC: Sí, pero lo tienes que crear, porque sólo así no funciona.
#include <cmath>
#include <fstream>


Q_data in_real[9140];
Q_data in_real_ok[9140];
Q_out out_gold[9140];
Q_out out_gold_ok[9140];
Q_out output[9140];


#include <iostream>
#include <fstream>



int main(void)
{
    std::ifstream fileInput("Datain_TKEO_Q.dat", std::ios::binary);
    std::ifstream fileOutput("Dataout_TKEO_Q.dat", std::ios::binary);

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
        out_gold_ok[i] = (Q_out)(out_gold[i]);
    }

    // Procesar datos
    for (int i = 0; i < 9140; ++i)
    {
        TKEO(&in_real[i], &output[i]);
    }


    // Comparar resultados
    for (int i = 0; i < 9140; ++i)
    {

    	std::cout  << output[i] << "\n";

    	/*
        if (fabs(static_cast<double>(out_gold[i]) - static_cast<double>(output[i])) > 0.0000001)
        {
            std::cout << "ERROR " << i << ": outputC = " << output[i] << " | outputG = "  << out_gold_ok[i] << " | error = " << (out_gold_ok[i] - output[i]) << "\n";
        }
        else
        {
        	std::cout << "Filtrado correcto, salida calculada para i=" << i << ": " << output[i] << " y salida de Matlab: " << out_gold_ok[i] << "\n";
        }*/
    }


    // Guardar los datos de salida en un archivo
    std::ofstream fileOutputSave("Output_TKEO_Q.dat", std::ios::binary);
    if (!fileOutputSave.is_open())
    {
    	std::cerr << "Error: Apertura fichero de salida para guardar los datos fallida\n";
        return 1;
    }

    // Escribir los datos de output en el archivo
    for (int i = 0; i < 9140; ++i)
    {
        fileOutputSave.write(reinterpret_cast<char*>(&output[i]), sizeof(Q_out));
    }

    // Cerrar el archivo de salida
    fileOutputSave.close();

}

/*
Q_data in_real[9140];

Q_out out_gold[9140];
Q_out out_gold_ok[9140];
Q_out output[9140];


#include <iostream>
#include <fstream>



int main(void)
{
    std::ifstream fileInput("Datain_TKEO_Q.dat", std::ios::binary);
    std::ifstream fileOutput("Dataout_TKEO_Q.dat", std::ios::binary);

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
        fileInput.read(reinterpret_cast<char*>(&in_real[i]), sizeof(Q_data));
        std::cout << "Dato Entrada 1:" << in_real[i] << "\n";
    }

    // Leer datos de salida esperados
    for (int i = 0; i < 9140; ++i)
    {
        //fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(Q_out));
        fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(int32_t));
        out_gold_ok[i] = (Q_out)(out_gold[i]);
    }

    // Procesar datos
    for (int i = 0; i < 9140; ++i)
    {
        TKEO(&in_real[i], &output[i]);
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

}*/
/*
Q_data in_real[9140];

Q_out out_gold[9140];
Q_out out_gold_ok[9140];
Q_out output[9140];


#include <iostream>
#include <fstream>
#include <vector>


int main(void)
{
    std::ifstream fileInput("Datain_TKEO_Q.dat", std::ios::binary);
    std::ifstream fileOutput("Dataout_TKEO_Q.dat", std::ios::binary);


    if (!fileOutput.is_open())
    {
        std::cerr << "Error: Apertura fichero de salida fallida\n";
        return 1;
    }




        if (!fileInput.is_open()) {
            std::cerr << "Error: Apertura fichero de entrada fallida\n";
            return 1;
        }

        // Determinar el tamaño del archivo
        fileInput.seekg(0, std::ios::end);
        std::streampos fileSize = fileInput.tellg();
        fileInput.seekg(0, std::ios::beg);

        // Calcular el número de elementos (cada uno es int32_t)
        size_t numElements = fileSize / sizeof(int32_t);

        // Crear un vector para almacenar los datos leídos
        std::vector<Q_data> in_real(numElements);

        // Leer datos de entrada
        for (size_t i = 0; i < numElements; ++i) {
            int32_t binary_value;
            fileInput.read(reinterpret_cast<char*>(&binary_value), sizeof(int32_t));
            if (fileInput.gcount() != sizeof(int32_t)) {
                std::cerr << "Error: No se pudieron leer todos los datos\n";
                return 1;
            }
            in_real[i] = *reinterpret_cast<float*>(&binary_value);
            //std::cout << "Dato Entrada " << i << ": " << in_real[i] << "\n";
        }

        fileInput.close();


    // Leer datos de salida esperados
    for (int i = 0; i < 9140; ++i)
    {
        //fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(Q_out));
        fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(int32_t));
        out_gold_ok[i] = (Q_out)(out_gold[i]);
    }

    // Procesar datos
    for (int i = 0; i < 9140; ++i)
    {
        TKEO(&in_real[i], &output[i]);
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

}*/





