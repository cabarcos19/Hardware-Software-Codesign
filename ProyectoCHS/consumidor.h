#ifndef CONSUMIDOR_H
#define CONSUMIDOR_H

#include "systemc.h"
#include "fifo.h"
#include <stdio.h>

SC_MODULE (consumidor) {
public:
	sc_port<read_if_T<sc_uint<8>>>	addr_in; //8 bits sin signo
	sc_port<read_if_T<sc_uint<8>>>	addr_out; //8 bits sin signo
	sc_port<read_if_T<bool>> ready_out; //bool
	sc_port<read_if_T<sc_int<32>>>	doutReal;//32 bits con signo
	sc_port<read_if_T<sc_int<32>>>	doutImg;//32 bits con signo

SC_HAS_PROCESS(consumidor);

  void consumir();

consumidor(sc_module_name name_, char *fileName) : sc_module(name_){

	cout<<"consumidor: " << name() << "  " << fileName << endl;
	fichero = fopen(fileName, "rt");
	if( !fichero ){
		cerr << "No se puede abrir el fichero de entrada: " << fileName << endl;
		return;
	}

    SC_THREAD(consumir);
}


private:
	FILE *fichero;

}; 


#endif