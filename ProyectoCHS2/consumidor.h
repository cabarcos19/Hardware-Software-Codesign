	#ifndef CONSUMIDOR_H
	#define CONSUMIDOR_H

	#include "systemc.h"
	#include <stdio.h>

	SC_MODULE (consumidor) {
	public:
	sc_in< bool > clk, rst, rx_valid;
	sc_in < sc_uint<8> > rx_data;


	SC_HAS_PROCESS(consumidor);

	  void consumir(){

		int RX_DATA;
		int RX; 

		if( rst.read() ){
			N = 0; 
			return;
		}

		if( rx_valid.read() ){
			RX_DATA = rx_data.read().to_int();
			fscanf(resultados, "%d ", &RX);
			if(RX_DATA != RX)
				fprintf(stderr, "Error rx_data posicion %d : %d <> %d\n", N, RX, RX_DATA);
			++N;
			if(N == 255){
				fclose(resultados);
				sc_stop();
			}
		}

	  }

	consumidor(sc_module_name name_, char *fileName) : sc_module(name_){

		cout<<"consumidor: " << name() << "  " << fileName << endl;

		resultados = fopen(fileName, "rt");
		if(!resultados){
			fprintf(stderr, "No es posible abrir el fichero %s\n", fileName);
			exit(-1);
		}

		SC_METHOD(consumir);
		sensitive << clk.pos();
	}
	FILE *resultados;
	int N, estado;  
	}; 


	#endif