//Test Bench del TKEO
//Código del TKEO con Ap_fixed (los datos estan cuantizados)
//Joaquín Ramos García

#include <iostream>   // cout
#include "TKEO_Q_8C.hpp" // Se declara el archivo que se va a simular. RNC: Sí, pero lo tienes que crear, porque sólo así no funciona.
#include <cmath>
#include <fstream>
#include <cstdint> // Para usar tipos de datos específicos como int32_t y uint32_t

Q_data in_real[9140];
Q_out out_gold[9140];
Q_out out_gold_ok[9140];
Q_out output_C1[9140];
Q_out output_C2[9140];
Q_out output_C3[9140];
Q_out output_C4[9140];
Q_out output_C5[9140];
Q_out output_C6[9140];
Q_out output_C7[9140];
Q_out output_C8[9140];


int32_t TL_Data[9140*9];

#define status_word 0x000C0000;



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
    uint32_t ceros= 0b0000;
    //Creacción del TL_data
    for(int j=0; j < 9140*9; j+=9 ){
    	uint32_t indice = 0; // 4 bits
    	for(int k=0; k < 9; k++ ){
    		switch (k){
    		case 0:
    			TL_Data[j+k]=status_word;
    			break;
    		case 1:
    			// ToDo: Print in_real
    		    TL_Data[j+k]=(indice << 28) |  (in_real[j/9]);
    		    // ToDo: Print TL_data
    		    break;
    		case 2:
    			TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    			break;
    		case 3:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		case 4:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		case 5:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		case 6:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		case 7:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		case 8:
    		    TL_Data[j+k]=(indice << 28) | (ceros << 24) | (in_real[j/9]);
    		    break;
    		}
    		std::cout << "TL_Data del canal" << k << ": " << TL_Data[j+k]<< "\n";
    		std::cout << "Dato original 1 del canal" << k << ": " << in_real[j/9]<< "\n";
    		std::cout << "Dato original 2 del canal" << k << ": " << ((TL_Data[j+k] ) & 0xFFFFFF) << "\n";
    		indice = (indice + 1);
    	}

    }

    // Leer datos de salida esperados
    for (int i = 0; i < 9140; ++i)
    {
        //fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(Q_out));
        fileOutput.read(reinterpret_cast<char*>(&out_gold[i]), sizeof(int32_t));
        out_gold_ok[i] = (Q_out)(out_gold[i]);
    }

    // Procesar datos
    for (int i = 0; i < 9140 ; i ++ ) {
        TKEO(&TL_Data[i*9], &output_C1[i],&output_C2[i],&output_C3[i],&output_C4[i],&output_C5[i],&output_C6[i],&output_C7[i],&output_C8[i]);
    }

/*
    // Comparar resultados
    for (int i = 0; i < 9140; ++i)
    {

    	if (fabs(static_cast<double>(out_gold[i]) - static_cast<double>(output_C1[i])) > 0.0000001)
        {
            std::cout << "ERROR " << i << ": outputC = " << output_C1[i] << " | outputG = "  << out_gold_ok[i] << " | error = " << (out_gold_ok[i] - output_C1[i]) << "\n";
        }
        else
        {
        	std::cout << "Filtrado correcto, salida calculada para i=" << i << ": " << output_C1[i] << " y salida de Matlab: " << out_gold_ok[i] << "\n";
        }
     }*/




    /*
    // Imprimir valores de in_real
    std::cout << "Valores de in_real:" << std::endl;
    for (int i = 0; i < 9140; ++i)
    {
        std::cout << in_real[i] << std::endl;
    }

    // Imprimir valores de TL_Data
    std::cout << "Valores de TL_Data:" << std::endl;
    for (int i = 0; i < 9140*9; ++i)
    {
        std::cout << TL_Data[i] << std::endl;
    }
    */

    return 0;


}





/*
 *
 *
 *
 * //Test Bench del TKEO
//Código del TKEO con Ap_fixed (los datos estan cuantizados)
//Joaquín Ramos García

#include <iostream>   // cout
#include "TKEO_Q.hpp" // Se declara el archivo que se va a simular. RNC: Sí, pero lo tienes que crear, porque sólo así no funciona.
#include <cmath>
#include <fstream>


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

 */

